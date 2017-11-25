#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "env.h"
#include "Node.h"
#include "info.h"

#define TRUE  1
#define FALSE 0

int nodeFd;
BT_INFO btInfo;

void insert_init(char *url);
void load_root_node(BT_NODE *node, BT_INFO *info);

int main(int argc, char **argv){
    char *url = "www.yahoo.com.tw";
     
    insert_init(url);
    
    return 0;
}

void insert_init(char *url){
    BT_NODE buf;

    info_loaded(&btInfo);
    load_root_node(&buf, &btInfo);
         
    if( buf.isLeaf == TRUE ){
        //copy url to node storage
        //insertion rule
    }
    else{
        //go to the next level node until finding the leaf 
    }
}

// load the root node from the file(NODE_FILE_NAME) 
void load_root_node(BT_NODE *buf, BT_INFO *info){
    if(btInfo.totalNode > 0){//rootNode does exist
        nodeFd = open(NODE_FILE_NAME,O_RDWR);
        Node_loaded(buf, info->rootInumber, nodeFd);
    }
    else{//root node doesn't exist
        //build rootNode
        Node_init(buf); 
        buf->isLeaf = TRUE;
    }
}
