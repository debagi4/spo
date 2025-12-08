#include "dgml_writer.h"
#include "Tree.h"
#include "cfg.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* xml_escape(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char* buf = (char*)malloc(len * 6 + 1);
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

static void write_dgml_header(FILE* f) {
    fprintf(f, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    fprintf(f, "<DirectedGraph xmlns=\"http://schemas.microsoft.com/vs/2009/dgml\">\n");
}

static void write_dgml_footer(FILE* f) {
    fprintf(f, "</DirectedGraph>\n");
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

int dgml_write_cfg(const ControlFlowGraph* cfg, const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) return -1;

    write_dgml_header(f);

    fprintf(f, "  <Nodes>\n");
    for (size_t i = 0; i < cfg->block_count; ++i) {
        const BasicBlock* bb = &cfg->blocks[i];
        char id[32];
        snprintf(id, sizeof(id), "B%d", bb->id);

        char label[64];
        snprintf(label, sizeof(label), "%s%s%s",
                 id,
                 bb->is_entry ? " (entry)" : "",
                 bb->is_exit  ? " (exit)"  : "");

        fprintf(f, "    <Node Id=\"%s\" Label=\"%s\" />\n", id, label);
    }
    fprintf(f, "  </Nodes>\n");

    fprintf(f, "  <Links>\n");
    for (size_t i = 0; i < cfg->block_count; ++i) {
        const BasicBlock* bb = &cfg->blocks[i];
        char src[32];
        snprintf(src, sizeof(src), "B%d", bb->id);

        if (bb->next != CFG_INVALID_BLOCK) {
            char dst[32];
            snprintf(dst, sizeof(dst), "B%d", bb->next);
            fprintf(f, "    <Link Source=\"%s\" Target=\"%s\" Label=\"next\" />\n",
                    src, dst);
        }
        if (bb->true_target != CFG_INVALID_BLOCK) {
            char dst[32];
            snprintf(dst, sizeof(dst), "B%d", bb->true_target);
            fprintf(f, "    <Link Source=\"%s\" Target=\"%s\" Label=\"true\" />\n",
                    src, dst);
        }
        if (bb->false_target != CFG_INVALID_BLOCK) {
            char dst[32];
            snprintf(dst, sizeof(dst), "B%d", bb->false_target);
            fprintf(f, "    <Link Source=\"%s\" Target=\"%s\" Label=\"false\" />\n",
                    src, dst);
        }
    }
    fprintf(f, "  </Links>\n");

    write_dgml_footer(f);
    fclose(f);
    return 0;
}

int dgml_write_call_graph(const CallGraph* cg, const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) return -1;

    write_dgml_header(f);

    fprintf(f, "  <Nodes>\n");
    for (size_t i = 0; i < cg->func_count; ++i) {
        const char* name = cg->functions[i];
        fprintf(f, "    <Node Id=\"%s\" Label=\"%s\" />\n", name, name);
    }
    fprintf(f, "  </Nodes>\n");

    fprintf(f, "  <Links>\n");
    for (size_t i = 0; i < cg->edge_count; ++i) {
        const CallGraphEdge* e = &cg->edges[i];
        fprintf(f, "    <Link Source=\"%s\" Target=\"%s\" />\n",
                e->caller, e->callee);
    }
    fprintf(f, "  </Links>\n");

    write_dgml_footer(f);
    fclose(f);
    return 0;
}
