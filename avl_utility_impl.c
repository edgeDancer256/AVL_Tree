#include<stdio.h>
#include<stdlib.h>
#include"avl_header.h"

//Creates an empty AVL Tree
AVL_TREE* create_avl_tree() {
    //Allocate memory for the tree
    AVL_TREE* avl_tree = (AVL_TREE*) malloc(sizeof(AVL_TREE));
    //Check if allocation was successful
    if(avl_tree == NULL) {
        fprintf(stderr, "Error during memory allocation\n");
        exit(EXIT_FAILURE);
    }
    //Set the head pointer to point to NULL as it is an empty tree
    avl_tree->head = NULL;

    //Return the tree
    return avl_tree;
}

//Creates a new node and return it for insertion
NODE* create_node(int key) {
    //Allocate memory for the node
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    //Check if allocation was successful
    if(new_node == NULL) {
        fprintf(stderr, "Error during memory allocation\n");
        exit(EXIT_FAILURE);
    }
    //Set value of info field to provided value
    new_node->info = key;
    //Set child pointers to NULL
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    //Set default height of node to 1
    new_node->height = 1;

    //Return the node
    return new_node;
}

//Helper function to calculate maximum height of two subtrees
int max_height(int a, int b) {
    return (a > b) ? a : b;
}

//Helper function to calculate the height of the node
int node_height(NODE* node) {
    if(node == NULL) {
        return 0;
    }
    return node->height;
}

//Helper function to calculate the balance factor of a node
int balance_factor(NODE* node) {
    if(node == NULL) {
        return 0;
    }
    //Balance factor is given by height(left child) - height(right child)
    return node_height(node->left_child) - node_height(node->right_child);
}

//Helper function to perform left-rotation
NODE* left_rotate(NODE* node) {
    //Get appropriate pointers
    NODE* right = node->right_child;
    NODE* left_right = right->left_child;

    //Set Left child of right child of "root" to the "root"
    right->left_child = node;
    //Set right child of "root" to left child of right child of "root"
    node->right_child = left_right;

    //Update all heights accordingly
    node->height = max_height(node_height(node->left_child), node_height(node->right_child)) + 1;
    right->height = max_height(node_height(right->left_child), node_height(right->right_child)) + 1;

    //Return the new "root"
    return right;
}

//Helper function to perform right-rotation
NODE* right_rotate(NODE* node) {
    //Get appropriate pointers
    NODE* left = node->left_child;
    NODE* right_left = left->right_child;

    //Set right child of left child of "root" to the "root"
    left->right_child = node;
    //Set left child of "root" to right child of left child of "root" 
    node->left_child = right_left;

    //Update all heights accordingly
    node->height = max_height(node_height(node->left_child), node_height(node->right_child)) + 1;
    left->height = max_height(node_height(left->left_child), node_height(left->right_child)) + 1;

    //Return the new "root"
    return left;
}

//Helper function to find the node with minimum value of the left subtree
//To be used when the node being deleted is the root 
NODE* find_min(NODE* node) {
    //Traverse the tree till you find the left-most node
    while(node->left_child != NULL) {
        node = node->left_child;
    }

    //Return the left-most node
    return node;
}

//Function to insert a new node into the tree
NODE* insert_node(NODE* root, int info) {
    //Create a new node and return that if tree is empty
    if(root == NULL) {
        return create_node(info);
    }

    //Traverse the tree to find the position to insert the new node 
    if(info < root->info) {
        root->left_child = insert_node(root->left_child, info);
    } else if(info > root->info) {
        root->right_child = insert_node(root->right_child, info);
    } else {
        return root;
    }

    //Find the current height of the node to which the new node has to be inserted
    root->height = max_height(node_height(root->left_child), node_height(root->right_child)) + 1;
    
    //Calculate the balance factor
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

    //Return the newly created node to be attached to it's proper parent
    return root;
}

//Function to find a node in the tree
NODE* find_node(AVL_TREE* avl_tree, int info) {
    NODE* p = avl_tree->head;
    
    //Traverse the tree till you find the node or you reach the end
    while(p && p->info != info) {
        if(info > p->info) {
            p = p->right_child;
        } else {
            p = p->left_child;
        }
    } 

    //Return node if found or return NULL
    return p;
}

//Function to delete a node from the tree
NODE* delete_node(NODE* root, int info) {
    //If tree is empty, return
    if(root == NULL) {
        return root;
    }

    //Traverse the tree till you find the node to be deleted
    if(info < root->info) {
        root->left_child = delete_node(root->left_child, info);
    } else if(info > root->info) {
        root->right_child = delete_node(root->right_child, info);
    } else { 
        if(root->right_child == NULL && root->left_child == NULL) {         //Case : Right child and Left child are NULL
            free(root);
            root = NULL;
        } else if(root->left_child != NULL && root->right_child == NULL) {  //Case : Left child is not NULL and Right child is NULL
            NODE* temp = root->left_child;
            root = root->left_child;
            free(temp);
        } else if(root->right_child != NULL && root->left_child == NULL) {  //Case : Left child is NULL and Right child is not NULL
            NODE* temp = root->right_child;
            root = root->right_child;
            free(temp);
        } else {                                                            //Case : Both children are not NULL
            NODE* temp = find_min(root->right_child);
            root->info = temp->info;
            root->right_child = delete_node(root->right_child, temp->info);
        }
    }
    if(root == NULL) {
        return root;
    }

    //Calculate height and balance factor for balancing after delete
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

//Function to display the tree in In-Order
void display_inorder(NODE* root) {

    if(root == NULL) {
        return;
    }

    //Display left subtree
    display_inorder(root->left_child);
    //Display root
    printf("| %d |", root->info);
    //Display right subtree
    display_inorder(root->right_child);
}


//Helper function for display_levelorder
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

//Function to display tree in Level-Order
void display_levelorder(NODE* root) {
    //Get the height of the root and display all levels one by one
    int h = node_height(root);
    for(int i = 0; i <= h; i++) {
        disp_curr_level(root, i);
        printf("\n");
    }
}

//Function to display tree in Pre-Order
void display_preorder(NODE* root) {
    if(root == NULL) {
        return;
    }
    printf("| %d |", root->info);
    display_preorder(root->left_child);
    display_preorder(root->right_child);
}

//Function to destroy the tree
void destroy_tree(NODE* root) {
    if(root != NULL) {
        //Destroy left subtree of root
        if(root->left_child != NULL) destroy_tree(root->left_child);
        //Destroy right subtree of root
        if(root->right_child != NULL) destroy_tree(root->right_child);
        //Destroy root
        free(root);
        return;
    }
    return;
}
