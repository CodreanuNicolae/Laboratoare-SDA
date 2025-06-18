#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    int nr_of_nodes = 0;
    printf("Enter the number of nodes: ");
    scanf("%d", &nr_of_nodes);

    LinkedList* list = alloc_list(nr_of_nodes);

    int choice = 0;

    while (choice != FREE_LIST) {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case READ_LIST:
                read_list(list);
                break;

            case PRINT_LIST:
                print_list(list);
                break;

            case SEARCH_BY_TITLE: {
                char title[MAX_TITLE_LENGTH];
                printf("Enter title to search: ");
                scanf(" %s", title);
                Book target_book;
                target_book.title = malloc(MAX_AUTHOR_LENGTH * sizeof(char));
                strncpy(target_book.title, title, MAX_TITLE_LENGTH);
                int pos = search(list, &target_book, _title_book_comparator);
                free(target_book.title);
                if (pos != -1)
                    printf("Found at position %d\n", pos);
                else
                    printf("Not found.\n");
                break;
            }

            case SEARCH_BY_AUTHOR: {
                char author[MAX_AUTHOR_LENGTH];
                printf("Enter author to search: ");
                scanf(" %s", author);
                printf("Author name: %s\n", author);
                Book target_book;
                target_book.author = malloc(MAX_AUTHOR_LENGTH * sizeof(char));
                strncpy(target_book.author, author, MAX_AUTHOR_LENGTH);
                int pos = search(list, &target_book, _author_book_comparator);
                free(target_book.author);
                if (pos != -1)
                    printf("Found at position %d\n", pos);
                else
                    printf("Not found.\n");
                break;
            }

            case SEARCH_BY_YEAR: {
                int year;
                printf("Enter year to search: ");
                scanf("%d", &year);
                Book target_book;
                target_book.year = year;
                int pos = search(list, &target_book, _year_book_comparator);
                if (pos != -1)
                    printf("Found at position %d\n", pos);
                else
                    printf("Not found.\n");
                break;
            }

            case SEARCH_BY_PAGES: {
                int pages;
                printf("Enter pages to search: ");
                scanf("%d", &pages);
                Book target_book;
                target_book.pages = pages;
                int pos = search(list, &target_book, _pages_book_comparator);
                if (pos != -1)
                    printf("Found at position %d\n", pos);
                else
                    printf("Not found.\n");
                break;
            }

            case SEARCH_BY_PRICE: {
                float price;
                printf("Enter price to search: ");
                scanf("%f", &price);
                Book target_book;
                target_book.price = price;
                int pos = search(list, &target_book, _price_book_comparator);
                if (pos != -1)
                    printf("Found at position %d\n", pos);
                else
                    printf("Not found.\n");
                break;
            }
            case SORT_BY_TITLE: {
                sort_list(list, _title_book_comparator);
                break;
            }
            case SORT_BY_AUTHOR: {
                sort_list(list, _author_book_comparator);
                break;
            }
            case SORT_BY_YEAR: {
                sort_list(list,_year_book_comparator);
                break;
            }
            case SORT_BY_PAGES: {
                sort_list(list, _pages_book_comparator);
                break;
            }
            case SORT_BY_PRICE: {
                sort_list(list, _price_book_comparator);
                break;
            }
            case PUSH_FRONT: {
                Node *new_node = alloc_node();
                if (!new_node) {
                    break;
                }
                read_node(new_node);
                push_front(list, new_node);
                break;
            }

            case PUSH_BACK: {
                Node *new_node = alloc_node();
                if (!new_node) {
                    break;
                }
                read_node(new_node);
                push_back(list, new_node);
                break;
            }

            case INSERT_AT_POSITION: {
                int pos;
                printf("Enter position: ");
                scanf("%d", &pos);

                Node *new_node = alloc_node();
                if (!new_node) {
                    break;
                }
                read_node(new_node);
                insert_at_position(list, new_node, pos);
                break;
            }

            case DELETE_AT_POSITION: {
                int pos = 0;
                printf("Enter position: ");
                scanf("%d", &pos);
                delete_at_position(list,pos);
                break;
            }
            case REVERSE_LIST: {
                reverse_list(list);
                break;
            }
            case CLEAN_LIST: {
                clear_list(list);
                break;
            }
            case FREE_LIST: {
                free_list(list);
                exit(0);
            }
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
