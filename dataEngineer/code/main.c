#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include "env.h"
#include "main.h"
#include "file.h"
#include "mem.h"
#include "heap.h"

#define MEGABYTES 1024*1024
#define KILOBYTES 1024

int check_dir(const char *path);
void search_file(FileInfo *fi, const char *dirPath);
size_t mtf_fill_buf(FileInfo *fi, char* buf, size_t fillSize);
int divide_into_smallblock(MemInfo* mi, FileInfo* fi, IMeg* img);
void  merge_all_partitions( char* mem, int numblocks, IMeg* img);
void help_message();

int main(int argc, char** argv){
    int opt = -1;

    IMeg imeg;
    imeg.unique = FALSE,
    imeg.sensitive = TRUE,
    imeg.increase = TRUE;
    imeg.memSize = DEFAULT_MEM_SIZE;
    strcpy(imeg.outputFile, DEFAULT_OUTPUT_FILE);

    char delimiter[DELIMITER_MAX_LENGTH],
            pathBuf[PATH_MAX_LENGTH];

  /***********************************
  * to set the user's Options
  *************************************/

    strcpy(delimiter, "\\n");
    while( (opt = getopt(argc,argv,"m:iUudCcho:D:")) != -1 ){
        switch(opt){
            case 'm':
                imeg.memSize = atoi(optarg);
                imeg.memSize = imeg.memSize*KILOBYTES;
                printf("mem_size:%lu\n",imeg.memSize);
                break;
            case 'U':
                printf("Unique\n");
                imeg.unique = TRUE;
                break;
            case 'u':
                printf("Not Unique\n");
                imeg.unique = FALSE;
                break;
            case 'd':
                printf("decreasing\n");
                imeg.increase = FALSE;
                break;
            case 'i':
                printf("increasing\n");
                imeg.increase = TRUE;
                break;
            case 'C':
                printf("Case Insensitive\n");
                imeg.sensitive = FALSE;
                break;
            case 'c':
                printf("case sensitive\n");
                imeg.sensitive = TRUE;
                break;
            case 'o':
                printf("outfileName:%s\n",strcpy(imeg.outputFile, optarg));
                break;
            case 'D':
                if(strcmp(optarg,"\\n") == 0 ){
                    delimiter[0] = '\n'; 
                    delimiter[1] = '\0';
                }
                else
                    printf("Dedelimitter:%s\n",strcpy(delimiter,optarg));
                
                if(delimiter[0] == '\n' )
                    printf("change line\n");
                break;
            case 'h':
                help_message();    
                return 0;
                break;
            default:
                fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",argv[0]);
                exit(EXIT_FAILURE);
        }
    }

/***********************************
 *  get the path of all files
 ************************************/ 
    FileInfo fi;
    FileInfo_init( &fi );
    while(argv[optind] != NULL){
        strcpy(pathBuf,argv[optind++]);
        if( check_dir(pathBuf) == FALSE ) //printf("file:%s\n",pathBuf);
            FileInfo_setPath( &fi, pathBuf);
        else{ 
            printf("dir:%s\n",pathBuf); 
            search_file( &fi, pathBuf);
        }
    }
//    FileInfo_display( &fi ); 
    if(fi.numFile == 0){
        fprintf(stderr,"No input file\n");
        return 0;
    }

 /****************************************
 * to split the file into smaller partition that contains sorted urls
 **************************************/
    int numblocks = 0; 
    char* mem = (char*) malloc(sizeof(char)* imeg.memSize);
    memset(mem, 0, imeg.memSize); 
    
    FileInfo_changefd( &fi );
    MemInfo mi;
    MemInfo_init( &mi, mem, imeg.memSize);
    
    numblocks = divide_into_smallblock( &mi, &fi, &imeg);

    printf("the number of blocks:%d\n",numblocks);
    FileInfo_destruct( &fi );
    MemInfo_save( &mi );
    MemInfo_destruct( &mi ); 
    
/**************************************
 * to merge all partitions into a file 
 ******************************************/
    merge_all_partitions( mem, numblocks, &imeg);
       
/**********************************
 * destruction
 **************************************/
    free(mem);

    return 0;
}

int check_dir(const char *path){
    struct stat buf;

    if( stat(path, &buf) != -1 && (buf.st_mode & S_IFMT) == S_IFDIR )
        return TRUE;
    else{
//       fprintf(stderr,"stat error:\n%s\n",strerror(errno));
        return FALSE;
    }
}

void search_file(FileInfo *fi, const char *dirPath){
    struct dirent *buf;            
    DIR *dir;
    char pathBuf[PATH_MAX_LENGTH];

    dir = opendir(dirPath);
    while( (buf = readdir(dir)) != NULL ){
        if(strcmp(buf->d_name,".") == 0 || strcmp(buf -> d_name, "..") == 0) continue;
        sprintf( pathBuf, "%s/%s", dirPath, buf->d_name);
        if(check_dir(pathBuf) == TRUE ){ 
//            printf("dir:%s\n",pathBuf);  
            search_file(fi, pathBuf);
        }
        else FileInfo_setPath( fi, pathBuf);
    }
    closedir(dir); 
}

size_t mtf_fill_buf(FileInfo *fi, char* buf, size_t fillSize){
    int nread = 0,
        count = 0;

    if(fi->fd == -1) FileInfo_changefd(fi);
    while( count != fillSize ){
        if( (nread = read( fi->fd, buf+ count, fillSize - count)) == (fillSize - count) )
            return fillSize;
        else{
            count += nread;
            FileInfo_changefd( fi );
            if(fi->fd == 0) break;
        }
    }
    printf("count:%d in mtf_fill_buf\n",count);
    return count;
}

int  divide_into_smallblock(MemInfo* mi, FileInfo* fi, IMeg* imeg){
    int numblocks = 0;
    size_t offset = 0;
    char *dot, *startFlag;

    dot = startFlag = mi->pb;
    dot -= 1;
    offset = mtf_fill_buf( fi, mi->pb, DEFAULT_PROCESS_BLOCK_SIZE);
    mi->pbEnd = mi->pb + offset;
    while( dot++ ){
        if( *dot == '\n' ){
            Mem_save_entry(mi, &startFlag, &dot);
            if(Mem_is_enough( mi ) != TRUE){
                //printf("=============mem is not enough===============\n");
//                MemInfo_display( mi );
                Mem_sort( mi, imeg);
//                Mem_display( mi ); 
                Mem_save( mi, mi->numData, &numblocks);
                MemInfo_reset( mi );
            }
        }
        if( dot == mi->pbEnd ){
            if( mi->pbEnd != mi->pb + DEFAULT_PROCESS_BLOCK_SIZE) { 
                Mem_sort( mi, imeg);
 //               Mem_display( mi );
                Mem_save( mi, mi->numData, &numblocks);
                break;
            }
            offset = dot - startFlag;
            memcpy( mi->pb, startFlag, offset);
            mi->pbEnd = mi->pb + offset;

            offset = mtf_fill_buf( fi, mi->pb+offset, DEFAULT_PROCESS_BLOCK_SIZE-offset);
            mi->pbEnd += offset;
            dot = mi->pb-1;
            startFlag = mi->pb;
        }
    }
//    Mem_display( mi );
    
    return numblocks;
}

void merge_all_partitions( char* mem, int numblocks, IMeg* imeg){
    int i;
    int check_reload;

    HeapInfo hi;
    HeapInfo_init( &hi, numblocks, mem, imeg); 
    for(i=1; i<hi.heapLen; i++){ Heap_bottom_heapify( &hi, i, imeg); }
    //for(i=0; i<hi.heapLen; i++){ HeapNode_display( &(hi.heapTree[i]) ); }
//    HeapInfo_BlockInfo_display( &hi ); 

     while(1){   
        Heap_pop( &hi, imeg );
        check_reload = Heap_reload_root( &hi );
        if( check_reload == FALSE ){ //there is no data in the partition
            hi.heapTree[0] = hi.heapTree[hi.heapLen-1];
            hi.heapLen --;
        }
//    HeapInfo_BlockInfo_display( &hi ); 
        if(hi.heapLen == 0) { break; }
        Heap_top_heapify( &hi, imeg);
    //    for(j=0; j<hi.heapLen; j++){ HeapNode_display( &(hi.heapTree[j]) ); }
      //  printf("\n\n");
   }
    HeapInfo_destruct( &hi, numblocks);
}


void help_message(){
    printf("Name:\n\tesort - external sort\n\n"); 
    printf("\tesort [Option].... Directory/file...\n\n");
    printf("Description:\n\t");
    printf("To sort the urls from files by external way.\n\n");
    printf("\t -m, --memory size (megabytes) to use\n\t\t set the memory size to process\n\n");
    printf("\t -o, --output file \n\t\t set output file \n\n");
    printf("\t -i, --increasing order \n\t\t set output file with increasing order urls\n\n");
    printf("\t -d, --decreasing order \n\t\t set output file with decreasing order urls\n\n");
    printf("\t -C, --Case Insensitive \n\t\t set output file without case\n\n");
    printf("\t -c, --Case sensitive \n\t\t set output file with case\n\n");
    printf("\t -U, --Unique url \n\t\t set output file with unique url\n\n");
    printf("\t -u, --Not unique url \n\t\t set output file with no unique url \n\n");
    printf("\t -h, --help message\n\t\t print the help message\n\n");
}






