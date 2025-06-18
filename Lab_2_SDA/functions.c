
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100


int _title_book_comparator(Book* book1, Book* book2) {
    return strcmp(book1->title, book2->title);
}

int _author_book_comparator(Book* book1, Book* book2) {
    return strcmp(book1->author, book2->author);
}

int _year_book_comparator(Book* book1, Book* book2) {
    return book1->year - book2->year;
}

int _pages_book_comparator(Book* book1, Book* book2) {
    return book1->pages - book2->pages;
}

int _price_book_comparator(Book* book1, Book* book2) {
    return (int)(book1->price - book2->price);
}


void print_menu() {
    printf("\nMenu:\n");
    printf("1. Read list\n");
    printf("2. Print list\n");
    printf("3. Search by title\n");
    printf("4. Search by author\n");
    printf("5. Search by year\n");
    printf("6. Search by pages\n");
    printf("7. Search by price\n");
    printf("8. Sort by title\n");
    printf("9. Sort by author\n");
    printf("10. Sort by year\n");
    printf("11. Sort by pages\n");
    printf("12. Sort by price\n");
    printf("13. Push front\n");
    printf("14. Push back\n");
    printf("15. Insert at position\n");
    printf("16. Remove at position\n");
    printf("17. Reverse list\n");
    printf("18. Clear list\n");
    printf("19. Exit\n");
    printf("Enter your choice: ");
}


Book *allocate_book() {
    Book *book = malloc(sizeof(Book));

    if (book == NULL) {
        return NULL;
    }

    book->title = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
    book->author = (char*)malloc(MAX_AUTHOR_LENGTH * sizeof(char));

    if (!book->title || !book->author) {
        return NULL;
    }

    return book;
}

Node* alloc_node() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }

    new_node->data = allocate_book();

    new_node->next = NULL;
    return new_node;
}


LinkedList* alloc_list(const int nr_of_nodes) {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < nr_of_nodes; i++) {
        Node* new_node = alloc_node();
        if (list->head == NULL) {
            list->head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return list;
}

void free_node(Node* node) {
    free(node->data->title);
    free(node->data->author);
    free(node->data);
    free(node);
}

void free_list(LinkedList* list) {
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free_node(current);
        current = next;
    }
    free(list);
}

void read_node(Node* node) {
    printf("Enter title: ");
    scanf("%s", node->data->title);

    printf("Enter author: ");
    scanf("%s", node->data->author);

    printf("Enter year: ");
    scanf("%d", &node->data->year);

    printf("Enter pages: ");
    scanf("%d", &node->data->pages);

    printf("Enter price: ");
    scanf("%f", &node->data->price);
}

void read_list(LinkedList* list) {
    Node* current = list->head;
    while (current) {
        read_node(current);
        current = current->next;
    }
}

void print_node(Node* node) {
    printf("\nTitle: %s\n", node->data->title);
    printf("Author: %s\n", node->data->author);
    printf("Year: %d\n", node->data->year);
    printf("Pages: %d\n", node->data->pages);
    printf("Price: %.2f\n", node->data->price);
}

void print_list(LinkedList* list) {
    Node* current = list->head;
    while (current) {
        print_node(current);
        current = current->next;
    }
}

int search(LinkedList* list, Book *target_book, BookComparator comparator) {
    int pos = 0;
    Node* current = list->head;
    while (current) {
        if (comparator(current->data, target_book) == 0) {
            return pos;
        }
        current = current->next;
        pos++;
    }
    return -1;
}

void swap_nodes(Node* first_node, Node* second_node) {
    Book* temp_book = first_node->data;
    first_node->data = second_node->data;
    second_node->data = temp_book;
}

void sort_list(LinkedList* list, BookComparator book_comparator) {
    if (list->head == NULL) return;

    int swapped;
    Node* last_sorted_node = NULL;

    do {
        swapped = 0;
        Node *current_node = list->head;

        while (current_node->next != last_sorted_node) {
            if (book_comparator(current_node->data, current_node->next->data) > 0) {
                swap_nodes(current_node, current_node->next);
                swapped = 1;
            }
            current_node = current_node->next;
        }
        last_sorted_node = current_node;
    } while (swapped);
}

void push_front(LinkedList *list, Node *new_node) {
    new_node->next = list->head;
    list->head = new_node;
}

void push_back(LinkedList *list, Node *new_node) {
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void insert_at_position(LinkedList *list, Node *new_node, int position) {
    if (position == 0) {
        new_node->next = list->head;
        list->head = new_node;
        return;
    }

    Node *current = list->head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    new_node->next = current->next;
    current->next = new_node;
}

void delete_at_position(LinkedList* list, int position) {
    if (list->head == NULL) {
        return;
    }

    if (position == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        free_node(temp);
        return;
    }

    Node* current = list->head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }

    if (current == NULL || current->next == NULL) {
        return;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free_node(temp);
}

void reverse_list(LinkedList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
}

void clear_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next_node = current->next;
        free_node(current);
        current = next_node;
    }
    list->head = NULL;
}

void clean_tree(Node* root) {
    if (root == NULL) {
        return;
    }

    clean_tree(root->left);
    clean_tree(root->right);

    root->left = NULL;
    root->right = NULL;
}





