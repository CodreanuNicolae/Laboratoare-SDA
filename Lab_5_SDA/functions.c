#include "functions.h"
#include "structs.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

BigInt bigint_from_int(uint32_t value) {
    BigInt num;
    if (value == 0) {
        num.digits = (uint32_t *) malloc(sizeof(uint32_t));
        num.digits[0] = 0;
        num.count = 1;
    } else {
        num.digits = (uint32_t *) malloc(sizeof(uint32_t));
        num.digits[0] = value;
        num.count = 1;
    }
    return num;
}

void bigint_free(BigInt *num) {
    if (num->digits) {
        free(num->digits);
        num->digits = NULL;
        num->count = 0;
    }
}

void bigint_resize(BigInt *num, int new_count) {
    num->digits = (uint32_t *) realloc(num->digits, new_count * sizeof(uint32_t));
    if (new_count > num->count) {
        memset(num->digits + num->count, 0, (new_count - num->count) * sizeof(uint32_t));
    }
    num->count = new_count;
}

BigInt bigint_add(BigInt a, BigInt b) {
    int max_count = (a.count > b.count) ? a.count : b.count;
    BigInt result;
    result.digits = (uint32_t *) calloc(max_count + 1, sizeof(uint32_t));
    result.count = max_count + 1;

    uint64_t carry = 0;
    for (int i = 0; i < max_count; i++) {
        uint64_t sum = carry;
        if (i < a.count) sum += a.digits[i];
        if (i < b.count) sum += b.digits[i];

        result.digits[i] = sum % BIGINT_BASE;
        carry = sum / BIGINT_BASE;
    }

    if (carry) {
        result.digits[max_count] = carry;
    } else {
        result.count = max_count;
    }

    return result;
}

BigInt bigint_sub(BigInt a, BigInt b) {
    BigInt result;
    result.digits = (uint32_t *) calloc(a.count, sizeof(uint32_t));
    result.count = a.count;

    int borrow = 0;
    for (int i = 0; i < a.count; i++) {
        int64_t diff = (int64_t) a.digits[i] - borrow;
        if (i < b.count) diff -= b.digits[i];

        if (diff < 0) {
            diff += BIGINT_BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits[i] = diff;
    }

    int new_count = a.count;
    while (new_count > 1 && result.digits[new_count - 1] == 0) {
        new_count--;
    }
    bigint_resize(&result, new_count);

    return result;
}

BigInt bigint_mul(BigInt a, BigInt b) {
    BigInt result;
    result.digits = (uint32_t *) calloc(a.count + b.count, sizeof(uint32_t));
    result.count = a.count + b.count;

    for (int i = 0; i < a.count; i++) {
        uint64_t carry = 0;
        for (int j = 0; j < b.count; j++) {
            uint64_t product = (uint64_t) a.digits[i] * b.digits[j] + result.digits[i + j] + carry;
            result.digits[i + j] = product % BIGINT_BASE;
            carry = product / BIGINT_BASE;
        }

        int pos = i + b.count;
        while (carry > 0) {
            uint64_t sum = result.digits[pos] + carry;
            result.digits[pos] = sum % BIGINT_BASE;
            carry = sum / BIGINT_BASE;
            pos++;
        }
    }

    int new_count = result.count;
    while (new_count > 1 && result.digits[new_count - 1] == 0) {
        new_count--;
    }
    bigint_resize(&result, new_count);

    return result;
}

BigInt bigint_square(BigInt a) {
    return bigint_mul(a, a);
}


BigInt bigint_double(BigInt a) {
    return bigint_add(a, a);
}


void bigint_print(BigInt num) {
    printf("%u", num.digits[num.count - 1]);


    for (int i = num.count - 2; i >= 0; i--) {
        printf("%09u", num.digits[i]);
    }
}


BigInt fibonacci(int n) {
    if (n == 0) return bigint_from_int(0);

    BigInt a = bigint_from_int(0);
    BigInt b = bigint_from_int(1);


    int mask = 1;
    while (mask <= n) mask <<= 1;
    mask >>= 1;

    while (mask) {
        BigInt two_b = bigint_double(b);
        BigInt two_b_minus_a = bigint_sub(two_b, a);
        BigInt a_sq = bigint_square(a);
        BigInt b_sq = bigint_square(b);


        BigInt new_a = bigint_mul(a, two_b_minus_a);
        BigInt new_b = bigint_add(a_sq, b_sq);


        bigint_free(&two_b);
        bigint_free(&two_b_minus_a);
        bigint_free(&a_sq);
        bigint_free(&b_sq);
        bigint_free(&a);
        bigint_free(&b);

        a = new_a;
        b = new_b;


        if (n & mask) {
            BigInt next = bigint_add(a, b);
            bigint_free(&a);
            a = b;
            b = next;
        }

        mask >>= 1;
    }

    bigint_free(&b);
    return a;
}

void display_arr(int *arr, int size) {
    int limit = size > 100 ? 100 : size;
    for (int i = 0; i < limit; i++) {
        printf("%d ", arr[i]);
    }
}

void initialize_arr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
    is_sorted = false;
}

void free_memory(int **arr) {
    if (*arr != NULL) {
        free(*arr);
        *arr = NULL;
        size = 0;
        is_sorted = false;
    }
}

void bubble_sort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return i + 1;
}

void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void quick_sort_wrapper(int *arr, int size) {
    quick_sort(arr, 0, size - 1);
}

double measure_sort_time(void (*sort_func)(int *, int), int *arr, int size) {
    int *copy = (int *) malloc(size * sizeof(int));
    if (!copy) {
        exit(1);
    }
    memcpy(copy, arr, size * sizeof(int));

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    sort_func(copy, size);

    QueryPerformanceCounter(&end);
    free(copy);

    return (double) (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;
}

void empirical_sort_analysis() {
    int test_sizes[] = {100, 1000, 10000, 50000, 100000};
    int n_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
    double bubble_times[n_tests];
    double quick_times[n_tests];

    for (int i = 0; i < n_tests; i++) {
        int N = test_sizes[i];
        fflush(stdout);

        int *test_arr = (int *) malloc(N * sizeof(int));
        if (!test_arr) {
            exit(1);
        }
        initialize_arr(test_arr, N);

        if (N <= 10000) {
            bubble_times[i] = measure_sort_time(bubble_sort, test_arr, N);
            printf("Bubble: %.2f us, ", bubble_times[i]);
        } else {
            bubble_times[i] = -1;
            printf("Bubble: skipped, ");
        }

        quick_times[i] = measure_sort_time(quick_sort_wrapper, test_arr, N);
        printf("Quick: %.2f us\n", quick_times[i]);

        free(test_arr);
    }

    printf("\nSorting times (microseconds):\n");
    printf("Array size (N)\t");
    for (int i = 0; i < n_tests; i++) {
        printf("%d\t\t", test_sizes[i]);
    }

    printf("\nBubble sort\t");
    for (int i = 0; i < n_tests; i++) {
        if (bubble_times[i] >= 0) {
            printf("%.2f\t\t", bubble_times[i]);
        } else {
            printf("N/A\t\t");
        }
    }

    printf("\nQuick sort\t");
    for (int i = 0; i < n_tests; i++) {
        printf("%.2f\t\t", quick_times[i]);
    }
    printf("\n");
}

void measure_with_qpc_inplace(void (*sort_func)(int *, int), int *arr, int size, const char *name) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    sort_func(arr, size);

    QueryPerformanceCounter(&end);
    double microseconds = (double) (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;

    printf("%s completed in %.2f microseconds.\n", name, microseconds);
}

int linear_search(int *arr, int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

int binary_search(int *arr, int size, int key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void measure_search(int (*search_func)(int *, int, int), int *arr, int size, int key, const char *name) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    int index = search_func(arr, size, key);

    QueryPerformanceCounter(&end);
    double microseconds = (double) (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;

    if (index >= 0) {
        printf("%s: Found %d at index %d.\n", name, key, index);
    } else {
        printf("%s: %d not found in the array.\n", name, key);
    }
    printf("%s completed in %.2f microseconds.\n", name, microseconds);
}

double measure_time_linear_search(int *arr, int size, int *keys, int num_searches) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < num_searches; i++) {
        volatile int idx = linear_search(arr, size, keys[i]);
        (void) idx;
    }

    QueryPerformanceCounter(&end);
    return (double) (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;
}

double measure_time_binary_search(int *arr, int size, int *keys, int num_searches) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < num_searches; i++) {
        volatile int idx = binary_search(arr, size, keys[i]);
        (void) idx;
    }

    QueryPerformanceCounter(&end);
    return (double) (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;
}

void empirical_search_analysis() {
    int test_sizes[] = {100, 1000, 10000, 100000};
    int n_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
    const int num_searches = 10000;

    double linear_times[n_tests];
    double binary_times[n_tests];


    for (int i = 0; i < n_tests; i++) {
        int N = test_sizes[i];
        int *test_arr = (int *) malloc(N * sizeof(int));
        if (!test_arr) {
            exit(1);
        }

        initialize_arr(test_arr, N);
        quick_sort_wrapper(test_arr, N);

        int *search_keys = (int *) malloc(num_searches * sizeof(int));
        if (!search_keys) {
            free(test_arr);

            exit(1);
        }
        for (int k = 0; k < num_searches; k++) {
            search_keys[k] = rand() % 1000;
        }

        linear_times[i] = measure_time_linear_search(test_arr, N, search_keys, num_searches);
        binary_times[i] = measure_time_binary_search(test_arr, N, search_keys, num_searches);

        free(test_arr);
        free(search_keys);

        printf("N=%d done.\n", N);
    }

    printf("\nSearch time (microseconds) for 10,000 searches:\n");
    printf("N\t");
    for (int i = 0; i < n_tests; i++) printf("%d\t", test_sizes[i]);
    printf("\nLinear Search\t");
    for (int i = 0; i < n_tests; i++) printf("%.2f\t", linear_times[i]);
    printf("\nBinary Search\t");
    for (int i = 0; i < n_tests; i++) printf("%.2f\t", binary_times[i]);
    printf("\n");
}

void empirical_fibonacci_analysis() {
    int test_values[] = {50, 100, 1000, 10000, 100000, 1000000};
    int n_tests = sizeof(test_values) / sizeof(test_values[0]);
    double times[n_tests];


    for (int i = 0; i < n_tests; i++) {
        int n = test_values[i];
        printf("Computing Fibonacci(%d)...", n);
        fflush(stdout);

        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);

        BigInt fib = fibonacci(n);

        QueryPerformanceCounter(&end);
        double microseconds = (double) (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;
        times[i] = microseconds;

        bigint_free(&fib);

        printf(" done in %.2f microseconds\n", microseconds);
    }

    printf("\nFibonacci computation times:\n");
    printf("N\t\t");
    for (int i = 0; i < n_tests; i++) {
        printf("%d\t\t", test_values[i]);
    }
    printf("\nTime (us)\t");
    for (int i = 0; i < n_tests; i++) {
        printf("%.2f\t", times[i]);
    }
    printf("\n");
}
