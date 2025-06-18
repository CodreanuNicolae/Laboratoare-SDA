#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LEN 100

void print_menu() {
    printf("\nMenu:\n"
        "1. Read binary search tree\n"
        "2. Print binary search tree\n"
        "3. Balance tree\n"
        "4. Search node by key\n"
        "5. DFS preorder traversal\n"
        "6. BFS traversal\n"
        "7. Exit\n");
}

Node *create_node(int key, const char *title, int pages, int price) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->key = key;
    new_node->title = malloc(strlen(title) + 1);
    if (!new_node->title) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->title, title);
    new_node->pages = pages;
    new_node->price = price;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *insert_bst(Node *root, Node *new_node) {
    if (!root) return new_node;
    if (new_node->key < root->key)
        root->left = insert_bst(root->left, new_node);
    else
        root->right = insert_bst(root->right, new_node);
    return root;
}

BinaryTree *create_binary_tree() {
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    if (!tree) return NULL;
    tree->root = NULL;
    printf("Enter nodes (key title pages price):\n");

    while (1) {
        int key, pages, price;
        char title[MAX_TITLE_LEN];

        if (scanf("%d", &key) != 1 || key == -1)
            break;

        if (scanf("%99s %d %d", title, &pages, &price) != 3)
            break;

        Node *new_node = create_node(key, title, pages, price);
        if (!new_node) {
            printf("Memory error.\n");
            break;
        }

        tree->root = insert_bst(tree->root, new_node);
    }

    return tree;
}

void print_tree(Node *root) {
    if (!root) return;
    print_tree(root->left);
    printf("%d %s %d %d\n", root->key, root->title, root->pages, root->price);
    print_tree(root->right);
}

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root->title);
    free(root);
}

void count_nodes(Node *root, int *count) {
    if (!root) return;
    count_nodes(root->left, count);
    (*count)++;
    count_nodes(root->right, count);
}

void store_inorder(Node *root, Node **nodes, int *index) {
    if (!root) return;
    store_inorder(root->left, nodes, index);
    nodes[(*index)++] = root;
    store_inorder(root->right, nodes, index);
}

Node *build_balanced_tree(Node **nodes, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    Node *root = nodes[mid];
    root->left = build_balanced_tree(nodes, start, mid - 1);
    root->right = build_balanced_tree(nodes, mid + 1, end);
    return root;
}

void balance_tree(BinaryTree *tree) {
    if (!tree || !tree->root) return;
    int count = 0;
    count_nodes(tree->root, &count);
    Node **nodes = malloc(count * sizeof(Node *));
    if (!nodes) return;
    int index = 0;
    store_inorder(tree->root, nodes, &index);
    tree->root = build_balanced_tree(nodes, 0, count - 1);
    free(nodes);
}

Node *search_node(Node *root, int key) {
    if (!root) return NULL;
    if (key == root->key) return root;
    if (key < root->key)
        return search_node(root->left, key);
    else
        return search_node(root->right, key);
}

void print_node(Node *node) {
    if (!node) {
        printf("Node not found.\n");
        return;
    }
    printf("Key: %d\nTitle: %s\nPages: %d\nPrice: %d\n",
           node->key, node->title, node->pages, node->price);
}

void dfs_preorder(Node *root) {
    if (!root) return;
    printf("%d %s %d %d\n", root->key, root->title, root->pages, root->price);
    dfs_preorder(root->left);
    dfs_preorder(root->right);
}

void enqueue(Queue *q, Node *node) {
    QueueNode *temp = malloc(sizeof(QueueNode));
    temp->tree_node = node;
    temp->next = NULL;
    if (!q->rear) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node *dequeue(Queue *q) {
    if (!q->front) return NULL;
    QueueNode *temp = q->front;
    Node *node = temp->tree_node;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return node;
}

int is_empty(Queue *q) {
    return q->front == NULL;
}

void bfs(Node *root) {
    if (!root) return;

    Queue q = {NULL, NULL};
    enqueue(&q, root);

    while (!is_empty(&q)) {
        Node *current = dequeue(&q);
        printf("%d %s %d %d\n", current->key, current->title, current->pages, current->price);

        if (current->left)
            enqueue(&q, current->left);
        if (current->right)
            enqueue(&q, current->right);
    }
}
