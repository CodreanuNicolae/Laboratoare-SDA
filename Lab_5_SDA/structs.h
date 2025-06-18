#ifndef STRUCTS_H
#define STRUCTS_H

#define BIGINT_BASE 1000000000

typedef struct {
    uint32_t *digits;
    int count;
} BigInt;

#endif
