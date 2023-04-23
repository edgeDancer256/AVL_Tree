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

NODE* create_node(int key) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->info = key;
    new_node->left_child = NULL;
    new_node->right_child = NULL;

    return new_node;
}

void insert_node(AVL_TREE *pl, int key) {
    NODE* x = pl->head;
    NODE* y = NULL;

    if(pl->head == NULL) {
        NODE* new_node = create_node(key);
        pl->head = new_node;
    } else {
        while(x != NULL) {
            y = x;
            if(x->info >= key) {
                x = x->right_child;
            } else if(x->info < key) {
                x = x->left_child;
            }
        }
        NODE* new_node = create_node(key);
        if(key < y->info) y->left_child = new_node;
        if(key > y->info) y->right_child = new_node;
    }
    
    balance_tree(pl);
}
NODE* delete_node(AVL_TREE *pl, int key);


int find_node(AVL_TREE *pl, int key) {
    NODE* curr = pl->head;
    while(curr && curr->info != key) {
        if(key > curr->info) {
            curr = curr->right_child;
        } else {
            curr = curr->left_child;
        }
    }

    return curr;
}

void display_tree(AVL_TREE *pl);

void destroy_tree(AVL_TREE *pl);
void destroy_node(NODE *node);

void balance_tree(AVL_TREE *avl_tree);
int balance_factor(NODE *node) {
    int b_f = 0;
    if(node->left_child) b_f += node_height(node->left_child);
    if(node->right_child) b_f += node_height(node->right_child);

    return b_f;
}

int node_height(NODE* node) {
    int l_height = 0;
    int r_height = 0;

    if(node->left_child) l_height = node_height(node->left_child);
    if(node->right_child) r_height = node_height(node->right_child);

    return r_height > l_height ? ++r_height : ++l_height;
}


