/***************************
 *              C Unit Test
 * Reference Home:  http://cunit.sourceforge.net/
 *****************************/
#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"

int init_suite(){return 0;}
int clean_suite(){return 0;}

int str_equ(char* a, char* b);

void test_unit1(void){
    char *a = "i love you";
    CU_ASSERT_STRING_EQUAL(a,a);
}
    
int main(){
    CU_pSuite pSuite = NULL;
    
    if( CUE_SUCCESS != CU_initialize_registry()){
        fprintf(stderr,"initialize registry cause error\n");
        return CU_get_error();
    }

    pSuite = CU_add_suite("Suite1",init_suite,clean_suite);
    if(NULL == pSuite){
        fprintf(stderr,"add registry cause error\n");
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(NULL == CU_add_test(pSuite, "test1",test_unit1)){
        fprintf(stderr,"test registry cause error\n");
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}


int str_equ(char* a, char* b){
    return strcmp(a,b);
}
