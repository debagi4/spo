#include "dgml_writer.h"
#include <stdio.h>
#include "Tree.h"
#include <string.h>
#include <stdlib.h>

char* xml_escape(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char* buf = (char*)malloc(len * 6 + 1); // максимально на случай замены
    if (!buf) return NULL;
    char* p = buf;
    for (size_t i = 0; i < len; i++) {
        switch (s[i]) {
            case '&': strcpy(p, "&amp;"); p += 5; break;
            case '<': strcpy(p, "&lt;"); p += 4; break;
            case '>': strcpy(p, "&gt;"); p += 4; break;
            case '"': strcpy(p, "&quot;"); p += 6; break;
            case '\'': strcpy(p, "&apos;"); p += 6; break;
            case '\n': strcpy(p, "&#10;"); p += 5; break; // заменяем LF
            case '\r': strcpy(p, "&#13;"); p += 5; break; // заменяем CR
            default: *p++ = s[i]; break;
        }
    }
    *p = '\0';
    return buf;
}

static void write_node(FILE* f, Tree* node, int* id_counter, int parent_id, FILE* link_f) {
    node->id = (*id_counter)++;

    char* value_escaped = "";
    char* tmp = NULL;
    if (node->value && node->child_count == 0) {
        tmp = xml_escape(node->value);
        value_escaped = tmp;
    }

    fprintf(f, "  <Node Id=\"%d\" Label=\"%s : %s\" />\n", node->id, node->type, value_escaped[0] ? value_escaped: "");

    if (parent_id >= 0) {
        fprintf(link_f, "  <Link Source=\"%d\" Target=\"%d\" />\n", parent_id, node->id);
    }

    for (int i = 0; i < node->child_count; i++) {
        write_node(f, node->children[i], id_counter, node->id, link_f);
    }

    if (tmp) free(tmp);
}

void write_dgml(Tree* root, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    fprintf(f, "<DirectedGraph Title=\"AST\" xmlns=\"http://schemas.microsoft.com/vs/2009/dgml\">\n");
    fprintf(f, " <Nodes>\n");

    FILE* link_f = tmpfile(); // временный файл для ссылок
    int counter = 0;
    write_node(f, root, &counter, -1, link_f);

    fprintf(f, " </Nodes>\n <Links>\n");

    fseek(link_f, 0, SEEK_SET);
    char buf[1024];
    while (fgets(buf, sizeof(buf), link_f)) {
        fputs(buf, f);
    }
    fclose(link_f);

    fprintf(f, " </Links>\n</DirectedGraph>\n");
    fclose(f);
}
