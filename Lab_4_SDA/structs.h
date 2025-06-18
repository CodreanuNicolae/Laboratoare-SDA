#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Node {
    int key;
    char *title;
    int pages;
    int price;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

typedef struct QueueNode {
    Node* tree_node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

typedef enum {
    READ_BINARY_SEARCH_TREE = 1,
    PRINT_BINARY_SEARCH_TREE = 2,
    BALANCE_SEARCH_TREE = 3,
    SEARCH_BY_KEY = 4,
    DFS = 5,
    BFS = 6,
    FREE_TREE = 7,
} Case;
#endif
