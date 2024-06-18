
// std
#include<stdio.h>
#include<time.h>

// rawr
#include"rawr/rawr.h"


int main(int argc, char* argv[]){

    const int width = 128*4, height = 128*4; // window size

    if( rawr_initdraw(width, height, "fqqsadasd") != 0)
        return 0;

    rawr_setzerocol(46,41,78);
    rawr_setonecol(255,212,0);

    dword frames = 0;
    
    int x =4,y=4;

    while(rawr_runupdate && !rawr_quit){
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

        rawr_drawrect(x,y,x+4,y+4,0x1);
        
        rawr_draw();

        frames++;
    }

    rawr_free();
    
    return 0;
}
