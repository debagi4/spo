//
// Created by Герман Багдасарян on 26.11.2025.
//

#ifndef SPO_EXECUTION_H
#define SPO_EXECUTION_H

typedef struct FilenameParseTree FilenameParseTree;
typedef struct ExecutionNode ExecutionNode;
typedef struct FunExecution FunExecution;
typedef struct Array Array;

#include "stdio.h"
#include "Tree.h"
#include "parse_wrapper.h"

struct ExecutionNode {
    char *text;
    ExecutionNode *definitely;
    ExecutionNode *conditionally;
    Tree *operationTree;
    int id;
    int printed;
};

struct Array {
    int size;
    int nextPosition;
    void **elements;
};

struct FunExecution {
    char *name;
    char *filename;
    Tree *signature;
    Tree *funCalls;
    ExecutionNode *nodes;
    char **errors;
    int errorsCount;
};

struct FilenameParseTree {
    char *filename;
    ParseResult *tree;
};


Array *executionGraph(const FilenameParseTree *input, int size);

void printExecution(FunExecution *funExecution, FILE *outputFunCallFile, FILE *outputOperationTreesFile,
                    FILE *outputExecutionFile);


#endif //SPO_EXECUTION_H