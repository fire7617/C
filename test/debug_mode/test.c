#include <stdio.h>

#ifdef _DEBUG
#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
#define DEBUG(args...)
#endif

int main(){

    DEBUG("Debugging Mode was enabled\n");

#ifdef _DEBUG
    printf("test success\n");
#endif

    return 0;
}
