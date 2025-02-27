#include "tree.h"

node_t* create_tree(){
    return create_node(0, NULL, NULL, NULL);
}

node_t* create_node(int value, node_t* left, node_t* right, node_t* parent){
    node_t* node = (node_t*) malloc(sizeof(node_t));
    
    node->value = value;
    node->left = left;
    node->right = right;
    node->parent = parent;

    return node;
}

void destroy_tree(node_t* root){
    if(root == NULL){
        return;
    }

    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

