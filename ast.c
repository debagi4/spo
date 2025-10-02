//
// Created by Герман Багдасарян on 02.10.2025.
//

#include <stdlib.h>
#include <string.h>
#include "ast.h"

#include <stdio.h>

/* внутреннее представление узла */
struct Node {
    char *type; /* тип узла, например "funcDef", "var", "expr" */
    char *value; /* текстовое содержимое (если есть) */
    struct Node **children;
    size_t n_children, capacity;
};

/* вспомогательная функция «растягивания» массива */
static void node_grow(Node *node) {
    if (node->n_children == node->capacity) {
        size_t new_cap = node->capacity ? 2 * node->capacity : 4;
        node->children = realloc(node->children,
                                 new_cap * sizeof(Node *));
        node->capacity = new_cap;
    }
}

Node *node_new(const char *type, const char *value) {
    Node *n = calloc(1, sizeof(Node));
    n->type = strdup(type);
    n->value = value ? strdup(value) : NULL;
    return n;
}

void node_add_child(Node *parent, Node *child) {
    if (!parent || !child) return;
    node_grow(parent);
    parent->children[parent->n_children++] = child;
}

void node_free(Node *root) {
    if (!root) return;
    for (size_t i = 0; i < root->n_children; ++i)
        node_free(root->children[i]);
    free(root->type);
    free(root->value);
    free(root->children);
    free(root);
}

/* --------------------------------------------------------------------- */
/* простая сериализация в DGML – для демонстрации */
static void dgml_write_node(FILE *f, const Node *n, int depth) {
    /* indent */
    for (int i = 0; i < depth; ++i) fprintf(f, "  ");

    /* узел (Node) */
    if (n->value)
        fprintf(f, "<Node Id=\"%s\" Label=\"%s:%s\" />\n",
                n->type, n->type, n->value);
    else
        fprintf(f, "<Node Id=\"%s\" Label=\"%s\" />\n",
                n->type, n->type);

    /* связи к потомкам */
    for (size_t i = 0; i < n->n_children; ++i) {
        /* indent */
        for (int j = 0; j < depth + 1; ++j) fprintf(f, "  ");
        fprintf(f, "<Link Source=\"%s\" Target=\"%s\" />\n",
                n->type, n->children[i]->type);
        dgml_write_node(f, n->children[i], depth + 1);
    }
}

char *ast_to_dgml(const Node *root) {
    /* в реальном коде лучше использовать поток, но для простоты – строка */
    char *buf = NULL;
    size_t sz = 0;

    FILE *tmp = open_memstream(&buf, &sz);
    if (!tmp) return NULL;

    fprintf(tmp, "<DirectedGraph xmlns=\"http://schemas.microsoft.com/vs/2009/dgml\">\n");
    fprintf(tmp, "  <Nodes>\n");
    dgml_write_node(tmp, root, 2);
    fprintf(tmp, "  </Nodes>\n");
    fprintf(tmp, "</DirectedGraph>\n");

    fclose(tmp);
    return buf;
}
