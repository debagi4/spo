#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <libgen.h>
#include "Tree.h"
#include "dgml_writer.h"
#include "execution.h"
#include "parse_wrapper.h"

// Объявляем функцию из C++ обёртки
ParseResult *parse(const char *inp);

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <outputDir> <input> [<input>]\n", argv[0]);
        return 1;
    }

    DIR *outputDir = opendir(argv[1]);
    if (!outputDir) {
        fprintf(stderr, "Output dir %s doesn't exists\n", argv[1]);
        return 1;
    }
    closedir(outputDir);

    for (int i = 2; i < argc; ++i) {
        char *filename = basename(argv[i]);
        fprintf(stdout, "Filename: %s\n", filename);

        FILE *in = fopen(argv[i], "r");
        if (!in) {
            fprintf(stderr, "Cannot open file: %s\n", argv[i]);
            continue;
        }

        char outputParseTreeFileName[1024];
        sprintf(outputParseTreeFileName, "%s/%s-parse-tree.txt", argv[1], basename(filename));

        fseek(in, 0,SEEK_END);
        const long len = ftell(in);
        fseek(in, 0,SEEK_SET);

        char *buffer = (char *) malloc(len + 1);
        fread(buffer, 1, len, in);
        buffer[len] = 0;
        fclose(in);

        ParseResult *root = parse(buffer);
        if (root) {
            write_dgml(root->tree, outputParseTreeFileName);
        } else {
            fprintf(stderr, "Parsing failed\n");
            free(buffer);
            continue;
        }
        free(buffer);

        Array *executionRes =
                executionGraph(&(FilenameParseTree) {filename, root}, 1);
        for (int j = 0; j < root->errorsCount; ++j) {
            fprintf(stderr, "%s", root->errors[j]);
        }

        for (int j = 0; j < executionRes->nextPosition; ++j) {
            FunExecution *funExecution = executionRes->elements[j];

            for (int k = 0; k < funExecution->errorsCount; ++k) {
                fprintf(stderr, "%s", funExecution->errors[k]);
            }
        }
        for (int j = 0; j < executionRes->nextPosition; ++j) {
            FunExecution *funExecution = executionRes->elements[j];

            char outputFunCallFileName[1024];
            sprintf(outputFunCallFileName, "%s/%s.%s.ext-fun-call.txt", argv[1], basename(funExecution->filename),
                    funExecution->name);
            FILE *outputFunCallFile = fopen(outputFunCallFileName, "w");
            char outputOperationTreesFileName[1024];
            sprintf(outputOperationTreesFileName, "%s/%s.%s.ext-operation-tree.txt", argv[1],
                    basename(funExecution->filename), funExecution->name);
            FILE *outputOperationTreesFile = fopen(outputOperationTreesFileName, "w");
            char outputExecutionFileName[1024];
            sprintf(outputExecutionFileName, "%s/%s.%s.ext", argv[1],
                    basename(funExecution->filename), funExecution->name);
            FILE *outputExecutionFile = fopen(outputExecutionFileName, "w");

            printExecution(funExecution, outputFunCallFile, outputOperationTreesFile, outputExecutionFile);

            fclose(outputFunCallFile);
            fclose(outputOperationTreesFile);
            fclose(outputExecutionFile);
        }
        free_tree(root->tree);
    }

    return 0;
}
