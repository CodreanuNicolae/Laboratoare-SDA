#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"

void print_menu();

Node *create_node(int key);

Node *read_tree();

BinaryTree *create_binary_tree();

void print_tree(Node *root);

void free_tree(Node *root);

int get_tree_depth(Node *root);

Node *search_node(Node *root, int key);

int get_node_depth(Node *root, int key, int depth);

int get_height(Node *root);

int get_node_height(Node *root, int key);

void print_leaf_nodes(Node *root);

void clean_tree(Node *root);

void print_inorder(Node *root);

void print_preorder(Node *root);

void print_postorder(Node *root);

#endif //FUNCTIONS_H
