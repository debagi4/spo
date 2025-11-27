//
// Created by Герман Багдасарян on 27.11.2025.
//

#ifndef SPO_DOT_WRITER_H
#define SPO_DOT_WRITER_H

#include "cfg.h"

/* Записать CFG одной функции в .dot (Graphviz) */
int dot_write_cfg(const ControlFlowGraph* cfg, const char* path);

/* Записать граф вызовов в .dot */
int dot_write_call_graph(const CallGraph* cg, const char* path);

#endif //SPO_DOT_WRITER_H