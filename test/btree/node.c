#include "node.h"

void BtreeInfo_init(BtreeInfo* this){
    this->root = NULL;
    this->num_nodes=0; 
}


void Node_init(Node* this, int num){
    this->num = num;
    this->isLeaf= 1;
    this->lnode = NULL;
    this->rnode = NULL;
}


void BtreeInfo_insert_node(BtreeInfo* this){
    Node* tmp = NULL;

    if(num_nodes == 0){
        this->root = (Node*) malloc(sizeof(Node));
        Node_init(this->root, 0);
    }
    else{
        tmp = this->root;               
        while(1){
            /*to go to next node  */
            if(tmp->isLeaf != 1){}   
            /* to create the new node */
            else
        }
    }

}


