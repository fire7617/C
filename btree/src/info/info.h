#ifndef INFO_H
#define INFO_H

#include <stdio.h>

#define BT_INFO_FILENAME  "bt.info"


typedef struct stBT_INFO{
    int rootInumber;
    int totalNode;
} BT_INFO;


void info_init(BT_INFO *this);

void info_loaded(BT_INFO *this);
void info_save(BT_INFO *this);

int info_getTotalNode(BT_INFO *this);
int info_getRootInumber(BT_INFO *this);

void info_totalNodeIncre(BT_INFO *this);
void info_display(BT_INFO *this);



#endif
