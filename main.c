
// std
#include<stdio.h>
#include<time.h>
#include<math.h>

// rawr
#include"rawr/rawr.h"



int main(int argc, char* argv[]){

    srand(time(NULL));

    const int width = 128*4, height = 128*4; // window size

    if(rawr_initdraw(width, height, "rawr") != 0)
        return 1;

    rawr_setzerocol(26, 0, 143);
    rawr_setonecol(19, 55, 156);

    int px = 32, py = 32;
    int r = 6;

    while(!rawr_quit){

    // init
        rawr_clearmatrixto(0x0);
        rawr_updateevents();

    // update
        if(rawr_getkeystate(0))
            py--;
        else if(rawr_getkeystate(1))
            py++;
        if(rawr_getkeystate(2))
            px++;
        else if(rawr_getkeystate(3))
            px--;
        if(rawr_getkeystate(4))
            r++;
        else if(rawr_getkeystate(5))
            r--;

    // drawr
        rawr_drawcirclefilled(px, py, r, 0x1);


        rawr_draw();
    }

    rawr_free();
    
    return 0;
}
