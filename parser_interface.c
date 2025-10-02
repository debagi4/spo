#include "parser_interface.h"
#include <stdio.h>

extern FILE *yyin;

extern int yyparse(void);

extern Node *ast_root;

Node *parse_file_to_ast(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        return NULL;
    }

    yyin = f;
    ast_root = NULL;

    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed for file: %s\n", filename);
        fclose(f);
        return NULL;
    }

    fclose(f);
    return ast_root;
}
