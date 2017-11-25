#include "ref.h"

static void addOne(){
    a++;
}

void addTwo(){
    addOne();
    addOne();
}

void printIt(){
    printf("%d\n",a);
}

void testLseek(){
    char *fileName;
    FILE *fp;

    fileName = "out";
    fp = fopen(fileName,"a+");
    
    if(fp == NULL) 
      printf("file not found\n");
    else{
        fseek(fp,0L,SEEK_SET);
        printf("the file length  bytes\n" );
    }


}
