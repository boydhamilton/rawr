# rawrlib

Game framework, built with and for C programming. C's functional programming structure and rawr's removal of complications that may be unintuitive to the beginner game developer make the learning curve a breeze.

rawr is a simple 1bit 64x64 pixel game framework, designed for quick and easy arcade-style game development.

Example program:
```c
#include "rawr/rawr.h"

int main(int argc, char* argv[]){
  const int width = 128*4, height = 128*4; // window size

    if( rawr_initdraw(width, height, "rawr Demo") != 0)
        return 0;

    rawr_setzerocol(46,41,78); // set the colour of pixels in the high state
    rawr_setonecol(255,212,0); // "" "" "" "" "" "" "" low state
    
    int x =4,y=4;

    while(!rawr_quit){
        rawr_clearmatrixto(0x0); // clear the screen to either 1 or 0 state. can use ints to represent 1 or 0 too, not just hexadecimal
        rawr_updateevents(); // update events, run this before any of your own update code

        if(rawr_getkeystate(0))
            y--;
        else if(rawr_getkeystate(1))
            y++;
        if(rawr_getkeystate(2))
            x++;
        else if(rawr_getkeystate(3))
            x--;

        rawr_drawcircle(x,y,2,0x1);
        
        rawr_draw(); // run this after all your own update/drawing code
    }

    rawr_free(); // important to add at the end to avoid memory leaks!
    
    return 0;
}
```
