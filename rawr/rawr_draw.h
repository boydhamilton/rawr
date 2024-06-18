

#ifndef RAWR_DRAWH_
#define RAWR_DRAWH_

#include<SDL2/SDL.h>

#define _H 64
#define _W 64
// W MUST BE 2^N SUCH THAT N>=3


typedef unsigned char byte;
typedef unsigned int dword;

extern SDL_Texture* rawr_target;

extern SDL_Window* rawr_window;
extern SDL_Renderer* rawr_renderer;


/*
the pixel matrix optimizes for space using bitshifting to fully utilize space
because we only have to store ones and zeros, we can just use individual bits
each matrix element has an 8 bit datatype (byte)
imagine it as though the bits are in a row, very intuitive order.
retrieved by:
    int index = (int)floor(x/8);
    int offset = x%8;
    return (byte) ((rawr_pixelmatrix[y][index] >> offset) & 0x1);

set by:
    byte _x = x% _W;
    byte _y = y% _H;

    int index = (int)x/8;
    int offset = _x%8;
    byte mask = b << offset;
    rawr_pixelmatrix[_y][index] |= mask;
*/
extern byte rawr_pixelmatrix[_H][_W/8];


/*
initialize the rawr drawing enviroment
*/
int rawr_initdraw(int width, int height, char* title);

/*
rawr quit
*/
void rawr_free();

/*
returns the state of the pixel at the given position as a byte
*/
byte rawr_getpixel(byte x, byte y);

/*
set the state of the pixel at the given position
takes least significant bit of number as it has to be 1 or 0 to be stored as a single bit
*/
void rawr_setpixel(byte x, byte y, byte b);

/*
set the colour the pixels will be in at the one state
*/
void rawr_setonecol(byte r, byte g, byte b);

/*
returns current colour used at the one state
*/
byte* rawr_getonecol();

/*
set the colour the pixels will be in the zero state
*/
void rawr_setzerocol(byte r, byte g, byte b);

/*
returns current colour used at the zero state
*/
byte* rawr_getzerocol();

/*
set all pixels in the matrix to specified state
*/
void rawr_clearmatrixto(byte b);

/*
rawr fast drawing method
*/
void rawr_drawtorawr();

/*
draw call, to be called in main
*/
void rawr_draw();


#endif
