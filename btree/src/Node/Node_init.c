#include "Node.h"

void Node_init(BT_NODE *this){
    
    memset(this, 0, sizeof(BT_NODE));
    /*
    int i;
   // this->iNumber = 0;
    //this->isLeaf = 0;
    
   for(i=0; i<2*MINIMUM_DEG-1; i++)
        memset(&this->pszaKeys[i], 0, sizeof(char)*MAX_URL_SIZE);

    memset(this->iaChildren, 0 ,sizeof(unsigned int)* 2*MINIMUM_DEG);
    */
}
