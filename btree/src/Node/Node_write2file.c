
#include "Node.h"
/*
 *offset:the distance from beginning of the file 
 *       to position of targeted Node
 *fp : the file pointer that records the Node
 */
void Node_loaded(BT_NODE *buf, int offset, int fd){
    int nwrite;
    
    lseek(buf, offset, fd);
    if( (nwrite = write(fd, buf,sizeof(BT_NODE) )) <= 0 )
        printf("error:%s\n",strerror(errno));
}
