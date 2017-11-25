#ifndef _MEM_H_
#define _MEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#include "env.h"
#include "main.h"

#define INFO_OUT "meminfo.out"
#define MEM_OUT  "mem.data"

#define MEM_MAX_BLOCK 3 //10^3 maximum of mem block

#define TRUE 1
#define FALSE 0

 typedef struct{
    char *addr;
    int  len;
}DataPoint;

typedef struct{
    char *mem;
    char *pb;
    char *pbEnd;

    char* datablockFlag;
    DataPoint* addrblockFlag;
    int numData;
}MemInfo;

void MemInfo_init(MemInfo* this, char* mem, size_t memSize);
void MemInfo_destruct(MemInfo* this);
void MemInfo_save(MemInfo* this);
void MemInfo_load(MemInfo* this);
void MemInfo_display(MemInfo *this);
void MemInfo_reset(MemInfo* this);

void Mem_save(MemInfo* this,int numEntry, int* numMemBlock);
void Mem_display(MemInfo* this);
int  Mem_is_enough(MemInfo* this);
void Mem_sort(MemInfo* this, IMeg* img);
void Mem_save_entry(MemInfo* this, char** startFlag, char** dot);
int minstrcompare(const void* p1, const void* p2);
int maxstrcompare(const void* p1, const void* p2 );
int minstrcasecompare(const void* p1, const void* p2);
int maxstrcasecompare(const void* p1, const void* p2);
#endif 
