#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "dgml_writer.h"

extern Node *parse_file_to_ast(const char *filename);

int main(int argc, char **argv) {
    const char *in_file = NULL;
    const char *out_file = NULL;

    /* Обработка аргументов командной строки */
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-o") && i + 1 < argc) {
            out_file = argv[++i];
        } else if (argv[i][0] != '-') {
            in_file = argv[i];
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            fprintf(stderr, "Usage: %s <input> [-o <output.dgml>]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (!in_file) {
        fprintf(stderr, "Usage: %s <input> [-o <output.dgml>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Парсим файл и строим AST */
    Node *root = parse_file_to_ast(in_file);
    if (!root) {
        fprintf(stderr, "Failed to parse file: %s\n", in_file);
        return EXIT_FAILURE;
    }

    /* Определяем имя выходного файла */
    char *dynamic_out_file = NULL;
    if (!out_file) {
        size_t len = strlen(in_file);
        dynamic_out_file = malloc(len + 6);
        if (!dynamic_out_file) {
            perror("malloc");
            node_free(root);
            return EXIT_FAILURE;
        }
        strcpy(dynamic_out_file, in_file);
        strcat(dynamic_out_file, ".dgml");
        out_file = dynamic_out_file;
    }

    /* Записываем DGML */
    if (write_dgml_file(out_file, root) != 0) {
        fprintf(stderr, "Failed to write DGML to: %s\n", out_file);
        node_free(root);
        if (dynamic_out_file) free(dynamic_out_file);
        return EXIT_FAILURE;
    }

    printf("Successfully parsed %s and wrote DGML to %s\n", in_file, out_file);

    /* Освобождаем ресурсы */
    node_free(root);
    if (dynamic_out_file) free(dynamic_out_file);

    return EXIT_SUCCESS;
}
