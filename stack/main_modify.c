#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STACK 256 

void stack_push(char s, char *stack, int *ps);
char stack_pop(char *stack, int *ps);

/*main function */
int main(){
    char *data = "{{{{}}}}",
         tmp;

    char *stack;
    int  ps;
    int flag = -1;

    /*stack init*/
    stack = (char*) malloc(sizeof(char)*SIZE_STACK); 
    memset(stack, 0, sizeof(char)*SIZE_STACK);
    ps = SIZE_STACK;

    while( tmp = *data++ ){
        if(tmp == '{' || tmp == '(')
            stack_push(tmp, stack, &ps);
        else if(tmp == '}' && *(stack+ps) == '{')
                stack_pop(stack, &ps);
        else if( tmp == ')' && *(stack+ps) == '(')
                stack_pop(stack, &ps);
        else
            flag = 1; 
    }
   
    if(ps != SIZE_STACK || flag == 1)
        printf("error\n");
    else
        printf("success\n");
    return 0;  
     
}

void stack_push(char s,char *stack, int* ps){
    int tmp;

    tmp = *ps ;
    *(stack + tmp - 1)  = s;
    *ps -= 1;
}

char  stack_pop(char *stack, int *ps){
    int tmp;
    tmp = *ps;
    *ps += 1;
    
    return *(stack + tmp);
}
