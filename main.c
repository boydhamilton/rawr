
// std
#include<stdio.h>
#include<time.h>
#include<math.h>

// rawr
#include"rawr/rawr.h"



int main(int argc, char* argv[]){

    srand(time(NULL));

    const int width = 128*4, height = 128*4; // window size

    if(rawr_initdraw(width, height, "RARARWRRWRWR") != 0)
        return 1;

    rawr_setlightingenv();

    rawr_setzerocol(26, 0, 143);
    rawr_setonecol(19, 55, 156);

    byte x = 32, y=32;

    while(!rawr_quit){
        rawr_clearmatrixto(0x0);
        rawr_updateevents();

        rawr_setlightingenv();

        

        if(rawr_getkeystate(0))
            y--;
        else if(rawr_getkeystate(1))
            y++;
        if(rawr_getkeystate(2))
            x++;
        else if(rawr_getkeystate(3))
            x--;

        rawr_drawline(32,32,48,48,0x1);

        rawr_pointlight(x, y, 8, 0x1, 0x1);

        rawr_draw();
    }

    rawr_free();
    
    return 0;
}
