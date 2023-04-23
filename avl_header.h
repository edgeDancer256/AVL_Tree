typedef struct node {
    int info;
    struct node *left_child;
    struct node *right_child;
} NODE;

typedef struct avl_tree {
    NODE *head;
} AVL_TREE;

AVL_TREE* create_avl_tree();
NODE* create_node(int key);

void insert_node(AVL_TREE *pl, int key);
NODE* delete_node(AVL_TREE *pl, int key);
int find_node(AVL_TREE *pl, int key);

void display_tree(AVL_TREE *pl);

void destroy_tree(AVL_TREE *pl);
void destroy_node(NODE *node);

int balance_factor(NODE *node);
void balance_tree(AVL_TREE *avl_tree);