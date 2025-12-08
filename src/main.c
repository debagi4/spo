#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <libgen.h>
#include <string.h>

#include "Tree.h"
#include "dgml_writer.h"
#include "parse_wrapper.h"
#include "cfg.h"
#include "cfg_from_tree.h"
#include "dot_writer.h"

ParseResult *parse(const char *inp);

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <outputDir> <input> [<input>]\n", argv[0]);
        return 1;
    }

    const char* outputDirPath = argv[1];

    DIR *outputDir = opendir(outputDirPath);
    if (!outputDir) {
        fprintf(stderr, "Output dir %s doesn't exists\n", outputDirPath);
        return 1;
    }
    closedir(outputDir);

    /* Собираем все функции всех файлов */
    CfgFunctionAst* all_funcs = NULL;
    size_t all_count = 0;
    size_t all_capacity = 0;

    for (int i = 2; i < argc; ++i) {
        char *filename = basename(argv[i]);
        fprintf(stdout, "Filename: %s\n", filename);

        FILE *in = fopen(argv[i], "r");
        if (!in) {
            fprintf(stderr, "Cannot open file: %s\n", argv[i]);
            continue;
        }

        char outputParseTreeFileName[1024];
        sprintf(outputParseTreeFileName, "%s/%s-parse-tree.dgml",
                outputDirPath, basename(filename));

        fseek(in, 0,SEEK_END);
        const long len = ftell(in);
        fseek(in, 0,SEEK_SET);

        char *buffer = (char *) malloc(len + 1);
        if (!buffer) {
            fprintf(stderr, "Out of memory\n");
            fclose(in);
            return 1;
        }
        fread(buffer, 1, len, in);
        buffer[len] = 0;
        fclose(in);

        ParseResult *root = parse(buffer);
        if (!root) {
            fprintf(stderr, "Parsing failed: %s\n", argv[i]);
            free(buffer);
            continue;
        }

        /* Вывод AST в DGML (задание 1) */
        write_dgml(root->tree, outputParseTreeFileName);

        /* Сообщения об ошибках парсинга (если есть) */
        for (int e = 0; e < root->errorsCount; ++e) {
            fprintf(stderr, "%s\n", root->errors[e]);
        }

        /* Строим CfgFunctionAst для этого файла */
        FileFunctions ff = build_cfg_from_parse_result(argv[i], root);

        if (ff.count > 0) {
            if (all_count + ff.count > all_capacity) {
                size_t new_cap = all_capacity ? all_capacity * 2 : 4;
                while (new_cap < all_count + ff.count)
                    new_cap *= 2;
                CfgFunctionAst* arr = (CfgFunctionAst*)realloc(
                    all_funcs, new_cap * sizeof(CfgFunctionAst)
                );
                if (!arr) {
                    fprintf(stderr, "Out of memory in main (realloc)\n");
                    free(buffer);
                    return 1;
                }
                all_funcs = arr;
                all_capacity = new_cap;
            }

            memcpy(&all_funcs[all_count],
                   ff.funcs,
                   ff.count * sizeof(CfgFunctionAst));
            all_count += ff.count;

            free(ff.funcs); /* сами строки внутри оставляем — ими пользуется CFG */
        }

        free(buffer);
        free_tree(root->tree);
        /* ParseResult* root и его поля мы тут не чистим, утечка некритична для задания */
    }

    if (all_count == 0) {
        fprintf(stderr, "No functions found in input files\n");
        free(all_funcs);
        return 0;
    }

    /* Строим CFG для всех подпрограмм и граф вызовов */
    CfgModuleResult result;
    cfg_build_program(all_funcs, all_count, &result);

    /* Для каждой подпрограммы — файл вида sourceName.functionName.dgml */
    for (size_t i = 0; i < result.program.file_count; ++i) {
        FileInfo* fi = &result.program.files[i];

        char* sourcePath = fi->path;
        char* base = basename(sourcePath);

        for (size_t j = 0; j < fi->func_count; ++j) {
            FunctionInfo* fun = &fi->functions[j];

            const char* funcName =
                fun->signature.name ? fun->signature.name : "func";

            char cfgFileName[1024];
            sprintf(cfgFileName, "%s.%s.dgml", base, funcName);

            char cfgPath[2048];
            sprintf(cfgPath, "%s/%s", outputDirPath, cfgFileName);

            if (dgml_write_cfg(&fun->cfg, cfgPath) != 0) {
                fprintf(stderr, "Cannot write CFG to %s\n", cfgPath);
            }
            /* DOT-версия CFG */
            char dotFileName[1024];
            sprintf(dotFileName, "%s.%s.dot", base, funcName);
            char dotPath[2048];
            sprintf(dotPath, "%s/%s", outputDirPath, dotFileName);

            if (dot_write_cfg(&fun->cfg, dotPath) != 0) {
                fprintf(stderr, "Cannot write DOT CFG to %s\n", dotPath);
            }
        }

        char callPath[1024];
        sprintf(callPath, "%s/%s.callgraph.dgml", outputDirPath, base);
        if (dgml_write_call_graph(&result.call_graph, callPath) != 0) {
            fprintf(stderr, "Cannot write call graph to %s\n", callPath);
        }

        char callDotPath[1024];
        sprintf(callDotPath, "%s/%s.callgraph.dot", outputDirPath, base);
        if (dot_write_call_graph(&result.call_graph, callDotPath) != 0) {
            fprintf(stderr, "Cannot write DOT call graph to %s\n", callDotPath);
        }
    }

    /* Логические ошибки анализа CFG — в stderr */
    for (size_t i = 0; i < result.error_count; ++i) {
        AnalyzerError* e = &result.errors[i];
        fprintf(stderr, "%s:%zu:%zu: %s\n",
                e->loc.file ? e->loc.file : "<unknown>",
                e->loc.line,
                e->loc.column,
                e->message ? e->message : "<no message>");
    }

    cfg_module_result_free(&result);
    free(all_funcs);
    return 0;
}
