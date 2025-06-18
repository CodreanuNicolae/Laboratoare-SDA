#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"

void print_menu();

Node *create_node(int key, const char *title, int pages, int price);

BinaryTree *create_binary_tree();

Node *insert_bst(Node *root, Node *new_node);

void print_tree(Node *root);

void free_tree(Node *root);

void count_nodes(Node *root, int *count);

void store_inorder(Node *root, Node **nodes, int *index);

Node *build_balanced_tree(Node **nodes, int start, int end);

void balance_tree(BinaryTree *tree);

Node *search_node(Node *root, int key);

void print_node(Node *node);

void dfs_preorder(Node *root);

void bfs(Node *root);

void enqueue(Queue *q, Node *node);

Node *dequeue(Queue *q);

int is_empty(Queue *q);


#endif //FUNCTIONS_H
