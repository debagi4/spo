//
// Created by Герман Багдасарян on 27.11.2025.
//

#ifndef SPO_PARSE_WRAPPER_H
#define SPO_PARSE_WRAPPER_H
#include "Tree.h"

typedef struct ParseResult {
    int size;
    Tree **nodes;
    Tree *tree;
    char** errors;
    int errorsCount;
} ParseResult;

#endif //SPO_PARSE_WRAPPER_H