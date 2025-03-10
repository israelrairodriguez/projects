#include <stdio.h>
#include <stdbool.h>
#include "paint.h"
#include <stdlib.h>

char* read_any_len_line() {
    /*
    Read a line of any length from the user input. 
    @returns: The next line of characters from the input stream.
    The newline character, while read, is not included in the returned string.
    @modifies: stdin
    */

    char *line = NULL; //creates a buffer as NULL so getline does it.
    size_t bufsize = 0;
    ssize_t line_length; 

    printf("Enter your command: ");
    line_length = getline(&line, &bufsize, stdin); //Gets the length and line as line
    line[line_length - 1] = '\0'; //Makes the last one null rmeoving the newline

    return line; // Returns line
}

void shift_rows_down(Canvas* original, int num_rows_to_add, int new_num_cols) {
    char** new_canvas = malloc((original->num_rows + num_rows_to_add) * sizeof(char*));

    for (int i = original->num_rows - 1; i >= 0; --i) {
        new_canvas[i + num_rows_to_add] = original->canvas[i];
    }

    for (int i = 0; i < num_rows_to_add; ++i) {
        new_canvas[i] = malloc(sizeof(char) * (original->num_columns + 1));

        for (int j = 0; j < new_num_cols; ++j) {
                new_canvas[i][j] = '*'; 
        }
    }

    free(original->canvas);  
    original->canvas = new_canvas;
    original->num_rows += num_rows_to_add;
}

void shift_rows_up(Canvas* original, int num_rows_to_add, int new_num_cols) {
    char** new_canvas = malloc((original->num_rows + num_rows_to_add) * sizeof(char*));

    for (int i = original->num_rows - 1; i >= 0; --i) {
        new_canvas[i - num_rows_to_add] = original->canvas[i];
    }

    for (int i = 0; i < num_rows_to_add; ++i) {
        new_canvas[i] = malloc(sizeof(char) * (new_num_cols));  
        for (int j = 0; j < new_num_cols; ++j) {
            new_canvas[i][j] = '*'; 
        }
    }

    for (int i = 0; i < original->num_rows; ++i) {
        free(original->canvas[i]);
    }

    free(original->canvas);

    original->canvas = new_canvas;
    original->num_rows += num_rows_to_add;
    original->num_columns = new_num_cols; 

    print_canvas(original);
}




