//
// Created by Герман Багдасарян on 27.11.2025.
//

#include "dot_writer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- утилита: строка-добавлялка с realloc ---------- */

static void append_str(char** buf, size_t* len, size_t* cap, const char* s) {
    if (!s) return;
    size_t add = strlen(s);
    if (*len + add + 1 > *cap) {
        size_t new_cap = (*cap ? *cap * 2 : 64);
        while (*len + add + 1 > new_cap) {
            new_cap *= 2;
        }
        char* nbuf = (char*)realloc(*buf, new_cap);
        if (!nbuf) {
            fprintf(stderr, "Out of memory in append_str\n");
            exit(1);
        }
        *buf = nbuf;
        *cap = new_cap;
    }
    memcpy(*buf + *len, s, add);
    *len += add;
    (*buf)[*len] = '\0';
}

/* ---------- escape для dot-меток: \n, ", \ ---------- */

static char* escape_dot_label(const char* s) {
    if (!s) {
        char* r = (char*)malloc(1);
        if (r) r[0] = '\0';
        return r;
    }
    size_t cap = strlen(s) * 4 + 8;
    size_t len = 0;
    char* buf = (char*)malloc(cap);
    if (!buf) return NULL;

    for (const char* p = s; *p; ++p) {
        char c = *p;
        if (c == '\n') {
            append_str(&buf, &len, &cap, "\\n");
        } else if (c == '\r') {
            /* игнорируем или можно сделать \\n */
        } else if (c == '"') {
            append_str(&buf, &len, &cap, "\\\"");
        } else if (c == '\\') {
            append_str(&buf, &len, &cap, "\\\\");
        } else {
            char tmp[2] = { c, 0 };
            append_str(&buf, &len, &cap, tmp);
        }
    }
    buf[len] = '\0';
    return buf;
}

/* escape для идентификаторов (простее: экранируем только " и \) */
static char* escape_dot_id(const char* s) {
    return escape_dot_label(s);
}

/* ---------- строковое представление вида операции ---------- */

static const char* op_kind_to_string(OperationKind k) {
    switch (k) {
        case OP_ASSIGN:      return "ASSIGN";
        case OP_BINARY:      return "BINARY";
        case OP_UNARY:       return "UNARY";
        case OP_CALL:        return "CALL";
        case OP_RETURN:      return "RETURN";
        case OP_BRANCH_COND: return "BRANCH_COND";
        case OP_JUMP:        return "JUMP";
        case OP_UNKNOWN:
        default:             return "OP";
    }
}

/* ---------- собрать label для одного базового блока ---------- */

static char* build_block_label(const BasicBlock* bb) {
    char* buf = NULL;
    size_t len = 0, cap = 0;
    char tmp[128];

    /* первая строка: B<i> (+ entry/exit) */
    snprintf(tmp, sizeof(tmp), "B%d", bb->id);
    append_str(&buf, &len, &cap, tmp);

    if (bb->is_entry) {
        append_str(&buf, &len, &cap, " (entry)");
    }
    if (bb->is_exit) {
        append_str(&buf, &len, &cap, " (exit)");
    }

    /* далее — по строке на каждую OperationTree в блоке */
    for (size_t i = 0; i < bb->op_count; ++i) {
        OperationTree t = bb->operations[i];
        if (!t) continue;

        Operation* op = &t->operation;
        const char* kind_str = op_kind_to_string(op->kind);
        const char* text = (op->op ? op->op : "");

        append_str(&buf, &len, &cap, "\n"); /* новая строка внутри label */

        append_str(&buf, &len, &cap, kind_str);
        append_str(&buf, &len, &cap, ": ");

        if (text && *text) {
            append_str(&buf, &len, &cap, text);
        } else {
            append_str(&buf, &len, &cap, "<no-op>");
        }
    }

    if (!buf) {
        buf = (char*)malloc(1);
        if (buf) buf[0] = '\0';
    }

    return buf;
}

/* ---------- вывод CFG в dot ---------- */

int dot_write_cfg(const ControlFlowGraph* cfg, const char* path) {
    if (!cfg || !path) return -1;

    FILE* f = fopen(path, "w");
    if (!f) {
        perror("dot_write_cfg fopen");
        return -1;
    }

    const char* fname = (cfg->function_name ? cfg->function_name : "CFG");
    char* fname_esc = escape_dot_id(fname);

    fprintf(f, "digraph \"%s\" {\n", fname_esc ? fname_esc : "CFG");
    fprintf(f, "  node [shape=box, fontsize=10];\n");
    fprintf(f, "  rankdir=TB;\n\n");

    /* узлы */
    for (size_t i = 0; i < cfg->block_count; ++i) {
        const BasicBlock* bb = &cfg->blocks[i];

        char nodeId[32];
        snprintf(nodeId, sizeof(nodeId), "B%d", bb->id);

        char* raw_label = build_block_label(bb);
        char* esc_label = escape_dot_label(raw_label);

        /* проверяем, есть ли в блоке условие */
        int has_branch = 0;
        for (size_t i = 0; i < bb->op_count; ++i) {
            OperationTree t = bb->operations[i];
            if (t && t->operation.kind == OP_BRANCH_COND) {
                has_branch = 1;
                break;
            }
        }

        /* выберем форму:
           - ромб для условий
           - овал для entry/exit
           - прямоугольник для обычных блоков
        */
        const char* shape = "box";
        if (bb->is_entry || bb->is_exit) {
            shape = "oval";
        }
        if (has_branch) {
            shape = "diamond";
        }

        fprintf(f, "  %s [label=\"%s\", shape=%s];\n",
                nodeId,
                esc_label ? esc_label : "",
                shape);

        free(raw_label);
        free(esc_label);
    }

    fprintf(f, "\n");

    /* рёбра */
    for (size_t i = 0; i < cfg->block_count; ++i) {
        const BasicBlock* bb = &cfg->blocks[i];
        char src[32];
        snprintf(src, sizeof(src), "B%d", bb->id);

        if (bb->next != CFG_INVALID_BLOCK) {
            char dst[32];
            snprintf(dst, sizeof(dst), "B%d", bb->next);
            fprintf(f, "  %s -> %s [label=\"next\"];\n", src, dst);
        }
        if (bb->true_target != CFG_INVALID_BLOCK) {
            char dst[32];
            snprintf(dst, sizeof(dst), "B%d", bb->true_target);
            fprintf(f, "  %s -> %s [label=\"true\"];\n", src, dst);
        }
        if (bb->false_target != CFG_INVALID_BLOCK) {
            char dst[32];
            snprintf(dst, sizeof(dst), "B%d", bb->false_target);
            fprintf(f, "  %s -> %s [label=\"false\"];\n", src, dst);
        }
    }

    fprintf(f, "}\n");
    fclose(f);
    free(fname_esc);
    return 0;
}

/* ---------- вывод графа вызовов в dot ---------- */

int dot_write_call_graph(const CallGraph* cg, const char* path) {
    if (!cg || !path) return -1;

    FILE* f = fopen(path, "w");
    if (!f) {
        perror("dot_write_call_graph fopen");
        return -1;
    }

    fprintf(f, "digraph CallGraph {\n");
    fprintf(f, "  node [shape=ellipse, fontsize=10];\n\n");

    /* узлы-функции */
    for (size_t i = 0; i < cg->func_count; ++i) {
        const char* name = cg->functions[i];
        if (!name) continue;

        char* esc = escape_dot_id(name);
        fprintf(f, "  \"%s\" [label=\"%s\"];\n",
                esc ? esc : "",
                esc ? esc : "");
        free(esc);
    }

    fprintf(f, "\n");

    /* рёбра вызовов */
    for (size_t i = 0; i < cg->edge_count; ++i) {
        const CallGraphEdge* e = &cg->edges[i];
        if (!e->caller || !e->callee) continue;

        char* caller_esc = escape_dot_id(e->caller);
        char* callee_esc = escape_dot_id(e->callee);

        fprintf(f, "  \"%s\" -> \"%s\";\n",
                caller_esc ? caller_esc : "",
                callee_esc ? callee_esc : "");

        free(caller_esc);
        free(callee_esc);
    }

    fprintf(f, "}\n");
    fclose(f);
    return 0;
}
