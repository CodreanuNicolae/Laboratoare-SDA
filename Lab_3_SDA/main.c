#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define MEMORY_HAS_BEEN_FREED = 1

int main() {
    int choice = 0;
    int key_to_search = 0;
    while (choice != FREE_TREE) {
        print_menu();
        scanf("%d", &choice);
        switch (choice) {
            case READ_TREE:
                printf("Enter tree in preorder :\n");
                BinaryTree *tree = create_binary_tree();
                break;
            case PRINT_TREE:
                printf("Preorder output of tree:\n");
                print_tree(tree->root);
                printf("\n");
                break;
            case GET_DFS:
                int depth = get_tree_depth(tree->root);
                printf("Depth of the tree: %d\n", depth);
                break;
            case SEARCH_BY_KEY:
                printf("Enter a key to search for: ");
                scanf("%d", &key_to_search);

                Node *found_node = search_node(tree->root, key_to_search);

                if (found_node != NULL) {
                    printf("Node with key %d found.\n", key_to_search);
                } else {
                    printf("Node with key %d not found.\n", key_to_search);
                }
                break;
            case SEARCH_NODE_DEPTH:
                if (tree == NULL) {
                    printf("Tree is empty. Please read a binary tree first.\n");
                } else {
                    printf("Enter key to find depth: ");
                    scanf("%d", &key_to_search);
                    int depth = get_node_depth(tree->root, key_to_search, 1);
                    if (depth != -1) {
                        printf("Depth of node with key %d: %d\n", key_to_search, depth);
                    } else {
                        printf("Node with key %d not found.\n", key_to_search);
                    }
                }
                break;
            case SEARCH_NODE_HEIGHT:
                printf("Enter key to search for height: ");
                scanf("%d", &key_to_search);

                int node_height = get_node_height(tree->root, key_to_search);

                if (node_height > 0) {
                    printf("Height of node with key %d: %d\n", key_to_search, node_height);
                } else {
                    printf("Node with key %d not found.\n", key_to_search);
                }
                break;
            case PRINT_LEAVES:
                printf("Leaf nodes of the tree: ");
                print_leaf_nodes(tree->root);
                printf("\n");
                break;
            case CLEAN_TREE:
                clean_tree(tree->root);
                printf("Tree has been cleaned.\n");
                break;
            case INORDER:
                printf("Inorder:\n");
            print_inorder(tree->root);
            printf("\n");
            break;

            case PREORDER:
                printf("Preorder:\n");
            print_preorder(tree->root);
            printf("\n");
            break;

            case POSTORDER:
                printf("Postorder:\n");
            print_postorder(tree->root);
            printf("\n");
            break;

            case FREE_TREE:
                free_tree(tree->root);
                free(tree);
                exit(1);
            default: printf("Please enter a valid choice.\n");
        }
    }
    return 0;
}
