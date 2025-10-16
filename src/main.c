#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
#include "dgml_writer.h"

// Объявляем функцию из C++ обёртки
Tree* parse(const char* inp);

int main(int argc, char** argv) {
    if(argc < 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    if(!in) { perror("fopen"); return 1; }
    fseek(in,0,SEEK_END);
    long len = ftell(in);
    fseek(in,0,SEEK_SET);

    char* buffer = (char*)malloc(len + 1);
    fread(buffer,1,len,in);
    buffer[len]=0;
    fclose(in);

    Tree* root = parse(buffer);
    if(root) {
        write_dgml(root, argv[2]);
        free_tree(root);
    } else {
        fprintf(stderr,"Parsing failed\n");
    }

    free(buffer);
    return 0;
}
