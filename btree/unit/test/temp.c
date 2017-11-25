
void parsing_cmd(int argc, char **argv);
void read_url();
void save_node(BT_NODE *this);
void node_init(BT_NODE *this);
BT_NODE* read_node(char *buf);


void parsing_cmd(int argc, char **argv){
    int ch;
    const char *optstring = "i:d:q:I:D:Q:";

    while( (ch = getopt(argc, argv, optstring)) != -1 ){
        switch(ch){
            case 'i':
                printf("insert:%s\n",optarg);  
                break;
            case 'd':
                printf("del:%s\n",optarg);
                break;
            case 'q':
                printf("query:%s\n",optarg);
                break;
            default:
                printf("%s\n","parsing commnad  occurs error");
                break;
        }
    }
}

void read_url(){
    size_t nread = sizeof(char)*MAX_URL_SIZE;
    char *buf = malloc(nread);
    FILE *fp = fopen("./url.txt", "r");
    ssize_t c;
        
    if(fp == NULL){
        printf("url file path error\n");
        return;
    }
    if( (c = getline( &buf, &nread, fp) ) > 0 )
        printf("%s\n",buf);

    free(buf);
    fclose(fp);
}

void node_init(BT_NODE *this){
    int i;

    this->iNumber = 0;
    this->isLeaf = 0;
    
    for(i=0; i< 2*MINIMUM_DEG-1; i++)
        memset(&this->pszaKeys[i],0,sizeof(char)*MAX_URL_SIZE);
    for(i=0; i<2*MINIMUM_DEG; i++)
        this->iaChildren[i] = 0;
}

void save_node(BT_NODE *this){
    FILE *fp = fopen("out","w");
    
    fwrite(this,sizeof(BT_NODE),1,fp);   
    fclose(fp);
}

void print_node(BT_NODE *this){
    int i;

    printf("=====================\n");
    printf("iNumber:%d\n",this->iNumber);
    printf("isLeaf :%d\n",this->isLeaf);
    printf("Key:\n");
    for(i=0; i< 2*MINIMUM_DEG-1; i++)
       printf("%s\n",this->pszaKeys[i]);
    
    printf("child\n");
    for(i=0; i<2*MINIMUM_DEG; i++)
        printf("%d ",this->iaChildren[i]);

    printf("\n=====================\n");
}

BT_NODE* read_node(char *buf){
    FILE *fp= fopen("out","r");
    size_t nread = sizeof(BT_NODE);

    if(fp == NULL)
        printf("file point error\n");

    if( (nread = fread(buf,nread,1,fp)) > 0)        
        print_node((BT_NODE*)buf);
    else
        printf("read error\n");
    fclose(fp);

    return  (nread>0)?(BT_NODE*)buf:NULL;
}

