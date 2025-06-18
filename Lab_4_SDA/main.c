#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    BinaryTree* tree = NULL;
    int choice;

    while (choice != 7) {
        print_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case READ_BINARY_SEARCH_TREE:
                if (tree) {
                    free_tree(tree->root);
                    free(tree);
                }
            tree = create_binary_tree();
            break;
            case PRINT_BINARY_SEARCH_TREE:
                if (!tree || !tree->root) printf("Tree is empty.\n");
                else print_tree(tree->root);
            break;
            case BALANCE_SEARCH_TREE:
                if (!tree || !tree->root) printf("Tree is empty.\n");
                else {
                    balance_tree(tree);
                    printf("Tree balanced.\n");
                }
            break;
            case SEARCH_BY_KEY:
                if (!tree || !tree->root) {
                    printf("Tree is empty.\n");
                } else {
                    int search_key;
                    printf("Enter key to search: ");
                    scanf("%d", &search_key);
                    Node* found = search_node(tree->root, search_key);
                    print_node(found);
                }
            break;
            case DFS:
                if (!tree || !tree->root) printf("Tree is empty.\n");
                else dfs_preorder(tree->root);
            break;
            case BFS:
                if (!tree || !tree->root) printf("Tree is empty.\n");
                else bfs(tree->root);
            break;
            case FREE_TREE:
                if (tree) {
                    free_tree(tree->root);
                    free(tree);
                }
            default:
                printf("Invalid option.\n");
        }
    }
    return 0;
}
