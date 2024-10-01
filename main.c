

// rawr
#include"rawr/rawr.h"

#include<stdio.h>

int main(int argc, char* argv[]){

    if(rawr_initdraw(640, 640, "rawr") != 0)
        return 1;

    rawr_setzerocol(51, 51, 51);
    rawr_setonecol(72, 229, 194);

    byte x = 9, y =9;

    while(!rawr_quit){
        rawr_updateevents();
        
        rawr_setpixel(0,64,0x1);

        printf("%d\n", rawr_getpixel(0,63+1));

        rawr_draw();
    }

    rawr_free();
    
    return 0;
}
