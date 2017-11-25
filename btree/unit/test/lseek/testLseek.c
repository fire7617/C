#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

typedef struct stBT_NODE{
    int iNumber;
    int leaf;
} BT_NODE;

void Node_init(BT_NODE *this);
void Node_print(BT_NODE *this);
void write2File(BT_NODE *this);
void read2File(BT_NODE *buf, int iNumber);

char *nodeFileName = "bt.nodes";

int main(){
    BT_NODE root,buf; 

    Node_init(&root);
    root.iNumber = 10;
    root.leaf = 1;
    
    write2File(&root); 
    read2File(&buf,root.iNumber);
    Node_print(&buf);
    return 0;
}

void Node_init(BT_NODE *this){
    memset(this, 0, sizeof(BT_NODE)); 
}

void Node_print(BT_NODE *this){
    printf("iNumber:%d\n",this->iNumber);
    printf("leaf:%d\n",this->leaf);
}

void write2File(BT_NODE *this){
    int fd,
         nwrite;

    fd = open(nodeFileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    lseek(fd,sizeof(BT_NODE)*this->iNumber,SEEK_SET);
    if( (nwrite = write(fd, this,sizeof(BT_NODE))) <= 0 )
        printf("error %s\n",strerror(errno));
    else
        printf("writing file successes\n");
    close(fd);
}

void read2File(BT_NODE *buf, int iNumber){
    int fd,
        nread;
    
    fd = open(nodeFileName,O_RDONLY);
    lseek(fd,sizeof(BT_NODE)*iNumber,SEEK_SET);
    if( (nread = read(fd, buf, sizeof(BT_NODE))) < 0 )
        printf("error %s\n",strerror(errno));
    else
        printf("read file is successes\n");
    close(fd);
}
