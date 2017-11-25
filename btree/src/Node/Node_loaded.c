#include "Node.h"
/*
 *offset:the distance from beginning of the file 
 *       to position of targeted Node(BT_NODE)
 *fp : the file pointer that records the Node
 */
void Node_loaded(BT_NODE *buf, int offset, int fd){
    int nread;
    
    lseek(buf, offset*sizeof(BT_NODE), fd);
    if( (nread = read(fd, buf,sizeof(BT_NODE) )) <= 0 )
        printf("error:%s\n",strerror(errno));
}
