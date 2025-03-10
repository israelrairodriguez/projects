#ifndef WRITE_H  /* Include guard */
#define WRITE_H

#include <stdbool.h>
#include "paint.h"

typedef struct{
    int start_row;
    int start_column;
    int end_row;
    int end_column;
    bool isDiagonal;
    bool isHorizontal;
    bool isVertical;
} direction;

bool is_going_down_swapped(direction* direction);
bool is_going_down(direction* direction);
bool check_if_diagonal(direction* direction);
void find_direction(char* input, direction* direction);
void draw_horizontal(Canvas* original, direction* direction);
void draw_verical(Canvas* original, direction* direction);
void draw_diagonal(Canvas* original, direction* direction);

#endif //WRITE_H