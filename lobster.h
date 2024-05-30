#ifndef LOBSTER_H
#define LOBSTER_H

#define MAX_NAME_LENGTH 100

#include <stdio.h>

typedef struct Lobster {
    unsigned long long size;
    unsigned long long value;
    char name[MAX_NAME_LENGTH];
} Lobster;

typedef struct Matrix {
    unsigned long long num_rows;
    unsigned long long num_cols;
    unsigned long long *elements;
} Matrix;

void set_matrix_value(Matrix* mat, unsigned long long row, unsigned long long col, unsigned long long value);
void dynamic_programming_lobster(Lobster lobster_list, unsigned long long num_lobsters, unsigned long long max_net_capacity, FILE output_file);
unsigned long long get_matrix_value(Matrix* mat, unsigned long long row, unsigned long long col);
unsigned long long get_max_value(unsigned long long val1, unsigned long long val2);

#endif
