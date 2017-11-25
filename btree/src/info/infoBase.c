#include "info.h"

/*initialize the value of entry in BT_INFO*/
void info_init(BT_INFO *this){
    this->rootInumber = -1; //Show that rootNode does't exist
    this->totalNode = 0;
}

/* get value of totalNode in BT_INFO */
int info_getTotalNode(BT_INFO *this){
    return this->totalNode; 
}

/*get inumber of root*/
int info_getRootInumber(BT_INFO *this){ 
    return this->rootInumber; 
}

/*increase value of the totalNode for recording tree node */
void info_totalNodeIncre(BT_INFO *this){
    this->totalNode ++;
}

/* loading the BT_INFO from the file that recording last process*/
void info_loaded(BT_INFO *this){
    FILE *fp = fopen(BT_INFO_FILENAME,"r");
    int nread;
    
    if(fp == NULL){
        //file doesn't exist
        info_init(this);
    }
    else{
        if( (nread = fread( this, sizeof(BT_INFO), 1, fp)) <= 0 )
            //read error
            printf("read info file fails\n");

        fclose(fp);
    }


}

//* saving the information of BT_INFO to file */
void info_save(BT_INFO *this){
    FILE *fp = fopen(BT_INFO_FILENAME,"w+");
    int nwrite;
    
    if( (nwrite = fwrite(this,sizeof(BT_INFO),1,fp)) <= 0)
        //write error
        printf("writing  to file fails\n");
    fclose(fp);
}

/* print the information of BT_INFO */
void info_display(BT_INFO *this){
    printf("========BT_INFO=======\n");
    printf("root:%d\ntotalNode:%d\n", 
            this->rootInumber,this->totalNode);
    printf("==================\n");
}
