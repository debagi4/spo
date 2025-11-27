#include "cfg.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ---------- Вспомогательные утилиты ---------- */

static char *cfg_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *r = (char *) malloc(len + 1);
    if (!r) {
        fprintf(stderr, "Out of memory in cfg_strdup\n");
        exit(1);
    }
    memcpy(r, s, len + 1);
    return r;
}

void cfg_module_result_init(CfgModuleResult *r) {
    if (!r) return;
    memset(r, 0, sizeof(*r));
}

void cfg_module_result_free(CfgModuleResult *r) {
    if (!r) return;

    /* Освобождаем CFG */
    for (size_t i = 0; i < r->program.file_count; ++i) {
        FileInfo *fi = &r->program.files[i];
        for (size_t j = 0; j < fi->func_count; ++j) {
            FunctionInfo *fun = &fi->functions[j];
            ControlFlowGraph *cfg = &fun->cfg;

            if (cfg->blocks) {
                for (size_t b = 0; b < cfg->block_count; ++b) {
                    BasicBlock *bb = &cfg->blocks[b];
                    free(bb->operations); /* сами OperationTree не трогаем */
                }
                free(cfg->blocks);
            }
        }
        free(fi->functions);
        /* fi->path, signature.name и т.п. считаем принадлежащими парсеру */
    }
    free(r->program.files);

    /* Граф вызовов */
    for (size_t i = 0; i < r->call_graph.func_count; ++i)
        free(r->call_graph.functions[i]);
    free(r->call_graph.functions);

    for (size_t i = 0; i < r->call_graph.edge_count; ++i) {
        free(r->call_graph.edges[i].caller);
        free(r->call_graph.edges[i].callee);
    }
    free(r->call_graph.edges);

    /* Ошибки */
    for (size_t i = 0; i < r->error_count; ++i) {
        free(r->errors[i].message);
    }
    free(r->errors);

    memset(r, 0, sizeof(*r));
}

static void add_error(CfgModuleResult *result,
                      const char *msg,
                      SourceLocation loc) {
    if (!result) return;

    if (result->error_count == result->error_capacity) {
        size_t new_cap = result->error_capacity ? result->error_capacity * 2 : 4;
        AnalyzerError *arr = (AnalyzerError *) realloc(
            result->errors,
            new_cap * sizeof(AnalyzerError)
        );
        if (!arr) {
            fprintf(stderr, "Out of memory in add_error\n");
            exit(1);
        }
        result->errors = arr;
        result->error_capacity = new_cap;
    }

    AnalyzerError *e = &result->errors[result->error_count++];
    e->message = cfg_strdup(msg);
    e->loc = loc;
}

/* ---------- Работа с CFG: блоки и операции ---------- */

static BasicBlockId cfg_new_block(ControlFlowGraph *cfg) {
    if (cfg->block_count == cfg->block_capacity) {
        size_t new_cap = cfg->block_capacity ? cfg->block_capacity * 2 : 4;
        BasicBlock *nb = (BasicBlock *) realloc(
            cfg->blocks,
            new_cap * sizeof(BasicBlock)
        );
        if (!nb) {
            fprintf(stderr, "Out of memory in cfg_new_block\n");
            exit(1);
        }
        cfg->blocks = nb;
        cfg->block_capacity = new_cap;
    }

    BasicBlockId id = (BasicBlockId) cfg->block_count;
    BasicBlock *b = &cfg->blocks[cfg->block_count++];
    memset(b, 0, sizeof(*b));
    b->id = id;
    b->next = CFG_INVALID_BLOCK;
    b->true_target = CFG_INVALID_BLOCK;
    b->false_target = CFG_INVALID_BLOCK;
    b->operations = NULL;
    b->op_count = 0;
    b->op_capacity = 0;
    b->is_entry = 0;
    b->is_exit = 0;
    b->terminated_by_jump = 0;
    return id;
}

static BasicBlock *cfg_get_block(ControlFlowGraph *cfg, BasicBlockId id) {
    if (id < 0 || (size_t) id >= cfg->block_count) {
        fprintf(stderr, "Invalid BasicBlockId: %d\n", id);
        exit(1);
    }
    return &cfg->blocks[id];
}

static void cfg_append_operation(BasicBlock *block, OperationTree op) {
    if (!op) return;
    if (block->op_count == block->op_capacity) {
        size_t new_cap = block->op_capacity ? block->op_capacity * 2 : 4;
        OperationTree *arr = (OperationTree *) realloc(
            block->operations,
            new_cap * sizeof(OperationTree)
        );
        if (!arr) {
            fprintf(stderr, "Out of memory in cfg_append_operation\n");
            exit(1);
        }
        block->operations = arr;
        block->op_capacity = new_cap;
    }
    block->operations[block->op_count++] = op;
}

/* ---------- Стек целей break/continue ---------- */

typedef struct {
    ControlFlowGraph *cfg;
    CfgModuleResult *result;

    BasicBlockId *break_targets;
    size_t break_count;
    size_t break_capacity;

    BasicBlockId *cont_targets;
    size_t cont_count;
    size_t cont_capacity;
} CfgBuildContext;

static void push_break(CfgBuildContext *ctx, BasicBlockId id) {
    if (ctx->break_count == ctx->break_capacity) {
        size_t new_cap = ctx->break_capacity ? ctx->break_capacity * 2 : 4;
        BasicBlockId *arr = (BasicBlockId *) realloc(
            ctx->break_targets,
            new_cap * sizeof(BasicBlockId)
        );
        if (!arr) {
            fprintf(stderr, "Out of memory in push_break\n");
            exit(1);
        }
        ctx->break_targets = arr;
        ctx->break_capacity = new_cap;
    }
    ctx->break_targets[ctx->break_count++] = id;
}

static void pop_break(CfgBuildContext *ctx) {
    if (ctx->break_count > 0) ctx->break_count--;
}

static BasicBlockId current_break_target(const CfgBuildContext *ctx) {
    if (ctx->break_count == 0) return CFG_INVALID_BLOCK;
    return ctx->break_targets[ctx->break_count - 1];
}

static void push_continue(CfgBuildContext *ctx, BasicBlockId id) {
    if (ctx->cont_count == ctx->cont_capacity) {
        size_t new_cap = ctx->cont_capacity ? ctx->cont_capacity * 2 : 4;
        BasicBlockId *arr = (BasicBlockId *) realloc(
            ctx->cont_targets,
            new_cap * sizeof(BasicBlockId)
        );
        if (!arr) {
            fprintf(stderr, "Out of memory in push_continue\n");
            exit(1);
        }
        ctx->cont_targets = arr;
        ctx->cont_capacity = new_cap;
    }
    ctx->cont_targets[ctx->cont_count++] = id;
}

static void pop_continue(CfgBuildContext *ctx) {
    if (ctx->cont_count > 0) ctx->cont_count--;
}

static BasicBlockId current_continue_target(const CfgBuildContext *ctx) {
    if (ctx->cont_count == 0) return CFG_INVALID_BLOCK;
    return ctx->cont_targets[ctx->cont_count - 1];
}

/* ---------- Рекурсивная генерация CFG ---------- */

typedef struct {
    BasicBlockId entry;
    BasicBlockId exit;
} BlockRange;

static BlockRange build_stmt_list(CfgBuildContext *ctx,
                                  CfgStmt *first_stmt,
                                  BasicBlockId current);

static BlockRange build_stmt(CfgBuildContext *ctx,
                             CfgStmt *stmt,
                             BasicBlockId current);

/* Список операторов подряд */
static BlockRange build_stmt_list(CfgBuildContext *ctx,
                                  CfgStmt *first_stmt,
                                  BasicBlockId current) {
    BlockRange r;
    r.entry = current;
    BasicBlockId cur = current;

    CfgStmt *stmt = first_stmt;

    while (stmt) {
        BasicBlock *block = cfg_get_block(ctx->cfg, cur);

        /* Если блок уже завершён безусловным переходом — создаём новый */
        if (block->terminated_by_jump) {
            cur = cfg_new_block(ctx->cfg);
        }

        BlockRange sr = build_stmt(ctx, stmt, cur);
        cur = sr.exit;

        stmt = stmt->next;
    }

    r.exit = cur;
    return r;
}

/* Один оператор */
static BlockRange build_stmt(CfgBuildContext *ctx,
                             CfgStmt *stmt,
                             BasicBlockId current) {
    ControlFlowGraph *cfg = ctx->cfg;
    BasicBlock *curBlock = cfg_get_block(cfg, current);
    BlockRange r;
    r.entry = current;
    r.exit = current;

    switch (stmt->kind) {
        case CFG_STMT_SIMPLE: {
            cfg_append_operation(curBlock, stmt->op);
            stmt->op = NULL;
            return r;
        }

        case CFG_STMT_IF: {
            BasicBlockId condId = current;

            if (cfg_get_block(cfg, condId)->op_count > 0) {
                condId = cfg_new_block(cfg);
                cfg_get_block(cfg, current)->next = condId;
            }

            cfg_append_operation(cfg_get_block(cfg, condId), stmt->op);
            stmt->op = NULL;

            BasicBlockId thenId = cfg_new_block(cfg);
            BasicBlockId elseId = cfg_new_block(cfg);
            BasicBlockId joinId = cfg_new_block(cfg);

            BasicBlock *condBlock = cfg_get_block(cfg, condId);
            condBlock->true_target = thenId;
            condBlock->false_target = elseId;

            BlockRange thenRange = build_stmt_list(
                ctx, stmt->u.if_stmt.then_branch, thenId
            );

            BasicBlock *thenExit = cfg_get_block(cfg, thenRange.exit);
            if (!thenExit->terminated_by_jump &&
                thenExit->next == CFG_INVALID_BLOCK &&
                !thenExit->is_exit) {
                thenExit->next = joinId;
            }

            BlockRange elseRange = build_stmt_list(
                ctx, stmt->u.if_stmt.else_branch, elseId
            );

            BasicBlock *elseExit = cfg_get_block(cfg, elseRange.exit);
            if (!elseExit->terminated_by_jump &&
                elseExit->next == CFG_INVALID_BLOCK &&
                !elseExit->is_exit) {
                elseExit->next = joinId;
            }

            r.entry = condId;
            r.exit = joinId;
            return r;
        }

        case CFG_STMT_WHILE: {
            /* while(cond) body; */

            BasicBlockId condId = current;
            if (curBlock->op_count > 0) {
                condId = cfg_new_block(cfg);
                curBlock = cfg_get_block(cfg, condId);
            }

            cfg_append_operation(curBlock, stmt->op);
            stmt->op = NULL;

            BasicBlockId bodyId = cfg_new_block(cfg);
            BasicBlockId afterId = cfg_new_block(cfg);

            curBlock->true_target = bodyId;
            curBlock->false_target = afterId;

            push_break(ctx, afterId);
            push_continue(ctx, condId);

            BlockRange bodyRange = build_stmt_list(
                ctx, stmt->u.while_stmt.body, bodyId
            );

            pop_break(ctx);
            pop_continue(ctx);

            BasicBlock *bodyExit = cfg_get_block(cfg, bodyRange.exit);
            if (!bodyExit->terminated_by_jump &&
                bodyExit->next == CFG_INVALID_BLOCK &&
                !bodyExit->is_exit) {
                bodyExit->next = condId;
            }

            r.entry = condId;
            r.exit = afterId;
            return r;
        }

        case CFG_STMT_DO_WHILE: {
            /* do { body } while(cond); */

            BasicBlockId bodyId = current;
            BasicBlockId condId = cfg_new_block(cfg);
            BasicBlockId afterId = cfg_new_block(cfg);

            push_break(ctx, afterId);
            push_continue(ctx, condId);

            BlockRange bodyRange = build_stmt_list(
                ctx, stmt->u.do_while_stmt.body, bodyId
            );

            pop_break(ctx);
            pop_continue(ctx);

            BasicBlock *condBlock = cfg_get_block(cfg, condId);
            cfg_append_operation(condBlock, stmt->op);
            stmt->op = NULL;

            BasicBlock *bodyExit = cfg_get_block(cfg, bodyRange.exit);
            if (!bodyExit->terminated_by_jump &&
                bodyExit->next == CFG_INVALID_BLOCK &&
                !bodyExit->is_exit) {
                bodyExit->next = condId;
            }

            condBlock->true_target = bodyId;
            condBlock->false_target = afterId;

            r.entry = bodyId;
            r.exit = afterId;
            return r;
        }

        case CFG_STMT_FOR: {
            /* for(init; cond; step) body; */

            /* init */
            BlockRange initRange = build_stmt_list(
                ctx, stmt->u.for_stmt.init, current
            );

            BasicBlockId condId = initRange.exit;
            BasicBlock *condBlock = cfg_get_block(cfg, condId);

            cfg_append_operation(condBlock, stmt->op); /* cond */
            stmt->op = NULL;

            BasicBlockId bodyId = cfg_new_block(cfg);
            BasicBlockId stepId = cfg_new_block(cfg);
            BasicBlockId afterId = cfg_new_block(cfg);

            condBlock->true_target = bodyId;
            condBlock->false_target = afterId;

            push_break(ctx, afterId);
            push_continue(ctx, stepId);

            /* тело */
            BlockRange bodyRange = build_stmt_list(
                ctx, stmt->u.for_stmt.body, bodyId
            );

            /* если из тела не было безусловного выхода — идём в step */
            BasicBlock *bodyExit = cfg_get_block(cfg, bodyRange.exit);
            if (!bodyExit->terminated_by_jump &&
                bodyExit->next == CFG_INVALID_BLOCK &&
                !bodyExit->is_exit) {
                bodyExit->next = stepId;
            }

            /* шаг */
            BlockRange stepRange = build_stmt_list(
                ctx, stmt->u.for_stmt.step, stepId
            );

            pop_break(ctx);
            pop_continue(ctx);

            BasicBlock *stepExit = cfg_get_block(cfg, stepRange.exit);
            if (!stepExit->terminated_by_jump &&
                stepExit->next == CFG_INVALID_BLOCK &&
                !stepExit->is_exit) {
                stepExit->next = condId;
            }

            r.entry = initRange.entry;
            r.exit = afterId;
            return r;
        }

        case CFG_STMT_BREAK: {
            cfg_append_operation(curBlock, stmt->op);
            stmt->op = NULL;

            BasicBlockId target = current_break_target(ctx);
            if (target == CFG_INVALID_BLOCK) {
                add_error(ctx->result, "break вне цикла", stmt->loc);
            } else {
                curBlock->next = target;
                curBlock->terminated_by_jump = 1;
            }
            return r;
        }

        case CFG_STMT_CONTINUE: {
            cfg_append_operation(curBlock, stmt->op);
            stmt->op = NULL;

            BasicBlockId target = current_continue_target(ctx);
            if (target == CFG_INVALID_BLOCK) {
                add_error(ctx->result, "continue вне цикла", stmt->loc);
            } else {
                curBlock->next = target;
                curBlock->terminated_by_jump = 1;
            }
            return r;
        }

        case CFG_STMT_RETURN: {
            cfg_append_operation(curBlock, stmt->op);
            stmt->op = NULL;

            if (cfg->exit != CFG_INVALID_BLOCK) {
                curBlock->next = cfg->exit;
            }
            curBlock->terminated_by_jump = 1;
            return r;
        }
    }

    return r;
}

/* ---------- Построение CFG одной функции ---------- */

ControlFlowGraph cfg_build_function_cfg(const CfgFunctionAst *func_ast,
                                        CfgModuleResult *result) {
    ControlFlowGraph cfg;
    memset(&cfg, 0, sizeof(cfg));

    cfg.function_name = func_ast->signature.name;
    cfg.blocks = NULL;
    cfg.block_count = 0;
    cfg.block_capacity = 0;
    cfg.entry = CFG_INVALID_BLOCK;
    cfg.exit = CFG_INVALID_BLOCK;

    /* entry и exit */
    BasicBlockId entryId = cfg_new_block(&cfg);
    BasicBlockId exitId = cfg_new_block(&cfg);

    cfg.entry = entryId;
    cfg.exit = exitId;

    BasicBlock *entryBlock = cfg_get_block(&cfg, entryId);
    BasicBlock *exitBlock = cfg_get_block(&cfg, exitId);

    entryBlock->is_entry = 1;
    exitBlock->is_exit = 1;

    CfgBuildContext ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.cfg = &cfg;
    ctx.result = result;

    BlockRange bodyRange = build_stmt_list(
        &ctx, func_ast->body, entryId
    );

    /* если последний блок не заканчивается явным переходом — ведём в exit */
    BasicBlock *last = cfg_get_block(&cfg, bodyRange.exit);
    if (!last->terminated_by_jump &&
        last->next == CFG_INVALID_BLOCK &&
        !last->is_exit) {
        last->next = exitId;
    }

    free(ctx.break_targets);
    free(ctx.cont_targets);

    return cfg;
}

/* ---------- Группировка по файлам и граф вызовов ---------- */

static FileInfo *find_or_add_file(ProgramInfo *prog, const char *path) {
    for (size_t i = 0; i < prog->file_count; ++i) {
        if (strcmp(prog->files[i].path, path) == 0)
            return &prog->files[i];
    }

    if (prog->file_count == prog->file_capacity) {
        size_t new_cap = prog->file_capacity ? prog->file_capacity * 2 : 4;
        FileInfo *arr = (FileInfo *) realloc(
            prog->files,
            new_cap * sizeof(FileInfo)
        );
        if (!arr) {
            fprintf(stderr, "Out of memory in find_or_add_file\n");
            exit(1);
        }
        prog->files = arr;
        prog->file_capacity = new_cap;
    }

    FileInfo *fi = &prog->files[prog->file_count++];
    memset(fi, 0, sizeof(*fi));
    fi->path = (char *) path; /* указатель, не копируем; при желании можно сделать strdup */
    return fi;
}

static FunctionInfo *append_function(FileInfo *fi) {
    if (fi->func_count == fi->func_capacity) {
        size_t new_cap = fi->func_capacity ? fi->func_capacity * 2 : 4;
        FunctionInfo *arr = (FunctionInfo *) realloc(
            fi->functions,
            new_cap * sizeof(FunctionInfo)
        );
        if (!arr) {
            fprintf(stderr, "Out of memory in append_function\n");
            exit(1);
        }
        fi->functions = arr;
        fi->func_capacity = new_cap;
    }

    FunctionInfo *f = &fi->functions[fi->func_count++];
    memset(f, 0, sizeof(*f));
    return f;
}

/* --- Граф вызовов --- */

static void call_graph_add_function(CallGraph *cg, const char *name) {
    for (size_t i = 0; i < cg->func_count; ++i) {
        if (strcmp(cg->functions[i], name) == 0)
            return;
    }

    if (cg->func_count == cg->func_capacity) {
        size_t new_cap = cg->func_capacity ? cg->func_capacity * 2 : 4;
        char **arr = (char **) realloc(
            cg->functions,
            new_cap * sizeof(char *)
        );
        if (!arr) {
            fprintf(stderr, "Out of memory in call_graph_add_function\n");
            exit(1);
        }
        cg->functions = arr;
        cg->func_capacity = new_cap;
    }

    cg->functions[cg->func_count++] = cfg_strdup(name);
}

static int edge_exists(CallGraph *cg, const char *caller, const char *callee) {
    for (size_t i = 0; i < cg->edge_count; ++i) {
        if (strcmp(cg->edges[i].caller, caller) == 0 &&
            strcmp(cg->edges[i].callee, callee) == 0)
            return 1;
    }
    return 0;
}

static void call_graph_add_edge(CallGraph *cg,
                                const char *caller,
                                const char *callee) {
    if (edge_exists(cg, caller, callee))
        return;

    if (cg->edge_count == cg->edge_capacity) {
        size_t new_cap = cg->edge_capacity ? cg->edge_capacity * 2 : 4;
        CallGraphEdge *arr = (CallGraphEdge *) realloc(
            cg->edges,
            new_cap * sizeof(CallGraphEdge)
        );
        if (!arr) {
            fprintf(stderr, "Out of memory in call_graph_add_edge\n");
            exit(1);
        }
        cg->edges = arr;
        cg->edge_capacity = new_cap;
    }

    CallGraphEdge *e = &cg->edges[cg->edge_count++];
    e->caller = cfg_strdup(caller);
    e->callee = cfg_strdup(callee);
}

/* рекурсивный обход дерева операций для поиска вызовов */
static void collect_calls_from_tree(const OperationTreeNode *node,
                                    const char *current_func,
                                    CallGraph *cg) {
    if (!node) return;

    if (node->operation.kind == OP_CALL) {
        const char *callee = NULL;

        if (node->operation.op && node->operation.op[0] != '\0') {
            callee = node->operation.op;
        } else if (node->operation.operand_count > 0 &&
                   node->operation.operands[0].text) {
            callee = node->operation.operands[0].text;
        }

        if (callee) {
            call_graph_add_function(cg, current_func);
            call_graph_add_function(cg, callee);
            call_graph_add_edge(cg, current_func, callee);
        }
    }

    for (size_t i = 0; i < node->child_count; ++i) {
        collect_calls_from_tree(node->children[i], current_func, cg);
    }
}

/* ---------- Построение CFG для всей программы ---------- */

void cfg_build_program(const CfgFunctionAst *funcs,
                       size_t func_count,
                       CfgModuleResult *result) {
    cfg_module_result_init(result);

    for (size_t i = 0; i < func_count; ++i) {
        const CfgFunctionAst *fAst = &funcs[i];

        ControlFlowGraph cfg = cfg_build_function_cfg(fAst, result);

        FileInfo *fi = find_or_add_file(&result->program, fAst->source_file);
        FunctionInfo *f = append_function(fi);

        f->signature = fAst->signature; /* поверхностная копия: строки не копируем */
        f->cfg = cfg;
        f->source_file = fAst->source_file;
    }

    /* Граф вызовов */
    for (size_t i = 0; i < result->program.file_count; ++i) {
        FileInfo *fi = &result->program.files[i];
        for (size_t j = 0; j < fi->func_count; ++j) {
            FunctionInfo *f = &fi->functions[j];
            const char *fname = f->signature.name;

            for (size_t b = 0; b < f->cfg.block_count; ++b) {
                BasicBlock *bb = &f->cfg.blocks[b];
                for (size_t k = 0; k < bb->op_count; ++k) {
                    OperationTree tree = bb->operations[k];
                    collect_calls_from_tree(tree, fname, &result->call_graph);
                }
            }
        }
    }
}
