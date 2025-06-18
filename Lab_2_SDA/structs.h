#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Book {
    char *title;
    char *author;
    int year;
    int pages;
    float price;
} Book;


typedef struct Node {
    Book *data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

typedef enum {
    READ_LIST = 1,
    PRINT_LIST = 2,
    SEARCH_BY_TITLE = 3,
    SEARCH_BY_AUTHOR = 4,
    SEARCH_BY_YEAR = 5,
    SEARCH_BY_PAGES = 6,
    SEARCH_BY_PRICE = 7,
    SORT_BY_TITLE = 8,
    SORT_BY_AUTHOR = 9,
    SORT_BY_YEAR = 10,
    SORT_BY_PAGES = 11,
    SORT_BY_PRICE = 12,
    PUSH_FRONT = 13,
    PUSH_BACK = 14,
    INSERT_AT_POSITION = 15,
    DELETE_AT_POSITION = 16,
    REVERSE_LIST = 17,
    CLEAN_LIST = 18,
    FREE_LIST = 19,
} Case;

typedef int (*BookComparator)(Book *book1, Book *book2);

#endif
