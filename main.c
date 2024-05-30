#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "lobster.h"

int main(int argc, char* argv[]) {

    // Variable declaration
    unsigned long long net_capacity, num_lobsters = 0;
    clock_t start_time, end_time;

    start_time = clock();

    FILE *input_file, *output_file;  // I/O files

    Lobster* lobster_list = malloc(sizeof(Lobster)); // Array to keep track of all available lobsters

    // I/O initialization
    input_file = fopen(argv[1], "r");
    output_file = fopen("output", "w");

    // Error handling
    if (argc != 2) {
        fprintf(stderr, "The program needs exactly one file as a command line argument");
        return 1;
    }

    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Failed to open files");
        return 2;
    }

    // Input
    fscanf(input_file, "%llu", &net_capacity);

    // Reading each lobster's attributes into the lobster list. It is assumed the input is correctly formatted
    while (fscanf(input_file, "%s %llu %llu",
                lobster_list[num_lobsters].name,
                &lobster_list[num_lobsters].size,
                &lobster_list[num_lobsters].value) != EOF) {
        if (lobster_list[num_lobsters].size <= net_capacity) { // Only consider the lobsters if they can fit in the net
            num_lobsters++;
            lobster_list = realloc(lobster_list, sizeof(Lobster) * (num_lobsters + 2));
        }
    }

    // Function call
    dynamic_programming_lobster(lobster_list, num_lobsters, net_capacity, output_file);

    end_time = clock();

    fprintf(output_file, "\n Time: %lf seconds", (double)((end_time - start_time)) / CLOCKS_PER_SEC);

    // Cleaning up
    free(lobster_list);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
