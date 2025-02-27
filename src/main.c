#include <stdio.h>
#include "visualizer.h"
#include "tree.h"

int main(int argc, char* argv[]){
    node_t* root = create_tree();
    node_t* left = create_node(1, NULL, NULL, root);
    node_t* right = create_node(2, NULL, NULL, root);

    root->left = left;
    root->right = right;

    print_tree(root, "./graphviz/dot/test.dot");

    destroy_tree(root);

	return 0;
}
