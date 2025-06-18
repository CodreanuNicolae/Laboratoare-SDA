#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdint.h>
#include "structs.h"

extern int *arr;
extern int size;
extern bool is_sorted;

void display_arr(int *arr, int size);

void initialize_arr(int *arr, int size);

void free_memory(int **arr);

void bubble_sort(int *arr, int size);

void quick_sort_wrapper(int *arr, int size);

double measure_sort_time(void (*sort_func)(int *, int), int *arr, int size);

void empirical_sort_analysis();


int linear_search(int *arr, int size, int key);

int binary_search(int *arr, int size, int key);

void measure_search(int (*search_func)(int *, int, int), int *arr, int size, int key, const char *name);

void empirical_search_analysis();


BigInt bigint_from_int(uint32_t value);

void bigint_free(BigInt *num);

void bigint_resize(BigInt *num, int new_count);

BigInt bigint_add(BigInt a, BigInt b);

BigInt bigint_sub(BigInt a, BigInt b);

BigInt bigint_mul(BigInt a, BigInt b);

BigInt bigint_square(BigInt a);

BigInt bigint_double(BigInt a);

void bigint_print(BigInt num);

BigInt fibonacci(int n);

void empirical_fibonacci_analysis();

void measure_with_qpc_inplace(void (*sort_func)(int *, int), int *arr, int size, const char *name);

#endif
