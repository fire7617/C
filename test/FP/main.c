#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(a,b) {int tmp=a; a=b; b=tmp;}

typedef void (*List_operate)(int*,int);

int compare_int(const void*, const void*);

void list_generate(int* u, int u_size);
void list_random  (int* u, int u_size);
void list_sort    (int* u, int u_size);
void list_print   (int* u, int u_size);

int main(int argc, char** argv){
    int i;
    int lo_size = 0;
    List_operate lo[4];
    memset( lo, 0, sizeof(void*)*4);
//init operate
    int *u = (int*)malloc(sizeof(int) * 10);
    int u_size = 10;

    lo[lo_size++] = &list_generate;
    lo[lo_size++] = &list_random;
    lo[lo_size++] = &list_sort;
    lo[lo_size++] = &list_print;
    //rlo_sizeun operation
    //
    for(i=0; i<4; i++)
        (*lo[i])(u, u_size);
   
    if(u != NULL) { free(u); u = NULL; }
    return 0;
}

int compare_int(const void* a, const void* b){
    return *(const int*)a-*(const int*)b;    
}

void list_generate(int* u, int u_size){
    int i;
    for(i=0; i<u_size; i++) u[i] = i;
    printf("generate\n");
    for(i=0; i<u_size; i++) printf("%d\t",u[i]);
    printf("\n");
}

void list_random(int* u, int u_size){
    int i,r = rand()%u_size;

    for(i=0; i<u_size; i++,r=rand()%u_size)  SWAP(u[i],u[r]);
    printf("list_random\n");
    for(i=0; i<u_size; i++) printf("%d\t",u[i]);
    printf("\n");
}

void list_sort(int* u, int u_size){
    qsort( u, u_size, sizeof(int), compare_int);
}

void list_print(int* u, int u_size){
    int i;
    printf("list_print\n");
    for(i=0; i<u_size; i++)
        printf("%d\t",u[i]);
    printf("\n");
}
