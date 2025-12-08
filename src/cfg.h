//
// Created by Герман Багдасарян on 27.11.2025.
//

#ifndef SPO_CFG_H
#define SPO_CFG_H

#include <stddef.h>

#define CFG_INVALID_BLOCK (-1)


typedef struct {
    const char *file;
    size_t line;
    size_t column;
} SourceLocation;

typedef struct {
    char *message;
    SourceLocation loc;
} AnalyzerError;

typedef enum {
    OP_UNKNOWN,
    OP_ASSIGN,
    OP_CALL,
    OP_RETURN,
    OP_BRANCH_COND
} OperationKind;

typedef struct Operand {
    char *text;
    SourceLocation loc;
} Operand;

typedef struct Operation {
    OperationKind kind;
    char *op;
    Operand *operands;
    size_t operand_count;
    SourceLocation loc;
} Operation;

typedef struct OperationTreeNode {
    Operation operation;
    struct OperationTreeNode **children;
    size_t child_count;
} OperationTreeNode;

typedef OperationTreeNode *OperationTree;

typedef int BasicBlockId;

typedef struct BasicBlock {
    BasicBlockId id;

    OperationTree *operations;
    size_t op_count;
    size_t op_capacity;

    BasicBlockId next;
    BasicBlockId true_target;
    BasicBlockId false_target;

    int is_entry;
    int is_exit;
    int terminated_by_jump;
} BasicBlock;

typedef struct ControlFlowGraph {
    char *function_name;

    BasicBlock *blocks;
    size_t block_count;
    size_t block_capacity;

    BasicBlockId entry;
    BasicBlockId exit;
} ControlFlowGraph;


typedef struct {
    char *name;
    char **parameters;
    size_t param_count;
    char *return_type;
} FunctionSignature;

typedef struct {
    FunctionSignature signature;
    ControlFlowGraph cfg;
    char *source_file;
} FunctionInfo;

typedef struct {
    char *path;
    FunctionInfo *functions;
    size_t func_count;
    size_t func_capacity;
} FileInfo;

typedef struct {
    FileInfo *files;
    size_t file_count;
    size_t file_capacity;
} ProgramInfo;


typedef struct {
    char *caller;
    char *callee;
} CallGraphEdge;

typedef struct {
    char **functions;
    size_t func_count;
    size_t func_capacity;

    CallGraphEdge *edges;
    size_t edge_count;
    size_t edge_capacity;
} CallGraph;


typedef struct {
    ProgramInfo program;
    CallGraph call_graph;

    AnalyzerError *errors;
    size_t error_count;
    size_t error_capacity;
} CfgModuleResult;


typedef enum {
    CFG_STMT_SIMPLE,
    CFG_STMT_IF,
    CFG_STMT_WHILE,
    CFG_STMT_DO_WHILE,
    CFG_STMT_FOR,
    CFG_STMT_BREAK,
    CFG_STMT_CONTINUE,
    CFG_STMT_RETURN
} CfgStmtKind;

typedef struct CfgStmt CfgStmt;

struct CfgStmt {
    CfgStmtKind kind;
    SourceLocation loc;
    OperationTree op;

    CfgStmt *next;

    union {
        struct {
            CfgStmt *then_branch;
            CfgStmt *else_branch;
        } if_stmt;

        struct {
            CfgStmt *body;
        } while_stmt;

        struct {
            CfgStmt *body;
        } do_while_stmt;

        struct {
            CfgStmt *init;
            CfgStmt *body;
            CfgStmt *step;
        } for_stmt;
    } u;
};

typedef struct {
    FunctionSignature signature;
    char *source_file;
    CfgStmt *body;
} CfgFunctionAst;


void cfg_module_result_init(CfgModuleResult *r);

void cfg_module_result_free(CfgModuleResult *r);

ControlFlowGraph cfg_build_function_cfg(const CfgFunctionAst *func_ast,
                                        CfgModuleResult *result);

void cfg_build_program(const CfgFunctionAst *funcs,
                       size_t func_count,
                       CfgModuleResult *result);

int dgml_write_cfg(const ControlFlowGraph *cfg, const char *path);

int dgml_write_call_graph(const CallGraph *cg, const char *path);

#endif //SPO_CFG_H
