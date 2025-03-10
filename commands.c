#include <stdio.h>
#include <stdlib.h>
#include "paint.h"
#include "write.h"
#include <string.h>
#include <stdbool.h>

void quit(Canvas* original){

    for (int i = 0; i < original->num_rows; ++i){
        free(original->canvas[i]);
    }
    free(original->canvas);
    original->canvas = NULL;
}

void help(){
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

void write(Canvas* original, char* input){
    /*
    check direction
    do
    */
    direction* direction = NULL;
    direction = malloc(sizeof(*direction));
    find_direction(input, direction);
    
    if(direction->isHorizontal){
        draw_horizontal(original, direction);
    }
    else if(direction->isVertical){
        draw_verical(original, direction);
    }
    else if(direction->isDiagonal){
        draw_diagonal(original,direction);
    }
    else {
        printf("This is not a straight line.\n");
    }
    free(direction);
}

void erase(Canvas* original, char* input){
    position* erase = NULL; 
    erase = malloc(sizeof(*erase));
    erase->row =  original->num_rows - atoi(&input[2]) - 1;
    erase->column = atoi(&input[4]) + 1;

    original->canvas[erase->row][erase->column] = '*';

    free(erase);
}

void resize(Canvas* original, char* input) {
    int new_num_rows = atoi(&input[2]);
    int new_num_cols = atoi(&input[4]);
    bool increase_size = false;

    char** temp = realloc(original->canvas, new_num_rows * sizeof(char*));
    original->canvas = temp;

    if (new_num_rows > original->num_rows) {
        for (int i = original->num_rows; i < new_num_rows; i++) {
            original->canvas[i] = malloc(new_num_cols * sizeof(char));
            memset(original->canvas[i], 42, new_num_cols * sizeof(char));
            increase_size = true;
        }
    } else if (new_num_rows < original->num_rows) {
        for (int i = 0; i < original->num_rows - new_num_rows; i++) {
            free(original->canvas[i]); 
            
            for (int j = i + 1; j < original->num_rows; j++) {
                original->canvas[j - 1] = original->canvas[j];
            }
        }
        for (int i = 0; i < new_num_rows; i++) {
            original->canvas[i] = realloc(original->canvas[i], new_num_cols * sizeof(char));
            }
    }

    for (int i = 0; i < new_num_rows; i++) {
        if (i >= original->num_rows) {
            original->canvas[i] = malloc(new_num_cols * sizeof(char));
            memset(original->canvas[i], 42, new_num_cols * sizeof(char)); 
        } else {
            char* temp_row = realloc(original->canvas[i], new_num_cols * sizeof(char));
            original->canvas[i] = temp_row;

            if (new_num_cols > original->num_columns) {
                memset(&original->canvas[i][original->num_columns], 42, 
                       (new_num_cols - original->num_columns) * sizeof(char));
            }
        }
    }

    if(increase_size){
        int num_rows_to_move = new_num_rows - original->num_rows;
        shift_rows_down(original, num_rows_to_move, new_num_cols); 
    }
    original->num_rows = new_num_rows;
    original->num_columns = new_num_cols;
}