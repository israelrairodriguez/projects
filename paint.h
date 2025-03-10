#ifndef PAINT_H  /* Include guard */
#define PAINT_H

typedef struct{
    int num_rows;
    int num_columns;
    char** canvas;
} Canvas;

typedef struct{
    int row;
    int column;
} position;

typedef struct{
    int num_rows;
    int num_cols;
} size;


void shift_rows_down(Canvas* original, int num_rows_to_move, int new_num_cols);
void shift_rows_up(Canvas* original, int num_rows_to_move, int new_num_cols);
char* read_any_len_line();
void get_size_of_canvas(int argc, char* argv[], Canvas* original); 
void create_canvas(Canvas* original);
void print_canvas(Canvas* original);
void run_paint(Canvas* original);
void quit(Canvas* original);
void help();
void write(Canvas* original, char* input);
void erase(Canvas* original, char* input);
void resize(Canvas* original, char* input);

#endif //PAINT_H