#ifndef _NODE_H_
#define _NODE_H_

typedef struct{
    int num;
    int  isLeaf;
    Node *lnode;
    Node *rnode;
}Node;

typedef struct{
    Node* root;
    unsigned int num_nodes;
}BtreeInfo;

// Node 
void Node_init(Node* this, int num);

// BtreeInfo
void BtreeInfo_init(BtreeInfo* this);

void BtreeInfo_insert_node(BtreeInfo* this);

#endif
