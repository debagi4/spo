//
// Created by Герман Багдасарян on 27.11.2025.
//

#ifndef SPO_CFG_FROM_TREE_H
#define SPO_CFG_FROM_TREE_H

#include "cfg.h"
#include "parse_wrapper.h"

/* Набор функций (CfgFunctionAst) из одного исходного файла */
typedef struct {
    CfgFunctionAst* funcs;
    size_t count;
    size_t capacity;
} FileFunctions;

/* Построить CfgFunctionAst по результату парсера (ParseResult) */
FileFunctions build_cfg_from_parse_result(const char* filename,
                                          const ParseResult* pr);

#endif //SPO_CFG_FROM_TREE_H