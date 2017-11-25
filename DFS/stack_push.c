#include "stack.h"

void stack_push(Point* buf, int* b_size, Point* dot){
    if(*b_size == MAX_STACK_SIZE -1 ){
        printf("stack full\n"); 
        return;
    }

    (*b_size)++;
    (buf + *b_size) -> x = dot->x;
    (buf + *b_size) -> y = dot->y;

} 
