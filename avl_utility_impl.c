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
    new_node->height = 1;

    return new_node;
}

int max_height(int a, int b) {
    return (a > b) ? a : b;
}


int node_height(NODE* node) {
    if(node == NULL) {
        return 0;
    }
    return node->height;
}

int balance_factor(NODE* node) {
    if(node == NULL) {
        return 0;
    }
    return node_height(node->left_child) - node_height(node->right_child);
}

NODE* left_rotate(NODE* node) {
    NODE* right = node->right_child;
    NODE* left_right = right->left_child;

    right->left_child = node;
    node->right_child = left_right;

    node->height = max_height(node_height(node->left_child), node_height(node->right_child)) + 1;
    right->height = max_height(node_height(right->left_child), node_height(right->right_child)) + 1;

    return right;
}

NODE* right_rotate(NODE* node) {
    NODE* left = node->left_child;
    NODE* right_left = left->right_child;

    left->right_child = node;
    node->left_child = right_left;

    node->height = max_height(node_height(node->left_child), node_height(node->right_child)) + 1;
    left->height = max_height(node_height(left->left_child), node_height(left->right_child)) + 1;

    return left;
}

NODE* find_min(NODE* node) {
    while(node->left_child != NULL) {
        node = node->left_child;
    }

    return node;
}

NODE* insert_node(NODE* root, int info) {
    if(root == NULL) {
        return create_node(info);
    }

    if(info < root->info) {
        root->left_child = insert_node(root->left_child, info);
    } else if(info > root->info) {
        root->right_child = insert_node(root->right_child, info);
    } else {
        return root;
    }

    root->height = max_height(node_height(root->left_child), node_height(root->right_child)) + 1;

    int b_f = balance_factor(root);

    //Balancing . . .
    //Left-Left Case
    if(b_f > 1 && info < root->left_child->info) {
        return right_rotate(root);
    }

    //Right-Right Case
    if(b_f < -1 && info > root->right_child->info) {
        return left_rotate(root);
    }

    //Left-Right Case
    if(b_f > 1 && info > root->left_child->info) {
        root->left_child = left_rotate(root->left_child);
        return right_rotate(root);
    }

    //Right-Left Case
    if(b_f < -1 && info < root->right_child->info) {
        root->right_child = right_rotate(root->right_child);
        return left_rotate(root);
    }

    return root;
}

NODE* find_node(AVL_TREE* avl_tree, int info) {
    NODE* p = avl_tree->head;
    
    while(p && p->info != info) {
        if(info > p->info) {
            p = p->right_child;
        } else {
            p = p->left_child;
        }
    } 

    return p;
}

NODE* delete_node(NODE* root, int info) {
    if(root == NULL) {
        return root;
    }

    if(info < root->info) {
        root->left_child = delete_node(root->left_child, info);
    } else if(info > root->info) {
        root->right_child = delete_node(root->right_child, info);
    } else {
        if(root->right_child == NULL && root->left_child == NULL) {
            free(root);
            root = NULL;
        } else if(root->left_child != NULL && root->right_child == NULL) {
            NODE* temp = root->left_child;
            root = root->left_child;
            free(temp);
        } else if(root->right_child != NULL && root->left_child == NULL) {
            NODE* temp = root->right_child;
            root = root->right_child;
            free(temp);
        } else {
            NODE* temp = find_min(root->right_child);
            root->info = temp->info;
            root->right_child = delete_node(root->right_child, temp->info);
        }
    }
    if(root == NULL) {
        return root;
    }

    root->height = 1 + max_height(node_height(root->left_child), node_height(root->right_child));
    int b_f = balance_factor(root);

    //Balancing . . .
    //Left-Left Case
    if(b_f > 1 && balance_factor(root->left_child) >= 0) {
        return right_rotate(root);
    }
    //Right-Right Case
    if(b_f < -1 && balance_factor(root->right_child) <= 0) {
        return left_rotate(root);
    }
    //Left-Right Case
    if(b_f > 1 && balance_factor(root->left_child) < 0) {
        root->left_child = left_rotate(root->left_child);
        return right_rotate(root);
    }
    //Right-Left Case
    if(b_f < -1 && balance_factor(root->right_child) > 0) {
        root->right_child = right_rotate(root->right_child);
        return left_rotate(root);
    }

    return root;
}

void display_inorder(NODE* root) {

    if(root == NULL) {
        return;
    }

    display_inorder(root->left_child);
    printf("| %d |", root->info);
    display_inorder(root->right_child);
}



void disp_curr_level(NODE* root, int level) {
    if(root == NULL) {
        return;
    }   
    if(level == 1) {
        printf("| %d |", root->info);
    } else if(level > 1) {
        disp_curr_level(root->left_child, level-1);
        disp_curr_level(root->right_child, level-1);
    }
}

void display_levelorder(NODE* root) {
    int h = node_height(root);
    for(int i = 0; i <= h; i++) {
        disp_curr_level(root, i);
        printf("\n");
    }
}

void destroy_tree(NODE* root) {
    destroy_tree(root->left_child);
    destroy_tree(root->right_child);
    free(root);
}
