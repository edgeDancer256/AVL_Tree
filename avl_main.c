#include <stdio.h>
#include "avl_header.h"

int main() {
    printf("|-|-|-| A V L Tree |-|-|-|\n");
    printf("Existing tree . . .\n");
    AVL_TREE *p = create_avl_tree();

    //Hardcoding 15 nodes
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
    p->head = insert_node(p->head, 49);
    p->head = insert_node(p->head, 33);
    p->head = insert_node(p->head, 35);
    p->head = insert_node(p->head, 40);
    p->head = insert_node(p->head, 2);
    
    printf("In-Order\n");
    display_inorder(p->head); printf("\n");
    printf("Level-Order\n");
    display_levelorder(p->head); printf("\n");
    printf("Pre-Order\n");
    display_preorder(p->head); printf("\n");

    int choice;
    int ele;

    
    printf("\n1. Insert element (Repeated values will not be inserted) \n");
    printf("2. Delete element\n");
    printf("3. Search for an element\n");
    printf("4. Display tree (Will be displayed in In-Order, Pre-Order and Level-Order)\n");
    printf("5. Exit\n");
    printf("Please select an option : ");

    scanf("%d", &choice);

    do {
        switch(choice) {
            case 1:
                printf("Enter the element to insert : ");
                scanf("%d", &ele);
                //Calling function to insert a node
                p->head = insert_node(p->head, ele);

                break;
            case 2:
                printf("Enter element to delete : ");
                scanf("%d", &ele);
                //Calling function to delete a node
                p->head = delete_node(p->head, ele);

                break;
            case 3:
                printf("Enter the element to search for : ");
                scanf("%d", &ele);
                //Calling function to search for element in tree
                NODE *temp = find_node(p, ele);
                if(temp != NULL && temp->info == ele) {
                    printf("Element present in tree\n");
                } else {
                    printf("Element not in tree\n");
                }
                break;
            case 4:
                //Calling functions to display tree - In-Order, Pre-Order, Level-Order
                if(p->head != NULL) {
                    printf("In-Order\n");
                    display_inorder(p->head); printf("\n");
                    printf("Level-Order\n");
                    display_levelorder(p->head); printf("\n");
                    printf("Pre-Order\n");
                    display_preorder(p->head); printf("\n");
                } else {
                    printf("Empty tree ! ! ! ! ! ! ! !");
                }
                break;
            case 5:
                //Destroying the tree and freeing memory
                destroy_tree(p->head);
                return 0;
        }
        
        printf("\n1. Insert element\n");
        printf("2. Delete element\n");
        printf("3. Search for an element\n");
        printf("4. Display tree (Will be displayed in In-Order, Pre-Order and Level-Order)\n");
        printf("5. Exit\n");
        printf("Please select an option : ");

        scanf("%d", &choice);
    }while(choice < 6);

    return 1;
}