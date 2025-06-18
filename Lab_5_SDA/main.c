#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int *arr = NULL;
int size = 0;
bool is_sorted = false;

int main() {
    srand((unsigned int) time(NULL));
    int option;
    int key;

    do {
        printf("\n=== Menu ===\n");
        printf("1. Initialize array with random numbers\n");
        printf("2. Display array\n");
        printf("3. Free array memory\n");
        printf("4. Sort with bubble sort (simple method)\n");
        printf("5. Sort with quick sort (efficient method)\n");
        printf("6. Empirical analysis: sorting times for various N\n");
        printf("7. Linear search\n");
        printf("8. Binary search\n");
        printf("9. Empirical analysis: 10,000 searches for various N\n");
        printf("10. Compute Fibonacci number (n up to 1,000,000)\n");
        printf("11. Empirical analysis: Fibonacci computation times\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            option = -1;
        }

        switch (option) {
            case 1:
                if (arr != NULL) {
                    free_memory(&arr);
                }
                printf("Enter array size: ");
                if (scanf("%d", &size) != 1 || size <= 0) {
                    printf("Invalid size.\n");
                    size = 0;
                    break;
                }
                arr = (int *) malloc(size * sizeof(int));
                if (arr == NULL) {
                    printf("Memory allocation failed.\n");
                    size = 0;
                    break;
                }
                initialize_arr(arr, size);
                printf("Array initialized with random numbers.\n");
                break;

            case 2:
                if (arr == NULL) {
                    printf("Array is not initialized.\n");
                } else {
                    display_arr(arr, size);
                }
                break;

            case 3:
                if (arr != NULL) {
                    free_memory(&arr);
                    printf("Memory freed.\n");
                } else {
                    printf("Array already freed or not initialized.\n");
                }
                break;

            case 4:
                if (arr != NULL) {
                    measure_with_qpc_inplace(bubble_sort, arr, size, "Bubble Sort");
                    is_sorted = true;
                } else {
                    printf("Array is not initialized.\n");
                }
                break;

            case 5:
                if (arr != NULL) {
                    measure_with_qpc_inplace(quick_sort_wrapper, arr, size, "Quick Sort");
                    is_sorted = true;
                } else {
                    printf("Array is not initialized.\n");
                }
                break;

            case 6:
                empirical_sort_analysis();
                break;

            case 7:
                if (arr != NULL) {
                    printf("Enter number to search (linear search): ");
                    if (scanf("%d", &key) != 1) {
                        printf("Invalid input.\n");
                        break;
                    }
                    measure_search(linear_search, arr, size, key, "Linear Search");
                } else {
                    printf("Array is not initialized.\n");
                }
                break;

            case 8:
                if (arr != NULL) {
                    if (!is_sorted) {
                        printf("Array is not sorted! Please sort it before binary search.\n");
                        break;
                    }
                    printf("Enter number to search (binary search): ");
                    if (scanf("%d", &key) != 1) {
                        printf("Invalid input.\n");
                        break;
                    }
                    measure_search(binary_search, arr, size, key, "Binary Search");
                } else {
                    printf("Array is not initialized.\n");
                }
                break;

            case 9:
                empirical_search_analysis();
                break;

            case 10: {
                printf("Enter n (0 <= n <= 1000000): ");
                int n;
                if (scanf("%d", &n) != 1 || n < 0 || n > 1000000) {
                    printf("Invalid input. n must be between 0 and 1,000,000.\n");
                    while (getchar() != '\n');
                    break;
                }

                printf("Calculating Fibonacci(%d)...\n", n);
                BigInt fib = fibonacci(n);

                printf("Fibonacci(%d) = ", n);
                bigint_print(fib);
                printf("\n");

                bigint_free(&fib);
                break;
            }

            case 11:
                empirical_fibonacci_analysis();
                break;

            case 0:
                if (arr != NULL) {
                    free_memory(&arr);
                }
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid option. Try again.\n");
                break;
        }
    } while (option != 0);
    return 0;
}
