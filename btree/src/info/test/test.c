#include <stdio.h>
#include "info.h"

int main(){
    BT_INFO info,
            tmp;

    info_init(&info);
    info_display(&info);
    info_save(&info);
    
    info_loaded(&tmp);
    info_totalNodeIncre(&tmp);
    info_save(&tmp);
    info_loaded(&tmp);
    info_display(&tmp);



    return 0;
}
