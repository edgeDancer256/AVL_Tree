#include <stdio.h>
#include "avl_header.h"

int main() {
    AVL_TREE *p = create_avl_tree();

    p->head = insert_node(p->head, 5);
    p->head = insert_node(p->head, 10);
    p->head = insert_node(p->head, 15);
    p->head = insert_node(p->head, 25);
    p->head = insert_node(p->head, 30);
    p->head = insert_node(p->head, 14);
    p->head = insert_node(p->head, 23);
    p->head = insert_node(p->head, 6);
    p->head = insert_node(p->head, 24);
    p->head = insert_node(p->head, 30);
    p->head = insert_node(p->head, 3);
    
    display_inorder(p->head); printf("\n");
    display_levelorder(p->head); printf("\n");

    p->head = delete_node(p->head, 10);

    display_inorder(p->head); printf("\n");
    display_levelorder(p->head); printf("\n");

    NODE* search = find_node(p, 23);
    if(search) printf("Node with info %d found\n", search->info);
    else printf("No node with given info found\n");
}