#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "env.h"

typedef struct{
    char **filePath;
    int numFile; // number of total files;

    int fd;
    int curIndex;

    int numBlock;//number of memory block
}FileInfo;

void FileInfo_init(FileInfo *this);
void FileInfo_setPath(FileInfo *this , const char *path);
void FileInfo_display(FileInfo *this);
void FileInfo_destruct(FileInfo *this);
void FileInfo_changefd(FileInfo *this);

#endif




