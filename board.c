#include <stdio.h>
#include <stdlib.h>
#include "paint.h"

void get_size_of_canvas(int argc, char* argv[], Canvas* original){
    if (argc == 1) {
        original->num_rows = 10;
        original->num_columns = 10;
    }
    else if (argc == 3){
        original->num_rows = atoi(argv[1]);
        original->num_columns = atoi(argv[2]);
    }
    else {
        printf("Too many arguments. Closing program.");
        exit(1);
    }
}

void create_canvas(Canvas* original){
    int num_rows = original -> num_rows + 1;
    int num_columns = original->num_columns + 1;

    original->canvas = malloc(num_rows* sizeof(char*));
    for (int i = 0; i < num_rows; ++i){
        original->canvas[i] = malloc(num_columns * sizeof(char));
    }

    for (int i = 0; i < num_rows; ++i) { 
        for (int j = 0; j < num_columns; ++j) { 
                original->canvas[i][j] = '*'; 
        }
    }

}

void print_canvas(Canvas* original) {
    int num_rows = original->num_rows;
    int num_columns = original->num_columns;

    for (int i = 0; i < num_rows; ++i) {
        printf("%3d", num_rows - i - 1);

        for (int j = 0; j < num_columns; ++j) {
            printf("%3c", original->canvas[i][j]);
        }
        printf("\n");
    }

    printf("   ");
    for (int j = 0; j < num_columns; ++j) {
        printf("%3d", j);  
    }
    printf("\n");
}

