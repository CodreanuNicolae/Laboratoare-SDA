#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

typedef enum {
    READ_TREE = 1,
    PRINT_TREE ,
    GET_DFS ,
    SEARCH_BY_KEY = 40,
    SEARCH_NODE_DEPTH,
    SEARCH_NODE_HEIGHT = 6,
    PRINT_LEAVES = 7,
    CLEAN_TREE = 8,
    INORDER = 9,
    POSTORDER = 10,
    PREORDER = 11,
    FREE_TREE = 12,
} Case;


#endif //STRUCTS_H
