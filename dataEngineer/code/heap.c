#include "heap.h"

void HeapInfo_init(HeapInfo* this, int heapLen, char* mem, IMeg* imeg){
    int i;
    size_t blockSize = imeg->memSize/heapLen;
    size_t nread;
    
    this->heapLen = heapLen;
    this->blockSize = blockSize;
    this->mem = mem;
    this->flag = (char**)malloc(sizeof(char*)*heapLen);
    this->bi = (BlockInfo*) malloc(sizeof(BlockInfo)*heapLen);
    memset(this->bi, 0, sizeof(BlockInfo)*heapLen);
    for(i=0; i<heapLen; i++){
        (this->bi + i)->path = (char*)malloc(sizeof(char)*PATH_MAX_LENGTH);  
        sprintf( (this->bi + i)->path, "%s/%d", DATA_PATH,i);
        (this->bi + i)->fp = fopen( (this->bi + i)->path,"r+"); 
   
        this->flag[i] = (this->bi + i)->startFlag = mem + i*blockSize;
        (this->bi + i)->endFlag = mem + (i+1)*blockSize;

        nread = fread(this->flag[i], sizeof(char), blockSize, (this->bi+i)->fp);
//        printf("%d:  nread:%lu\n",i,nread);
        if( nread < blockSize) {
            (this->bi +i)->endFlag = (this->bi + i)->startFlag + nread; 
  //          printf("startFlag:%p ", (this->bi +i)->startFlag);
    //        printf("endFlag:%p\n",(this->bi +i)->endFlag);
        }
    }

    this->heapTree = (HeapNode*) malloc(sizeof(HeapNode)*heapLen);
    memset( this->heapTree, 0, sizeof(HeapNode)*heapLen);
    for(i=0; i<heapLen; i++){
        (this->heapTree[i]).label = i;
        (this->heapTree[i]).point = (this->bi + i)->startFlag;
//        printf("%p %p\n",this->heapTree[i].point, (this->bi +i)->startFlag);
    }

    this->ofp = fopen(imeg->outputFile,"w");
    this->lastOutput = (char*)malloc(sizeof(char)*URL_MAX_SIZE); 
    memset(this->lastOutput, 0, URL_MAX_SIZE);
}

void HeapInfo_destruct(HeapInfo* this, int numblocks){
    int i;

    fclose(this->ofp);

    for(i=0; i<numblocks; i++){
        free( (this->bi+i)->path);
        fclose( (this->bi+i)->fp);
    }

    free(this->bi);
    free(this->flag);
    free(this->heapTree);
    free(this->lastOutput);
}


void Heap_bottom_heapify( HeapInfo* this, int index, IMeg* imeg){
    int i,p;
    HeapNode* t = this->heapTree; 

    for(i=index; i>0; i=p){
        p = (i-1)/2;
        if( strcompare( (t + i)->point, (t + p )->point, imeg ) <  0 ){ 
            /* SWAP the treeNode[i] and treeNode[p] */
            HeapNode_swap( (t + i), (t + p) );
        }
        else{ break; }
    }
}

void HeapNode_swap(HeapNode* x, HeapNode*y){
    HeapNode temp; 
    
    temp.label = x->label; 
    x->label= y->label; 
    y->label=temp.label; 
    
    temp.point = x->point; 
    x->point = y->point; 
    y->point = temp.point;
}


void HeapNode_display(HeapNode* hn){
    printf("========================\n");
    printf("label:%d\n", hn->label);
    printf("url:%s\n", hn->point);
    printf("========================\n");
}

void Heap_pop(HeapInfo* hi, IMeg* imeg ){
    size_t urlLen;
    char a = '\n';
    urlLen = strlen( (hi-> heapTree)->point );
    //printf("pop:%s\n", (hi->heapTree)->point);
    
    if(imeg->unique == TRUE){
        if(strcmp(hi->lastOutput,(hi->heapTree)->point) == 0){ return; }
        else { strcpy(hi->lastOutput,(hi->heapTree)->point); }
    }
    fwrite( (hi->heapTree)->point, sizeof(char), urlLen+1, hi->ofp); // 1 for '\0'
    fwrite( &a, sizeof(char), 1,  hi->ofp);

}

void Heap_top_heapify( HeapInfo* this, IMeg* imeg){
    int i,lc;
    int t;
    
    HeapNode* swap = this->heapTree;
    for(i=0, lc=i*2+1; lc < this->heapLen; i=lc, lc = lc*2+1){
        /* right cthisld node exists  */
        if( lc+1 < this->heapLen -1){
            t = strcompare( (swap + lc)->point, (swap + lc + 1 )->point,imeg);
            if( t <= 0  && strcompare( (swap + i)->point,  (swap + lc )->point, imeg) >  0 ){
                HeapNode_swap( &swap[lc], &swap[i] );
            }
            else if(t > 0 && strcompare( (swap + i)->point , (swap + lc + 1)->point,imeg ) >  0  ){
                HeapNode_swap( &swap[lc+1], &swap[i]); 
                lc++; 
            }
            else { break; }
        }
        else{
            if( strcompare( (swap + i)->point , (swap + lc)->point, imeg) > 0 ) { 
                HeapNode_swap(&swap[i], &swap[lc]);  
            } 
            else { break; }
        }
    }
}



/*********************************************************
 * Description:
 *     to  reload the node root from the partition that is labeled 
 *     by HeapNode label after heap_pop  
 ***********************************************************/

int Heap_reload_root( HeapInfo* this ){
    size_t t,nread;
    int index;
    char* flag;
    BlockInfo* bi;

    /* to move the point of HeapNode root to the beginning of next url */ 
    for(; ; (this->heapTree)->point++){
        if( *((this->heapTree)->point) == '\0' ){ 
            (this->heapTree)->point++;
            break;  
        }
    }
    
    index = (this->heapTree)->label;
    flag = (this->heapTree)->point;
    bi = this->bi + index;
    for(;; flag++){
        if( flag == bi->endFlag ){
            t = bi->endFlag - (this->heapTree)->point;
            if( t > 0 ){ memcpy( bi->startFlag, (this->heapTree)->point, t); }
                
            nread = fread( bi->startFlag + t, sizeof(char), this->blockSize-t, bi->fp );
            if( t == 0 && nread == 0) { return FALSE; }
             
            (this->heapTree)->point = bi->startFlag;
            bi->endFlag = bi->startFlag + t + nread;

            return TRUE;
        }
        else if( *flag == '\0' ) { return TRUE; }
    }
}


void HeapInfo_BlockInfo_display( HeapInfo* this){
    int i;

    for(i=0; i<this->heapLen; i++){
        printf("%d startFlag:%p endFlag:%p point:%p\n",
                i,(this->bi + i)->startFlag,(this->bi + i)->endFlag,
                ((this->heapTree + i)->point));
    }
}


int strcompare(char* x, char* y, IMeg* imeg){
    int t,nt;
   
    
    if(imeg->sensitive == TRUE){ t = strcmp(x,y); }
    else                       { t = strcasecmp(x,y); }

    if( t > 0 ){ nt = -1; }
    else if( t < 0 ) { nt =  1; }

    return (imeg->increase)?t:nt;
}


