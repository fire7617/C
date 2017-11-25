/*heap sort*/
#include <stdio.h>

#define SWAP(x,y)  {int tmp=x; x=y; y=tmp;}
#define MAX  10

void print_array(int* ele, int s_ele);
void heapify(int* ele, int s_ele);
int  heap_pop(int* ele, int* s_ele);
void heap_ajust(int* ele, int *s_ele, int adjustNode);

int main(void){
    int i;
    int ele[] = {1,8,10,8,7,8,4,6,9,5};
    int s_ele = 10;

    heapify(ele, s_ele);
    print_array(ele,s_ele);
//    printf("\n");
    
    for(i=0; i<10; i++)
        printf("%d\t",heap_pop(ele, &s_ele));
    return 0;
}

void heapify(int *ele, int s_ele){
    int i;
    int c,p;

    c = p = 0; /* c:New Node  p:the parent node*/
    for(i=0; i<s_ele; i++, c=i, p = (c-1)/2 ){
        while( c != 0 ){
            if( ele[c] < ele[p] ){
                SWAP( ele[c], ele[p] );
                c = p;
                p = (p- 1)/2;
            }
            else break;
        }
    } 
}

void heap_ajust(int* ele, int* s_ele, int adjustNode){
    int childIndex  = adjustNode*2 + 1;
    
    while( (adjustNode *2 + 1 ) <  *s_ele){
        childIndex = adjustNode *2 + 1;
        if( (childIndex + 1) < *s_ele && ele[childIndex] > ele[childIndex+1])
            childIndex ++;
        if( ele[childIndex] < ele[adjustNode] ){
            SWAP(ele[childIndex], ele[adjustNode]);
            adjustNode = childIndex;
        }
        else return;
    }
}

int heap_pop(int* ele, int* s_ele){
    int rootValue = ele[0];
    
    ele[0] = ele[*s_ele - 1];
    (*s_ele)--;
    heap_ajust(ele, s_ele, 0);
//    print_array(ele, *s_ele);

    return rootValue;
}

void print_array(int *ele,  int s_ele){
    int i;

    for(i=0; i<s_ele; i++)
        printf("%d\t",ele[i]);
    printf("\n");
}
