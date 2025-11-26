#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tree {
    int id;
    char* type;
    char* value;
    struct Tree** children;
    int child_count;
} Tree;

Tree* create_node(const char* type, const char* value);
void add_child(Tree* parent, Tree* child);
void free_tree(Tree* node);

#ifdef __cplusplus
}
#endif

#endif