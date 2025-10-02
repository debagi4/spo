//
// Created by Герман Багдасарян on 02.10.2025.
//
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

int write_dgml_file(const char *path, const Node *root) {
    char *dgml = ast_to_dgml(root);
    if (!dgml) return -1;

    FILE *f = fopen(path, "w");
    if (!f) {
        free(dgml);
        return -1;
    }

    fputs(dgml, f);
    fclose(f);
    free(dgml);
    return 0;
}
