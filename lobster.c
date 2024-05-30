#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "lobster.h"

// Matricial functions
void set_matrix_value(Matrix *mat, unsigned long long row, unsigned long long col, unsigned long long value) {
    unsigned long pos = row * mat->num_cols + col;
    *(mat->elements + pos) = value;
}

unsigned long long get_matrix_value(Matrix *mat, unsigned long long row, unsigned long long col) {
    return *(mat->elements + row * mat->num_cols + col);
}

unsigned long long get_max_value(unsigned long long val1, unsigned long long val2) {
    return (val1 > val2) ? val1 : val2;
}

void dynamic_programming_lobster(Lobster lobster_list, unsigned long long num_lobsters, unsigned long long max_net_capacity, FILE output_file) {
    Matrix dp_matrix;
    unsigned long long lobster_idx;
    unsigned long long capacity_idx;
    unsigned long long optimal_value;
    unsigned long long remaining_capacity;
    unsigned long long current_lobster;

    dp_matrix.num_rows = num_lobsters + 1;
    dp_matrix.num_cols = max_net_capacity + 1;

    dp_matrix.elements = malloc((dp_matrix.num_rows) * (dp_matrix.num_cols) * sizeof(unsigned long long));

    // DP Algorithm
    for (lobster_idx = 0; lobster_idx <= num_lobsters; lobster_idx++) {
        for (capacity_idx = 0; capacity_idx <= max_net_capacity; capacity_idx++) {
            if (capacity_idx == 0 || lobster_idx == 0) {
                set_matrix_value(&dp_matrix, lobster_idx, capacity_idx, 0);
            } else if (lobster_list[lobster_idx - 1].size <= capacity_idx) {
                set_matrix_value(&dp_matrix, lobster_idx, capacity_idx,
                    get_max_value(
                        lobster_list[lobster_idx - 1].value +
                        get_matrix_value(&dp_matrix, lobster_idx - 1, capacity_idx - lobster_list[lobster_idx - 1].size),
                        get_matrix_value(&dp_matrix, lobster_idx - 1, capacity_idx)
                    )
                );
            } else {
                set_matrix_value(&dp_matrix, lobster_idx, capacity_idx, get_matrix_value(&dp_matrix, lobster_idx - 1, capacity_idx));
            }
        }
    }

    optimal_value = get_matrix_value(&dp_matrix, dp_matrix.num_rows - 1, dp_matrix.num_cols - 1);

    remaining_capacity = dp_matrix.num_cols - 1;
    current_lobster = dp_matrix.num_rows - 1;

    // Getting used elements
    while (current_lobster != 0 && remaining_capacity != 0) {
        if (get_matrix_value(&dp_matrix, current_lobster, remaining_capacity) != get_matrix_value(&dp_matrix, current_lobster - 1, remaining_capacity)) {
            fprintf(output_file, "%s\n", lobster_list[current_lobster - 1].name);
            remaining_capacity = (remaining_capacity > lobster_list[current_lobster - 1].size) ? remaining_capacity - lobster_list[current_lobster - 1].size : 0;
        }
        current_lobster--;
    }

    free(dp_matrix.elements);

    fprintf(output_file, "\n=== Value in the knapsack %llu ===", optimal_value);
}
