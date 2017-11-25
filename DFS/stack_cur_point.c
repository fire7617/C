#include "stack.h"

Point* stack_cur_point(Point* buf, int* b_size){
    int offset = *b_size;

    return (buf + offset);
}


