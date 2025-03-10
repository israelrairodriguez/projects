#include "paint.h"
#include <stdbool.h>
#include <stdio.h>

void run_paint(Canvas* original){
    bool is_running = true;

    while(is_running){
        print_canvas(original);
        char* input = read_any_len_line();
        switch(input[0]){
            case 'q': 
                quit(original);
                is_running = false;
                break;
            case 'h':
                help();
                break;
            case 'w':
                write(original, input);
                break;
            case 'e':
                erase(original, input);
                break;
            case 'r':
                resize(original, input);
                break;
            case 'a':
            case 'd':
            case 's':
            case 'l':
                break;
            default:
            printf("Unrecognized command. Type h for help.\n");
        }
    }
}