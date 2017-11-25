#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "env.h"

#define NODE_FILE_NAME "bt.node"

typedef struct stBT_NODE{
    int iNumber;
    int isLeaf;
    char pszaKeys[2*MINIMUM_DEG-1][MAX_URL_SIZE];
    unsigned int iaChildren[2*MINIMUM_DEG];
    char pszPadding[PADDING];
}BT_NODE;



/**************
 * initialize Node 
 ************* */
void Node_init(BT_NODE *this);
/***************
 * get variable of Node
 ****************/
int Node_getINumber(BT_NODE *this);
int Node_getIsLeadf(BT_NODE *this);
char** Node_getPszaKeys(BT_NODE *this);
unsigned int Node_getChild(BT_NODE *this ,unsigned int childIndex);
/****
 *Load Node
 */

void Node_loaded(BT_NODE *buf, int offset, int fd);
void Node_write2file(BT_NODE *buf, int offset, int fd);
/***************
 *check Node 
 ***************/
int Node_isFull(BT_NODE *this);
/*****************
 *print Node
 *******************/
void Node_display(BT_NODE *this);

void Node_save(BT_NODE *this, char *fileName);
#endif 
