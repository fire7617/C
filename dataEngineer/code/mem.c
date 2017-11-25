#include "mem.h"

void MemInfo_init(MemInfo *this, char* mem, size_t memSize){
    this-> mem = mem;
    this-> pb = mem + (memSize - DEFAULT_PROCESS_BLOCK_SIZE);
    this-> pbEnd = mem + memSize;
    this-> datablockFlag = mem;
    this-> addrblockFlag = (DataPoint*)this->pb;

    this->numData = 0;
    
    mkdir(DATA_PATH, 0777); 
}

void MemInfo_reset(MemInfo* this){
    this-> datablockFlag = this->mem;
    this-> addrblockFlag = (DataPoint*)this->pb;
    this-> numData = 0;
}


void MemInfo_destruct(MemInfo *this){
    this->pb = this->pbEnd = NULL;
    this->datablockFlag = NULL;
    this->addrblockFlag = NULL;
    this->mem = NULL;
    this->numData = 0;
}

void MemInfo_save(MemInfo *this){
    int outfd;
    size_t nwrite;
    
    outfd = open(INFO_OUT, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR | S_IWUSR);
    if( (nwrite = write(outfd, this, sizeof(MemInfo))) == -1 )
        printf("MemInfo write error\n");

    close(outfd);
}

void MemInfo_load(MemInfo *this){
    int infd;
    size_t nread;

    if( (infd = open("meminfo.out", O_RDONLY)) != -1 )
        nread = read(infd, this, sizeof(MemInfo));
    else fprintf(stderr, "Usage:  [-t nsecs] [-n] name\n");
    close(infd);
}

void Mem_save(MemInfo* this,int numEntry, int* numMemBlock){
    int i;
    FILE *outfd;
    size_t nwrite;
    char fileNameBuf[MEM_MAX_BLOCK]; 

    sprintf(fileNameBuf,"data/%d",(*numMemBlock)++);
    
//    /* to save the number of data entry */
    outfd = fopen(fileNameBuf,"w");
//    fwrite( &numEntry,sizeof(int),1,outfd);
//
//    /* to save memory */
//    if( (nwrite = fwrite(mem,sizeof(char), MEM_SIZE-PROCESS_BLOCK_SIZE,outfd)) == 0 ) 
//        fprintf(stderr, "Usage:  [-t nsecs] [-n] name\n");
//
    DataPoint *flag;
    flag = (DataPoint*) this->pb;
    for(i=0; i<numEntry; i++){
        flag--;
        if( (nwrite = fwrite( flag->addr, sizeof(char), flag->len, outfd)) == 0 )        
            fprintf(stderr, "Usage:  [-t nsecs] [-n] name\n");
    }

    fclose(outfd);
}

void MemInfo_display( MemInfo *this){
    printf("==========mem:%p\npb:%p\npbEnd:%p\ndatablockFlag:%p\naddrblockFlag:%p\nnumData:%d\n============\n",
    this->mem,this->pb,this->pbEnd,
    this->datablockFlag,(char*)this->addrblockFlag,
    this->numData);
}

void Mem_display(MemInfo *this){
    int i;
    DataPoint *tmp;
    for(i=this->numData-1; i>=0; i--){
        tmp = this->addrblockFlag + i;
        printf("i:%d nread:%d %s\n",this->numData-i-1,tmp->len, tmp->addr);
    }
}


int Mem_is_enough(MemInfo* this){
    size_t offset;

    //printf("addrblockFlag %p\n",this->addrblockFlag);
    //printf("datablockFlag %p\n",this->datablockFlag);
    offset = (char*)this->addrblockFlag - this->datablockFlag;

    return ( offset > URL_MAX_SIZE + sizeof(DataPoint) )?TRUE:FALSE;
}


void Mem_sort(MemInfo* this, IMeg* imeg){
    int (*tmp)(const void* p1,const void* p2) = NULL;

    if(imeg->increase == TRUE && imeg->sensitive == TRUE){ tmp = minstrcompare; }
    else if(imeg->increase == TRUE && imeg->sensitive == FALSE){ tmp = minstrcasecompare; }
    else if(imeg->increase == FALSE && imeg->sensitive == TRUE){ tmp = maxstrcompare; }
    else if(imeg->increase == FALSE && imeg->sensitive == FALSE){ tmp = maxstrcasecompare; }
        

    qsort(this->addrblockFlag,this->numData, sizeof(DataPoint), tmp); 
}

int minstrcompare(const void* p1, const void* p2 ){
    const DataPoint* x = p1;
    const DataPoint* y = p2;

    return (strcmp(x->addr, y->addr) < 0);
}

int maxstrcompare(const void* p1, const void* p2 ){
    const DataPoint* x = p1;
    const DataPoint* y = p2;

    return (strcmp(x->addr, y->addr) > 0);
}

int minstrcasecompare(const void* p1, const void* p2){
    const DataPoint* x = p1;
    const DataPoint* y = p2;

    return (strcasecmp(x->addr, y->addr) < 0);
}

int maxstrcasecompare(const void* p1, const void* p2){
    const DataPoint* x = p1;
    const DataPoint* y = p2;

    return (strcasecmp(x->addr, y->addr) > 0);
}

void Mem_save_entry(MemInfo* this, char** startFlag, char** dot){
    size_t offset;
    DataPoint dataPointTmp;

    offset =(size_t)( *dot - *startFlag);
    memcpy( this->datablockFlag, *startFlag, offset);
    
    *(this->datablockFlag+offset) = '\0';

    dataPointTmp.addr = this->datablockFlag;
    this->datablockFlag += (offset+1);
    
    dataPointTmp.len = offset+1;//include '\0'
    this->addrblockFlag --;
    
    memcpy( this->addrblockFlag, &dataPointTmp, sizeof(DataPoint)); 
    this->numData ++;
    *startFlag = *dot + 1;
}

