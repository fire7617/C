#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>

#define MAX_STACK_SIZE 100

typedef struct{
    int x;
    int y;
}Point;


Point* stack_cur_poit(Point* buf, int* b_size);
void stack_push(Point* buf, int* b_size, Point* dot);
void stack_pop(Point* buf, int* b_size);

#endif
