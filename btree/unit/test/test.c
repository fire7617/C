#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "ref.h"



int main(void)
{
    addTwo();
    printIt();
    /*
    char *buf = malloc(sizeof(char) * 128);
    strcpy(buf,"i am good");
     
    printf("%s\n",buf);
    /*
    FILE *fp;
    char *buf;
    int bytes = 100;
    
    fp = fopen("./url.txt","r");
    buf = (char*) malloc(sizeof(char)*100);
//    while(getline( &buf, 100,fp) != -1)
    if(getline(&buf, &bytes ,fp) > 0)
      printf("%s\n",buf);

    fclose(fp);
    */
    return 0;
}
