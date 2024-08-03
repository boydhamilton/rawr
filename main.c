
// std
#include<stdio.h>
#include<time.h>
#include<math.h>

// rawr
#include"rawr/rawr.h"



int main(int argc, char* argv[]){

    const int width = 128*5, height = 128*5; // window size

    if(rawr_initdraw(width, height, "rawr") != 0)
        return 1;

    rawr_setzerocol(124, 88, 105);
    rawr_setonecol(175, 210, 233);

    byte x = 32, y=32;

    while(!rawr_quit){
        rawr_clearmatrixto(0x0);
        rawr_updateevents();

        if(rawr_getkeystate(0))
            y--;
        else if(rawr_getkeystate(1))
            y++;
        if(rawr_getkeystate(2))
            x++;
        else if(rawr_getkeystate(3))
            x--;

        rawr_drawlinecardinal(4,5,17,31,0x1);
        rawr_drawarc(48, 16, 10, PI_VIA_RAWR/4, 4 * PI_VIA_RAWR / 3, 0x1);

        rawr_pointlight(x, y, 12, 0x1, 0x1);

        rawr_draw();
    }

    rawr_free();
    
    return 0;
}
