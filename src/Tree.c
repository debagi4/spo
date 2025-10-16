#include <stdlib.h>
#include <string.h>
#include "Tree.h"

Tree* create_node(const char* type, const char* value) {
    Tree* node = (Tree*)malloc(sizeof(Tree));
    node->type = strdup(type);
    node->value = value ? strdup(value) : NULL;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

void add_child(Tree* parent, Tree* child) {
    parent->children = (Tree**)realloc(parent->children, sizeof(Tree*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = child;
}

void free_tree(Tree* node) {
    if(!node) return;
    free(node->type);
    if(node->value) free(node->value);
    for(int i=0;i<node->child_count;i++)
        free_tree(node->children[i]);
    free(node->children);
    free(node);
}