#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    printf("\nMenu:\n"
           "1. Read binary tree\n"
           "2. Print binary tree\n"
           "3. Get DFS\n"
           "4. Search by key\n"
           "5. Get depth of node by key\n"
           "6. Get height of node by key\n"
           "7. Print tree leaves\n"
           "8. Clean binary tree\n"
           "9. Inorder\n"
           "10.Postorder\n"
           "11.Inorder\n"
           "12. Exit\n");
}


Node *create_node(int key) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *read_tree() {
    int key;
    if (scanf("%d", &key) != 1) {
        return NULL;
    }
    if (key == -1) {
        return NULL;
    }

    Node *node = create_node(key);
    node->left = read_tree();
    node->right = read_tree();
    return node;
}

BinaryTree *create_binary_tree() {
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    if (!tree) {
        return NULL;
    }
    tree->root = read_tree();
    return tree;
}

void print_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->key);
    print_tree(root->left);
    print_tree(root->right);
}

void free_tree(Node *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int get_tree_depth(Node *root) {
    if (root == NULL)
        return 0;

    int left = get_tree_depth(root->left);
    int right = get_tree_depth(root->right);

    return (left > right ? left : right) + 1;
}

Node *search_node(Node *root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    Node *left_search = search_node(root->left, key);
    if (left_search != NULL) {
        return left_search;
    }

    return search_node(root->right, key);
}

int get_node_depth(Node *root, int key, int depth) {
    if (root == NULL) {
        return -1;
    }
    if (root->key == key) {
        return depth;
    }

    int left_depth = get_node_depth(root->left, key, depth + 1);
    if (left_depth != -1) {
        return left_depth;
    }
    return get_node_depth(root->right, key, depth + 1);
}

int get_height(Node *root) {
    if (root == NULL) {
        return 0;
    }

    int left_height = get_height(root->left);
    int right_height = get_height(root->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

int get_node_height(Node *root, int key) {
    if (root == NULL) {
        return 0;
    }

    if (root->key == key) {
        int left_height = get_height(root->left);
        int right_height = get_height(root->right);

        return 1 + (left_height > right_height ? left_height : right_height);
    }

    int left_height = get_node_height(root->left, key);
    if (left_height > 0) {
        return left_height;
    }

    return get_node_height(root->right, key);
}

void print_leaf_nodes(Node *root) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->key);
    }

    print_leaf_nodes(root->left);
    print_leaf_nodes(root->right);
}

void clean_tree(Node *root) {
    if (root == NULL) {
        return;
    }

    clean_tree(root->left);
    clean_tree(root->right);

    root->left = NULL;
    root->right = NULL;
}

void print_inorder(Node *root) {
    if (root == NULL) return;
    print_inorder(root->left);
    printf("%d ", root->key);
    print_inorder(root->right);
}

void print_postorder(Node *root) {
    if (root == NULL) return;
    print_postorder(root->left);
    print_postorder(root->right);
    printf("%d ", root->key);
}

void print_preorder(Node *root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    print_preorder(root->left);
    print_preorder(root->right);
}