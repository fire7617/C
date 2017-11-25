/*
 *to sort multiple partition that contain urls
 * */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "env.h"


typedef struct{
    int label;
    char* point;
}HeapNode;

typedef struct{
    char* startFlag;
    char* endFlag;
    FILE* fp;
    char* path;
}BlockInfo;

typedef struct{
    HeapNode* heapTree;
    BlockInfo* bi;
    char** flag; //to mark the current url
    int heapLen;
    char* mem;
    FILE* ofp;
    size_t blockSize;
    char* lastOutput;
}HeapInfo;

void HeapInfo_init( HeapInfo* this, int heapLen, char* mem, IMeg* imeg); //to initialize the Heap array
void HeapInfo_destruct( HeapInfo* this, int numBlocks);

void Heap_top_heapify( HeapInfo* this, IMeg* imeg);
void Heap_bottom_heapify( HeapInfo* this, int index, IMeg* imeg);
void Heap_pop( HeapInfo* this, IMeg* imeg ); //to pop the minimal url in the heap and wirte to file
void Heap_shift_down(HeapInfo* this);
int  Heap_reload_root( HeapInfo* this );// reload the data that locates in the partition

void HeapNode_swap(HeapNode* x, HeapNode* y);
void HeapNode_display(HeapNode* hn);

int strcompare(char* x, char* y, IMeg* imeg);
#endif







