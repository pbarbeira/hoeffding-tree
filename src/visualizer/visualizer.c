#include "visualizer.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct sbuff{
    char* buffer;
    size_t length;
    size_t capacity;
}sbuff_t;

void sb_init(sbuff_t* buffer, size_t capacity){
    buffer->length = 0;
    buffer->capacity = capacity;
    buffer->buffer = (char*) malloc(capacity);
}

void sb_increase(sbuff_t* buffer){
    buffer->capacity = 2 * buffer->capacity;
    buffer->buffer = (char*) realloc(buffer->buffer, buffer->capacity);
}

void sb_append(sbuff_t* buffer, const char* str){
    buffer->length += strlen(str);
    if(buffer->length > buffer->capacity){
        sb_increase(buffer);
    }
    buffer->buffer = strcat(buffer->buffer, str);    
}

void free_buffer(sbuff_t* buffer){
    free(buffer->buffer);
    buffer->length = 0;
    buffer->capacity = 0;
}

void generate(char* format, char* filepath){
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "dot -T%s %s -o graphviz/out.%s", format, filepath, format);
    system(cmd);
}

int print_helper(node_t* node, sbuff_t* buffer){
    if(node == NULL || (node->left == NULL && node->right == NULL)){
        return 0;
    }
    
    char tmpStr[64];
    
    snprintf(tmpStr, sizeof(tmpStr), "%d -> { ", node->value);
    
    if(node->left != NULL){
        snprintf(tmpStr + strlen(tmpStr), sizeof(tmpStr), "%d ", node->left->value);
    }
    if(node->right != NULL){
        snprintf(tmpStr + strlen(tmpStr), sizeof(tmpStr), "%d ", node->right->value);
    }
    
    snprintf(tmpStr + strlen(tmpStr), sizeof(tmpStr), "}\n");
    
    sb_append(buffer, tmpStr);
    
    if(print_helper(node->left, buffer)){
        perror("Error printing left subtree\n");
        return 1;
    }
    if(print_helper(node->right, buffer)){
        perror("Error printing rightt subtree\n");
        return 1;
    }
    
    return 0;
}

int print_tree(node_t* tree, char* filepath){
    sbuff_t buffer;
    sb_init(&buffer, 256);

    sb_append(&buffer, "digraph {\n");

    if(print_helper(tree, &buffer)){
        perror("Error parsing tree\n");
        return 1;
    }

    sb_append(&buffer, "}");

    FILE* fptr = fopen(filepath, "w");
    if(!fptr){
        perror("Failed to open file\n");
        return 1;
    }
    fprintf(fptr, "%s", buffer.buffer);

    fclose(fptr);   

    generate("svg", filepath);
    generate("png", filepath);

    return 0;
}
