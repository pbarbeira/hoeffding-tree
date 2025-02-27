#ifndef TREE_H_
#define TREE_H_

#include <stdlib.h>

typedef struct node_t{
    struct node_t* left;
    struct node_t* right;
    struct node_t* parent;
    int value;
}node_t;

node_t* create_tree();

node_t* create_node(int value, node_t* left, node_t* right, node_t* parent);

void destroy_tree(node_t* root);

#endif //TREE_H_
