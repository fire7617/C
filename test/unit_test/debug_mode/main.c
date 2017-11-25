/*heap sort*/
#include <stdio.h>

#ifdef _UNIT_TEST_
    #include "CUnit/Basic.h"
#endif

#define SWAP(x,y)  {int tmp=x; x=y; y=tmp;}
#define MAX  10

void print_array(int* ele, int s_ele);
void heapify(int* ele, int s_ele);
int  heap_pop(int* ele, int* s_ele);
void heap_ajust(int* ele, int *s_ele, int adjustNode);

#ifdef _UNIT_TEST_
    void testHeap_pop(void){
        int i;
        int s_ele = 10;
        int ele[] = {0,1,2,3,4,5,6,7,8,9,10};
        
        for(i=0; i<10; i++)
           CU_ASSERT(i == heap_pop(ele, &s_ele));
    }

    void test(void){}
#endif

int main(void){
    int i;
    int ele[] = {1,8,10,8,7,8,4,6,9,5};
    int s_ele = 10;


    heapify(ele, s_ele);
    print_array(ele,s_ele);
    printf("\n");
//    print_array(ele,s_ele);
    for(i=0; i<10; i++)
        printf("%d\t",heap_pop(ele, &s_ele));
    printf("\n");


#ifdef _UNIT_TEST_
    printf("=============UNIT_TEST==========\n");
    CU_pSuite pSuite = NULL;

    if( CUE_SUCCESS != CU_initialize_registry() )
        return CU_get_error();

    pSuite = CU_add_suite("Suite1", 0, 0);
    if( NULL == pSuite){
        fprintf(stderr, "add registry cause error\n");
        CU_cleanup_registry();
        return CU_get_error();
    }

    if( NULL == CU_add_test(pSuite, "testHeap_pop", testHeap_pop) ){
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Suite2", 0 , 0);
    if( NULL == pSuite){
        fprintf(stderr, "add registry cause error\n");
        CU_cleanup_registry();
        return CU_get_error();
    }

    if( NULL == CU_add_test(pSuite, "test", test)){
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_basic_set_mode( CU_BRM_VERBOSE );
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
#endif

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
    int leftChildIndex  = adjustNode*2 + 1;
    int rightChildIndex = adjustNode*2 + 2;
   
    if(leftChildIndex < *s_ele && ele[leftChildIndex] <= ele[rightChildIndex] && ele[adjustNode] > ele[leftChildIndex]){
        SWAP(ele[adjustNode],ele[leftChildIndex]);
        heap_ajust(ele, s_ele, leftChildIndex);
    }

    else if( rightChildIndex < *s_ele && ele[rightChildIndex] <= ele[leftChildIndex] && ele[adjustNode] > ele[rightChildIndex]){
        SWAP(ele[adjustNode], ele[rightChildIndex]);
        heap_ajust(ele, s_ele, rightChildIndex);
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
