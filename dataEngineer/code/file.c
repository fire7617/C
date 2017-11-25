#include "file.h"

void FileInfo_init(FileInfo *this){
    int i;
    this-> numFile = 0;

    this->filePath = (char**)malloc(sizeof(char*)*FILE_MAX_SIZE);
    for(i=0; i<FILE_MAX_SIZE; i++)
      this->filePath[i] = (char*)malloc(sizeof(char*)*PATH_MAX_LENGTH);

    this->fd = -1;
    this->curIndex = 0;
}

void FileInfo_setPath(FileInfo *this, const char *path){
    if(this->numFile < FILE_MAX_SIZE){
        strcpy(this->filePath[this->numFile],path);
        this->numFile ++;
    }
    else printf("====amount of  file exceeds\n=====");
}

void FileInfo_destruct(FileInfo *this){
    int i;

    for(i=0; i< this->numFile; i++) free( this->filePath[i]);
    free( this->filePath );
    this->filePath = NULL;

    this->numFile = 0;
}

void FileInfo_display(FileInfo *this){
    int i;

    for(i=0; i<this->numFile; i++)
        printf("%s\n", this->filePath[i]);
}

void FileInfo_changefd(FileInfo *this){
    if(this->fd != 0) close(this->fd);

    if( this->curIndex == this->numFile ) {
        this->fd = 0; 
        return;
    }
    if( (this->fd = open( this->filePath[this->curIndex++], O_RDONLY )) == -1){
        fprintf(stderr,"%s open error\n",this->filePath[this->curIndex-1]);
        exit(EXIT_FAILURE);
    } 

}

