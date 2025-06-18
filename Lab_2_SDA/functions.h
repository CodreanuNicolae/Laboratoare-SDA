#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

void print_menu();

Book *allocate_book();

Node *alloc_node();

LinkedList *alloc_list(int nr_of_nodes);

void free_node(Node *node);

void free_list(LinkedList *list);

void read_node(Node *node);

void read_list(LinkedList *head);

void print_node(Node *node);

void print_list(LinkedList *head);

int search(LinkedList *head, Book *target_book, BookComparator comparator);

void swap_nodes(Node *first_node, Node *second_node);

void sort_list(LinkedList *list,BookComparator book_comparator);

void push_front(LinkedList *list, Node *new_node);

void push_back(LinkedList *list, Node *new_node);

void insert_at_position(LinkedList *list, Node *new_node, int position);

void delete_at_position(LinkedList *list, int position);

void reverse_list(LinkedList *list);

void clear_list(LinkedList *list);

int _title_book_comparator(Book* book1, Book* book2);

int _author_book_comparator(Book* book1, Book* book2);

int _year_book_comparator(Book* book1, Book* book2);

int _pages_book_comparator(Book* book1, Book* book2);

int _price_book_comparator(Book* book1, Book* book2);
#endif
