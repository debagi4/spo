//
// Created by Герман Багдасарян on 27.11.2025.
//
#include "cfg_from_tree.h"
#include "Tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* ---------- Вспомогательные функции ---------- */

static int is_type(const Tree *node, const char *type) {
    return node && node->type && strcmp(node->type, type) == 0;
}

static SourceLocation make_loc(const char *file) {
    SourceLocation loc;
    loc.file = file;
    loc.line = 0;
    loc.column = 0;
    return loc;
}

/* Нумерация анонимных функций, если не можем вытащить имя */
static int anon_func_counter = 0;

/* Вытащить имя функции из текста вида "int main(a, b) { ... }" */
static char *extract_func_name(const char *text) {
    if (!text) goto anon;

    const char *p = strchr(text, '(');
    if (!p) goto anon;

    const char *end = p - 1;
    while (end > text && (*end == ' ' || *end == '\t' ||
                          *end == '\n' || *end == '\r'))
        --end;

    const char *start = end;
    while (start > text) {
        char c = start[-1];
        if (isalnum((unsigned char) c) || c == '_')
            --start;
        else
            break;
    }

    if (start > end) goto anon;

    size_t len = (size_t) (end - start + 1);
    if (len == 0) goto anon;

    char *name = (char *) malloc(len + 1);
    if (!name) return NULL;
    memcpy(name, start, len);
    name[len] = '\0';
    return name;

anon: {
        char buf[32];
        snprintf(buf, sizeof(buf), "func%d", ++anon_func_counter);
        char *name = (char *) malloc(strlen(buf) + 1);
        if (!name) return NULL;
        strcpy(name, buf);
        return name;
    }
}

/* Определить, похоже ли выражение на вызов функции: foo(...) */
static OperationKind guess_kind_and_name(const char *text, char **outName) {
    if (!text) {
        *outName = NULL;
        return OP_UNKNOWN;
    }

    const char *p = strchr(text, '(');
    if (!p) {
        *outName = strdup(text);
        return OP_UNKNOWN;
    }

    const char *q = p;
    while (q > text && (q[-1] == ' ' || q[-1] == '\t' ||
                        q[-1] == '\n' || q[-1] == '\r'))
        --q;

    if (q == text) {
        *outName = strdup(text);
        return OP_UNKNOWN;
    }

    const char *end = q - 1;
    const char *start = end;
    while (start > text) {
        char c = start[-1];
        if (isalnum((unsigned char) c) || c == '_')
            --start;
        else
            break;
    }

    size_t len = (size_t) (end - start + 1);
    if (len == 0) {
        *outName = strdup(text);
        return OP_UNKNOWN;
    }

    char buf[128];
    if (len >= sizeof(buf)) len = sizeof(buf) - 1;
    memcpy(buf, start, len);
    buf[len] = '\0';

    /* Отсекаем if/while/for/do, чтобы не путать с вызовом */
    if (strcmp(buf, "if") == 0 ||
        strcmp(buf, "while") == 0 ||
        strcmp(buf, "for") == 0 ||
        strcmp(buf, "do") == 0) {
        *outName = strdup(text);
        return OP_UNKNOWN;
    }

    *outName = strdup(buf);
    return OP_CALL;
}

/* обрезать пробелы и ; в конце */
static char* trim_and_strip_semicolon(const char* text) {
    if (!text) return NULL;

    const char* start = text;
    while (*start && isspace((unsigned char)*start))
        start++;

    const char* end = text + strlen(text);
    while (end > start &&
           (isspace((unsigned char)end[-1]) || end[-1] == ';'))
        --end;

    size_t len = (size_t)(end - start);
    char* res = (char*)malloc(len + 1);
    if (!res) return NULL;
    memcpy(res, start, len);
    res[len] = '\0';
    return res;
}

/* Создать OperationTreeNode для выражения/операции */
static OperationTree make_op_for_statement(const Tree* node,
                                           const char* file)
{
    const char* raw = (node && node->value) ? node->value
                                            : (node ? node->type : NULL);
    if (!raw) return NULL;

    char* text = trim_and_strip_semicolon(raw);
    if (!text) return NULL;

    OperationTreeNode* t = (OperationTreeNode*)calloc(1, sizeof(OperationTreeNode));
    if (!t) {
        free(text);
        return NULL;
    }

    t->children = NULL;
    t->child_count = 0;
    t->operation.operands = NULL;
    t->operation.operand_count = 0;
    t->operation.loc = make_loc(file);

    /* детектим тип операции, но сам текст не режем */
    const char* p = text;
    while (*p && isspace((unsigned char)*p)) p++;

    if (strncmp(p, "return", 6) == 0 &&
        (p[6] == 0 || isspace((unsigned char)p[6]))) {
        t->operation.kind = OP_RETURN;
        } else if (strstr(text, "(") && strstr(text, ")")) {
            /* очень грубо: что-то с () считаем вызовом */
            t->operation.kind = OP_CALL;
        } else if (strchr(text, '=')) {
            t->operation.kind = OP_ASSIGN;
        } else {
            t->operation.kind = OP_UNKNOWN;
        }

    /* сам текст кладём целиком в op */
    t->operation.op = text;  /* text уже на heap, не free-им */

    return t;
}

static OperationTree make_op_for_condition(const Tree* node,
                                           const char* file)
{
    const char* text = (node && node->value) ? node->value
                                             : (node ? node->type : NULL);

    char* cond = NULL;

    if (text) {
        /* ищем условие в первых скобках: ( ... ) */
        const char* lpar = strchr(text, '(');
        const char* rpar = lpar ? strchr(lpar + 1, ')') : NULL;

        if (lpar && rpar && rpar > lpar + 1) {
            const char* start = lpar + 1;
            const char* end   = rpar;

            while (start < end && isspace((unsigned char)*start))
                start++;
            while (end > start && isspace((unsigned char)end[-1]))
                --end;

            size_t len = (size_t)(end - start);
            cond = (char*)malloc(len + 1);
            if (cond) {
                memcpy(cond, start, len);
                cond[len] = '\0';
            }
        }
    }

    OperationTreeNode* t = (OperationTreeNode*)calloc(1, sizeof(OperationTreeNode));
    if (!t) {
        free(cond);
        return NULL;
    }

    t->operation.kind = OP_BRANCH_COND;
    t->operation.op   = cond ? cond : (text ? strdup(text) : NULL);
    t->operation.operands = NULL;
    t->operation.operand_count = 0;
    t->operation.loc = make_loc(file);
    t->children = NULL;
    t->child_count = 0;

    return t;
}

/* Создать новый CfgStmt */
static CfgStmt *new_stmt(CfgStmtKind kind, const char *file) {
    CfgStmt *s = (CfgStmt *) calloc(1, sizeof(CfgStmt));
    if (!s) return NULL;
    s->kind = kind;
    s->loc = make_loc(file);
    s->next = NULL;
    return s;
}

/* Добавить оператор в конец односвязного списка */
static void append_stmt(CfgStmt **head, CfgStmt **tail, CfgStmt *s) {
    if (!s) return;
    if (!*head) {
        *head = s;
        *tail = s;
    } else {
        (*tail)->next = s;
        *tail = s;
    }
}

/* Вперёд объявим разбор блоков и if/while/doWhile */
static CfgStmt *parse_block_statements(Tree *block, const char *filename);

static CfgStmt *parse_if_node(Tree *node, const char *filename);

static CfgStmt *parse_while_node(Tree *node, const char *filename);

static CfgStmt *parse_doWhile_node(Tree *node, const char *filename);

/* Разбор одного узла-оператора в CfgStmt */
static CfgStmt *parse_single_stmt(Tree *node, const char *filename) {
    if (!node) return NULL;

    if (is_type(node, "varDecl") || is_type(node, "expr")) {
        CfgStmt *s = new_stmt(CFG_STMT_SIMPLE, filename);
        s->op = make_op_for_statement(node, filename);
        return s;
    }
    if (is_type(node, "if")) {
        return parse_if_node(node, filename);
    }
    if (is_type(node, "while")) {
        return parse_while_node(node, filename);
    }
    if (is_type(node, "doWhile")) {
        return parse_doWhile_node(node, filename);
    }

    /* Остальные типы (пока) игнорируем */
    return NULL;
}

/* Разбор списка операторов внутри блока */
static CfgStmt *parse_block_statements(Tree *block, const char *filename) {
    if (!block) return NULL;

    CfgStmt *head = NULL;
    CfgStmt *tail = NULL;

    for (int i = 0; i < block->child_count; ++i) {
        Tree *ch = block->children[i];

        if (is_type(ch, "block")) {
            /* Вложенный блок — просто разворачиваем его операторы в текущий список */
            CfgStmt *inner = parse_block_statements(ch, filename);
            if (inner) {
                if (!head) {
                    head = inner;
                    tail = inner;
                    while (tail->next) tail = tail->next;
                } else {
                    tail->next = inner;
                    while (tail->next) tail = tail->next;
                }
            }
            continue;
        }

        CfgStmt *s = parse_single_stmt(ch, filename);
        if (s) {
            append_stmt(&head, &tail, s);
        }
    }

    return head;
}

/* if (...) { ... } [else { ... }] */
static CfgStmt *parse_if_node(Tree *node, const char *filename) {
    CfgStmt *s = new_stmt(CFG_STMT_IF, filename);
    if (!s) return NULL;

    s->op = make_op_for_condition(node, filename);

    Tree *then_block = NULL;
    Tree *else_block = NULL;

    for (int i = 0; i < node->child_count; ++i) {
        Tree *ch = node->children[i];
        if (is_type(ch, "block")) {
            if (!then_block)
                then_block = ch;
            else if (!else_block)
                else_block = ch;
        }
    }

    s->u.if_stmt.then_branch = parse_block_statements(then_block, filename);
    s->u.if_stmt.else_branch = parse_block_statements(else_block, filename);

    return s;
}

/* while (...) { ... } */
static CfgStmt *parse_while_node(Tree *node, const char *filename) {
    CfgStmt *s = new_stmt(CFG_STMT_WHILE, filename);
    if (!s) return NULL;

    s->op = make_op_for_condition(node, filename);

    Tree *body_block = NULL;
    for (int i = 0; i < node->child_count; ++i) {
        Tree *ch = node->children[i];
        if (is_type(ch, "block")) {
            body_block = ch;
            break;
        }
    }

    s->u.while_stmt.body = parse_block_statements(body_block, filename);
    return s;
}

/* do { ... } while (...); */
static CfgStmt *parse_doWhile_node(Tree *node, const char *filename) {
    CfgStmt *s = new_stmt(CFG_STMT_DO_WHILE, filename);
    if (!s) return NULL;

    s->op = make_op_for_condition(node, filename);

    Tree *body_block = NULL;
    for (int i = 0; i < node->child_count; ++i) {
        Tree *ch = node->children[i];
        if (is_type(ch, "block")) {
            body_block = ch;
            break;
        }
    }

    s->u.do_while_stmt.body = parse_block_statements(body_block, filename);
    return s;
}

/* Добавить функцию в FileFunctions (динамический массив) */
static void file_functions_append(FileFunctions *ff,
                                  const CfgFunctionAst *fn) {
    if (ff->count == ff->capacity) {
        size_t new_cap = ff->capacity ? ff->capacity * 2 : 4;
        CfgFunctionAst *arr =
                (CfgFunctionAst *) realloc(ff->funcs,
                                           new_cap * sizeof(CfgFunctionAst));
        if (!arr) {
            fprintf(stderr, "Out of memory in file_functions_append\n");
            exit(1);
        }
        ff->funcs = arr;
        ff->capacity = new_cap;
    }
    ff->funcs[ff->count++] = *fn;
}

/* Обработка узла funcDef: строим CfgFunctionAst */
static void process_func_node(Tree *funcNode,
                              const char *filename,
                              FileFunctions *out) {
    CfgFunctionAst f;
    memset(&f, 0, sizeof(f));

    f.source_file = (char *) filename;
    f.signature.name = extract_func_name(funcNode->value);
    f.signature.parameters = NULL;
    f.signature.param_count = 0;
    f.signature.return_type = NULL;
    f.body = NULL;

    Tree *body_block = NULL;
    for (int i = 0; i < funcNode->child_count; ++i) {
        Tree *ch = funcNode->children[i];
        if (is_type(ch, "block")) {
            body_block = ch;
            break;
        }
    }

    if (body_block) {
        f.body = parse_block_statements(body_block, filename);
    }

    file_functions_append(out, &f);
}

/* Обход всего AST в поисках funcDef */
static void collect_functions_from_tree(Tree *node,
                                        const char *filename,
                                        FileFunctions *out) {
    if (!node) return;

    if (is_type(node, "funcDef")) {
        process_func_node(node, filename, out);
        /* продолжаем спускаться — на всякий случай, если вложенные функции */
    }

    for (int i = 0; i < node->child_count; ++i) {
        collect_functions_from_tree(node->children[i], filename, out);
    }
}

/* ---------- Публичная функция ---------- */

FileFunctions build_cfg_from_parse_result(const char *filename,
                                          const ParseResult *pr) {
    FileFunctions ff;
    ff.funcs = NULL;
    ff.count = 0;
    ff.capacity = 0;

    if (!pr || !pr->tree)
        return ff;

    collect_functions_from_tree(pr->tree, filename, &ff);
    return ff;
}
