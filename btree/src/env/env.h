#ifndef ENV_H
#define ENV_H

#define DISK_BLOCK_SIZE 16*1024
#define MAX_URL_SIZE    128

#define   MINIMUM_DEG 3
//#define MINIMUM_DEG   ((int)(DISK_BLOCK_SIZE-2*sizeof(int)+MAX_URL_SIZE)/(2*(MAX_URL_SIZE+sizeof(int))))
#define PADDING       DISK_BLOCK_SIZE-2*sizeof(int)-2*(MINIMUM_DEG)*MAX_URL_SIZE+MAX_URL_SIZE-2*sizeof(int)*(MINIMUM_DEG)

#endif 
