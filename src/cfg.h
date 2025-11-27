//
// Created by Герман Багдасарян on 27.11.2025.
//

#ifndef SPO_CFG_H
#define SPO_CFG_H

#include <stddef.h>

#define CFG_INVALID_BLOCK (-1)

/* --- Положение в исходнике и ошибки анализа --- */

typedef struct {
    const char* file;
    size_t line;
    size_t column;
} SourceLocation;

typedef struct {
    char* message;      /* текст ошибки (выделяем через malloc/strdup) */
    SourceLocation loc;
} AnalyzerError;

/* --- Дерево операций (адаптируй к структурам из задания 1 при желании) --- */

typedef enum {
    OP_UNKNOWN,
    OP_ASSIGN,
    OP_BINARY,
    OP_UNARY,
    OP_CALL,
    OP_RETURN,
    OP_BRANCH_COND,
    OP_JUMP
} OperationKind;

typedef struct Operand {
    char* text;
    SourceLocation loc;
} Operand;

typedef struct Operation {
    OperationKind kind;
    char* op;              /* имя операции / функции / оператора */
    Operand* operands;
    size_t operand_count;
    SourceLocation loc;
} Operation;

typedef struct OperationTreeNode {
    Operation operation;
    struct OperationTreeNode** children;
    size_t child_count;
} OperationTreeNode;

typedef OperationTreeNode* OperationTree;

/* --- CFG: базовые блоки и граф --- */

typedef int BasicBlockId;

typedef struct BasicBlock {
    BasicBlockId id;

    OperationTree* operations;
    size_t op_count;
    size_t op_capacity;

    BasicBlockId next;        /* обычный переход / fall-through */
    BasicBlockId true_target; /* для условных переходов */
    BasicBlockId false_target;

    int is_entry;
    int is_exit;
    int terminated_by_jump;   /* return / break / continue / goto */
} BasicBlock;

typedef struct ControlFlowGraph {
    char* function_name;   /* не владеем строкой: используем указатель из AST */

    BasicBlock* blocks;
    size_t block_count;
    size_t block_capacity;

    BasicBlockId entry;
    BasicBlockId exit;     /* CFG_INVALID_BLOCK если нет явного exit */
} ControlFlowGraph;

/* --- Информация о функциях и файлах --- */

typedef struct {
    char* name;
    char** parameters;
    size_t param_count;
    char* return_type;
} FunctionSignature;

typedef struct {
    FunctionSignature signature;
    ControlFlowGraph cfg;
    char* source_file;      /* путь к файлу с определением */
} FunctionInfo;

typedef struct {
    char* path;
    FunctionInfo* functions;
    size_t func_count;
    size_t func_capacity;
} FileInfo;

typedef struct {
    FileInfo* files;
    size_t file_count;
    size_t file_capacity;
} ProgramInfo;

/* --- Граф вызовов --- */

typedef struct {
    char* caller;
    char* callee;
} CallGraphEdge;

typedef struct {
    char** functions;
    size_t func_count;
    size_t func_capacity;

    CallGraphEdge* edges;
    size_t edge_count;
    size_t edge_capacity;
} CallGraph;

/* --- Итог работы модуля CFG --- */

typedef struct {
    ProgramInfo program;
    CallGraph call_graph;

    AnalyzerError* errors;
    size_t error_count;
    size_t error_capacity;
} CfgModuleResult;

/* --- Промежуточное представление операторов для CFG --- */

typedef enum {
    CFG_STMT_SIMPLE,    /* простое выражение / присваивание / вызов */
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
    OperationTree op;     /* выражение: условие, return-выражение или само выражение */

    CfgStmt* next;        /* следующий оператор в последовательности */

    union {
        struct {
            CfgStmt* then_branch;  /* список операторов в then (односвязный список) */
            CfgStmt* else_branch;  /* список операторов в else */
        } if_stmt;
        struct {
            CfgStmt* body;         /* тело while */
        } while_stmt;
        struct {
            CfgStmt* body;         /* тело do..while */
        } do_while_stmt;
        struct {
            CfgStmt* init;         /* список операторов-инициализаций */
            CfgStmt* body;         /* тело цикла */
            CfgStmt* step;         /* список операторов шага */
        } for_stmt;
    } u;
};

typedef struct {
    FunctionSignature signature;
    char* source_file;
    CfgStmt* body;        /* первый оператор функции (односвязный список) */
} CfgFunctionAst;


/* Инициализация / освобождение результата модуля */
void cfg_module_result_init(CfgModuleResult* r);
void cfg_module_result_free(CfgModuleResult* r);

/* Построение CFG одной функции */
ControlFlowGraph cfg_build_function_cfg(const CfgFunctionAst* func_ast,
                                        CfgModuleResult* result);

/* Построение CFG всего набора функций + граф вызовов */
void cfg_build_program(const CfgFunctionAst* funcs,
                       size_t func_count,
                       CfgModuleResult* result);

/* Вывод CFG и графа вызовов в DGML */
int dgml_write_cfg(const ControlFlowGraph* cfg, const char* path);
int dgml_write_call_graph(const CallGraph* cg, const char* path);

#endif //SPO_CFG_H