#include<stdio.h>
#include<stdlib.h>
#include"avl_header.h"

AVL_TREE* create_avl_tree() {
    AVL_TREE* avl_tree = (AVL_TREE*) malloc(sizeof(AVL_TREE));
    if(avl_tree == NULL) {
        fprintf(stderr, "Error during memory allocation\n");
        exit(EXIT_FAILURE);
    }
    avl_tree->head = NULL;

    return avl_tree;
}

NODE* create_node(int key, NODE* parent) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->info = key;
    new_node->parent = parent;
    new_node->left_child = NULL;
    new_node->right_child = NULL;

    return new_node;
}

void insert_node(AVL_TREE *pl, int key) {
    NODE* x = pl;
    NODE* y = NULL;

    while(x != NULL) {
        y = x;
        if(x->info >= key) {
            x = x->right_child;
        } else if(x->info < key) {
            x = x->left_child;
        }
    }
    NODE* new_node = create_node(key, y);
    new_node->balance_factor = balance_factor(new_node);
    balance_tree(pl);
}
NODE* delete_node(AVL_TREE *pl, int key);
int find_node(AVL_TREE *pl, int key);

void display_tree(AVL_TREE *pl);

void destroy_tree(AVL_TREE *pl);
void destroy_node(NODE *node);

void balance_tree(AVL_TREE *avl_tree);
int balance_factor(NODE *node);