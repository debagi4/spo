//
// Created by Герман Багдасарян on 02.10.2025.
//

#ifndef SPO_AST_H
#define SPO_AST_H

/* forward declaration – opaque type */
typedef struct Node Node;

/* функции создания узлов (публичный API) */
Node *node_new(const char *type, const char *value);

void node_add_child(Node *parent, Node *child);

/* функция освобождения всего дерева */
void node_free(Node *root);

/* сериализация в DGML – возвращает строку (должна быть освобождена) */
char *ast_to_dgml(const Node *root);

#endif //SPO_AST_H
