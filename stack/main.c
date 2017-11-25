#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STACK 10

void stack_push(char s, char *stack, int *ps);
char stack_pop(char *stack, int *ps);

/*main function */
int main(){
    int i; 
    char *data = "}}}}",
         tmp;

    char *stack;
    int  ps;
    int flag = -1;

    /*stack init*/
    stack = (char*) malloc(sizeof(char)*SIZE_STACK); 
    for(i=0; i<SIZE_STACK; i++) stack[i] = '0';
    ps = SIZE_STACK;

    while( tmp = *data++ ){
        if(tmp == '{' || tmp == '(')
            stack_push(tmp, stack, &ps);
        else if(tmp == '}'){
            if( *(stack + ps) == '{')
                stack_pop(stack, &ps);
            else{
                printf("{} error expression\n");
                flag = 1;
                break;
            }
        }
        else if( tmp == ')' ){
            if( *(stack + ps) == '(' )
                stack_pop(stack, &ps);
            else{
                printf("() error expression\n");
                flag = 1;
                break;
            }
        }
        else{printf("error\n");}
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
    *ps = *ps - 1;
}
char  stack_pop(char *stack, int *ps){
    int tmp;
    tmp = *ps;
    *ps = *ps + 1;
    
    return *(stack + tmp);
}
