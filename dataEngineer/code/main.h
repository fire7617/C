#ifndef _MAIN_H_
#define _MAIN_H_

#include <string.h>
#include "env.h"

typedef struct{
    size_t memSize;
    int unique;
    int increase;
    int sensitive;
    char outputFile[FILENAME_MAX_LENGTH];
} IMeg;

#endif
