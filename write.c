#include <stdio.h>
#include <stdbool.h>
#include "write.h"
#include "paint.h"
#include <stdlib.h>

bool is_going_down_swapped(direction* direction){
    int swapper = direction->start_row;
    direction->start_row = direction->end_row;
    direction->end_row = swapper;

    swapper = direction->start_column;
    direction->start_column = direction->end_column;
    direction->end_column = swapper;
    if(direction->start_row > direction->end_row){
        return true;
    }
    else {
        return false;
    }

}

bool is_going_down(direction* direction){
    if(direction->start_row > direction->end_row){
        return true;
    }
    else {
        return false;
    }

}

bool check_if_diagonal(direction* direction){
    if(is_going_down(direction) || (is_going_down_swapped(direction))){
        int distance = direction->start_row - direction->end_row;
        if(direction->start_row - distance == direction->end_row && 
           direction->start_column + distance == direction->end_column){
            return true;
        }
        else {
                int swapper = direction->start_row;
                direction->start_row = direction->end_row;
                direction->end_row = swapper;

                swapper = direction->start_column;
                direction->start_column = direction->end_column;
                direction->end_column = swapper;
            if(direction->start_row + distance == direction->end_row && 
            direction->start_column + distance == direction->end_column){
                return true;
            }
            else {
                return false;
            }
        }
        
    }
    return false;
}

void find_direction(char* input, direction* direction){
    direction->start_row = atoi(&input[2]);
    direction->start_column = atoi(&input[4]);
    direction->end_row = atoi(&input[6]);
    direction->end_column = atoi(&input[8]);

    direction->isHorizontal = false;
    direction->isVertical = false;
    direction->isDiagonal = false;

    if (direction->start_row == direction->end_row){
        if(direction->end_column < direction->start_column){
            int swapper = direction->end_column;
            direction->end_column = direction->start_column;
            direction->start_column = swapper;
        }
        direction->isHorizontal = true;
    }
    else if (direction->start_column == direction->end_column){
        if(direction->end_row > direction->start_row){
            int swapper = direction->end_row;
            direction->end_row = direction->start_row;
            direction->start_row = swapper;
        }
        direction->isVertical = true;
    }
    else {
        if(check_if_diagonal(direction)){
            direction->isDiagonal = true;
        }

    }
}

void draw_horizontal(Canvas* original, direction* direction){
    int start_row = direction->start_row + 1;
    int num_to_draw = direction->end_column - direction->start_column + 1;
    int start_column = direction->start_column;

    for (int i = 0; i < num_to_draw; ++i){
        if(original->canvas[original->num_rows - start_row][start_column+ i] == '|' ||
           original->canvas[original->num_rows - start_row][start_column+ i] == '\\'||
           original->canvas[original->num_rows - start_row][start_column+ i] == '/' ||
           original->canvas[original->num_rows - start_row][start_column+ i] == '+' ){
            
            original->canvas[original->num_rows - start_row][start_column+ i]  = '+';
        }
        else{
            original->canvas[original->num_rows - start_row][start_column+ i] = '-';
        }
    }
}

void draw_verical(Canvas* original, direction* direction){
    int start_column = direction->start_column;
    int num_to_draw = direction->start_row - direction->end_row + 1;
    int start_row = original->num_rows - direction->start_row - 1;

    for (int i = 0; i < num_to_draw; ++i){
        if(original->canvas[start_row + i][start_column] == '-' ||
           original->canvas[start_row + i][start_column] == '\\'   ||
           original->canvas[start_row + i][start_column] == '/'    ||
           original->canvas[start_row + i][start_column] == '+'    ){
            
            original->canvas[start_row + i][start_column] = '+';
        }
        else{
            original->canvas[start_row + i][start_column] = '|';
        }
    }
}

void draw_diagonal(Canvas* original, direction* direction){
    if(is_going_down(direction)){
        int start_row = original->num_rows - direction->start_row - 1;
        int num_to_draw = direction->start_row - direction->end_row + 1;

        for(int i = 0; i < num_to_draw; ++i){
            if(original->canvas[start_row + i][direction->start_column + i] == '-'  ||
                original->canvas[start_row + i][direction->start_column + i] == '|' ||
                original->canvas[start_row + i][direction->start_column + i] == '/' ||
                original->canvas[start_row + i][direction->start_column + i] == '+' ){

                    original->canvas[start_row + i][direction->start_column + i] = '+';
               }
            else{
                original->canvas[start_row + i][direction->start_column + i] = '\\';
               }
        }
    }
    else {
        int start_row = original->num_rows - direction->start_row - 1;
        int num_to_draw = direction->end_row - direction->start_row + 1;
        
        for(int i = 0; i < num_to_draw; ++i){
            if(original->canvas[start_row - i][direction->start_column + i] == '-' ||
               original->canvas[start_row - i][direction->start_column + i] == '|' ||
               original->canvas[start_row - i][direction->start_column + i] == '\\'|| 
               original->canvas[start_row - i][direction->start_column + i] == '+') {
                
                    original->canvas[start_row - i][direction->start_column + i] = '+';
            }
            else{
                original->canvas[start_row - i][direction->start_column + i] = '/';
            }
        }
    }
}