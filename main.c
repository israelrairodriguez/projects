#include <stdio.h>
#include <stdlib.h>
#include "paint.h"
#include "write.h"

int main(int argc, char *argv[]){
    Canvas original;
    
    get_size_of_canvas(argc, argv, &original);
    create_canvas(&original);

    run_paint(&original);
    
    return 0;
}