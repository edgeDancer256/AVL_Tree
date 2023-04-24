typedef struct node {
    int info;
    struct node *left_child;
    struct node *right_child;
    int height;
} NODE;

typedef struct avl_tree {
    NODE *head;
} AVL_TREE;

AVL_TREE* create_avl_tree();
NODE* create_node(int key);

NODE* insert_node(NODE* root, int info);
NODE* find_node(AVL_TREE* avl_tree, int info);

void display_inorder(NODE* root);
void display_levelorder(NODE* root);

NODE* delete_node(NODE* root, int info);
void destroy_tree(NODE* root);
