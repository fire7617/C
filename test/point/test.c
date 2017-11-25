#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE 1024

struct Contain{
    int a;
    char b;
};

int main(){
    
    char a[ARRAY_SIZE];
    
    int *b = (int*) malloc(sizeof(int)*ARRAY_SIZE);
    struct Contain con;
    char *b2  = a;

    con.a = 10;
    con.b = 'a';

    printf("%ld %ld %ld\n",sizeof(a),sizeof(b),sizeof(struct Contain));
    printf("%ld %ld    \n", sizeof(*a),sizeof(*b2));
    return 0;
}
