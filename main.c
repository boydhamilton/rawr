

// rawr
#include"rawr/rawr.h"


int main(int argc, char* argv[]){

    if(rawr_initdraw(640, 640, "rawr") != 0)
        return 1;

    rawr_setzerocol(51, 51, 51);
    rawr_setonecol(72, 229, 194);

    byte x = 9, y =9;

    while(!rawr_quit){
        rawr_updateevents();
        rawr_clearmatrixto(0x0);
        
        if(rawr_getkeystate(0))
            y--;
        else if(rawr_getkeystate(1))
            y++;
        if(rawr_getkeystate(2))
            x++;
        else if(rawr_getkeystate(3))
            x--;


        rawr_drawrectfilled(32, 32, 16, 24, 0x1);
        rawr_drawcirclefilled(32, 48, 5, 0x0);
        rawr_drawarc(16, 16, 8, PI_VIA_RAWR/4, 3 * PI_VIA_RAWR/2, 0x1);

        rawr_draw();
    }

    rawr_free();
    
    return 0;
}
