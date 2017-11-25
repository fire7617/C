#include "Node.h"

/****************************
 * Get variable 
 **************************/
int Node_getINumber(BT_NODE *this){
    return this->iNumber;
}

int Node_getIsLeadf(BT_NODE *this){
    return this->isLeaf;
}

char** Node_getPszaKeys(BT_NODE *this){
    return (char**)this->pszaKeys;
}

unsigned int Node_getChild(BT_NODE *this, unsigned int childIndex){
    return this->iaChildren[childIndex];
}

/*********************************
 *Check Node
 *********************************/
int Node_isFull(BT_NODE *this){
    return (this->iNumber == (2*MINIMUM_DEG -1))?1:0;
}
/****************
 * Print Node
 ***************/
void Node_display(BT_NODE *this){
    int i;
    
    printf("=======================================\n");
    printf("iNumber:%d\nisLeadf:%d\n",this->iNumber,this->isLeaf);
    for(i=0; i<2*MINIMUM_DEG; i++)
        printf("%d:%d\n",i,this->iaChildren[i]);
    printf("=======================================\n");
}

void Node_save(BT_NODE *this, char *fileName){
     FILE *outFile = fopen(fileName,"a");

     fwrite(this, sizeof(BT_NODE), 1, outFile);
     fclose(outFile);
}
/*
void Node_save_modify(BT_NODE *this, int number){
    char *outFileName;
    FILE *outStream;
    off_t  

    outFileName = "out2";
    outStream = fopen(outFileName,"w+");
}
*/
