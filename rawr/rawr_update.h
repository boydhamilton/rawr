

#ifndef RAWR_INPUTH_
#define RAWR_INPUTH_

#include<stdlib.h>
#include<string.h>

#include<SDL2/SDL.h>


#ifndef RAWR_DRAWH_
typedef unsigned char byte;
#endif


extern byte rawr_keys[6];
extern byte rawr_quit;

extern byte rawr_continuouslysweepforcontroller;


/*
return 1 on success and 0 on failure
*/
int rawr_lookforcontroller();

/*
handle events and update surrounding variables accordingly 
*/
void rawr_updateevents();

/*
retrieve specified key state
0 up
1 down
2 right
3 left
4 c
5 x
6 z
*/
byte rawr_getkeystate(byte keyindex);

#endif