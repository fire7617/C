#include <stdio.h>
#include <string.h>
#include "env.h"

typedef struct stBT_NODE{
    int iNumber;
    int isLeaf;
    char pszaKeys[2*MINIMUM_DEG-1][MAX_URL_SIZE];
    unsigned int iaChildren[2*MINIMUM_DEG];
    char pszPadding[PADDING];
}BT_NODE;

void Node_init(BT_NODE *this);

int main(){
    int i;

    BT_NODE root;
    Node_init(&root);

    printf("%d\n",root.iNumber);
    
    for(i=0; i<MINIMUM_DEG*2; i++)
        printf("%d\n",root.iaChildren[i]);

    for(i=0; i< MINIMUM_DEG*2-1;i++)
        printf("%s\n",root.pszaKeys[i]);
    return 0;
}

void Node_init(BT_NODE *this){
    int i;

    this->iNumber = 0;
    this->isLeaf = 0;
    
    for(i=0; i<2*MINIMUM_DEG-1; i++)
        memset(this->pszaKeys[i], 0, sizeof(char)*MAX_URL_SIZE);
    memset(this->iaChildren, 0 ,sizeof(unsigned int)* 2*MINIMUM_DEG);
}

