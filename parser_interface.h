// parser_interface.h
#ifndef SPO_PARSER_INTERFACE_H
#define SPO_PARSER_INTERFACE_H

#include "ast.h"

/* Функция для парсинга файла и построения AST */
Node *parse_file_to_ast(const char *filename);

#endif //SPO_PARSER_INTERFACE_H
