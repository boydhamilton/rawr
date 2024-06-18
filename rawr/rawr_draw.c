

#ifndef RAWR_DRAWH_
#include"rawr_draw.h"
#endif

// include
//std
#include<stdlib.h>
#include<time.h>
#include<string.h>

#ifdef _WIN32
#include<windows.h>
#else
#include<unistd.h>
#endif

static long long tms() {
#ifdef _WIN32
    SYSTEMTIME st;
    GetSystemTime(&st);
    return ((long long)st.wSecond * 1000) + st.wMilliseconds;
#else
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ((long long)ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
#endif
}


//sdl2
#include<SDL2/SDL.h>


// NOTES
/*"     USER SIDE:
have nxm matrix of pixels
function to set pixel
function to set "one" colour, function to set "zero" colour as each pixel will be either 1 or 0
"*/

/*"     ME SIDE:
have nxm texture
draw user-set pixels to texture
render texture at scale onto window

optimize for space:
    bitshifting pixelmatrix to get 8 mutable bits per byte - DONE

optimize for time:
    identify adjacent groups of pixels then draw rectangles instead of individual pixels in drawcall

"*/


byte rawr_onecol[] = {255,255,255};
byte rawr_zerocol[] = {20,20,20};

SDL_Texture* rawr_target;


static dword cpixels = 0;
static byte cpixeldata[_W*_H][3]; // each pixel then x,y,b

static int windowwidth, windowheight;

byte rawr_pixelmatrix[_H][_W/8];


SDL_Window* rawr_window;
SDL_Renderer* rawr_renderer;



// unused, just assume user puts valid input
// static byte rawr_isobit(byte b){
//     return (byte)(b & 0x1);
// }

static void rawr_inittarget(SDL_Renderer* r){
    cpixels = 0;
    rawr_target = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _W, _H);
}


/*
window should be square and in increments of powers of two, max out at 64.
8x8, 16x16, 32x32, 64x64
*/
int rawr_initdraw(int width, int height, char* title){

    windowwidth = width;
    windowheight = height;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return 1;

    rawr_window = SDL_CreateWindow(
        title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windowwidth,windowheight,SDL_WINDOW_SHOWN);

    rawr_renderer = SDL_CreateRenderer(rawr_window,-1, SDL_RENDERER_ACCELERATED);

    if(!rawr_window || !rawr_renderer)
        return 2;

    rawr_inittarget(rawr_renderer);

    if(!rawr_target)
        return 3;


    return 0;
}

void rawr_free(){
    free(rawr_target);
    SDL_Quit();
}

byte rawr_getpixel(byte x, byte y){

    // int index = x/8; // DONT NEED FLOOR FOR INT DIVISION, decimal part is just whisked away as it doesnt have decimal representation
    // int offset = x%8;
    return (byte) (rawr_pixelmatrix[y][x/8] >> x%8) & 0x1;
}

void rawr_setpixel(byte x, byte y, byte b){

    byte _x = x% _W;
    byte _y = y% _H;

    // int index = (int)x/8;
    // int offset = _x%8;
    // byte mask = b << offset;
    rawr_pixelmatrix[_y][x/8] |= (b << (_x%8) );
    
    cpixeldata[cpixels][0] = _x;
    cpixeldata[cpixels][1] = _y;
    cpixeldata[cpixels][2] = b;
    cpixels++;
}

void rawr_setonecol(byte r, byte g, byte b){
    rawr_onecol[0] = r;
    rawr_onecol[1] = g;
    rawr_onecol[2] = b;
}

byte* rawr_getonecol(){
    return rawr_onecol;
}

void rawr_setzerocol(byte r, byte g, byte b){
    rawr_zerocol[0] = r;
    rawr_zerocol[1] = g;
    rawr_zerocol[2] = b;
}

byte* rawr_getzerocol(){
    return rawr_zerocol;
}

// drawr

void rawr_clearmatrixto(byte b){

    SDL_Renderer* r = rawr_renderer;

    SDL_SetRenderTarget(r, rawr_target);

    memset(rawr_pixelmatrix, (b) ? 255 : 0 ,_H*_W*sizeof(byte)); // 255 as to take up all bits

    if(b)
        SDL_SetRenderDrawColor(r,rawr_onecol[0],rawr_onecol[1],rawr_onecol[2],SDL_ALPHA_OPAQUE);
    else
        SDL_SetRenderDrawColor(r,rawr_zerocol[0],rawr_zerocol[1],rawr_zerocol[2],SDL_ALPHA_OPAQUE);

    SDL_RenderClear(r);

    SDL_SetRenderTarget(r, NULL);
}

void rawr_drawtorawr(){

    SDL_Renderer* r = rawr_renderer;

    SDL_SetRenderTarget(r, rawr_target);
    
    int cx, cy, cb;
    for(int i=0; i<cpixels; i++){
        cx = cpixeldata[i][0];
        cy = cpixeldata[i][1];
        cb = cpixeldata[i][2];

        if(cb)
            SDL_SetRenderDrawColor(r,rawr_onecol[0],rawr_onecol[1],rawr_onecol[2],SDL_ALPHA_OPAQUE);
        else
            SDL_SetRenderDrawColor(r,rawr_zerocol[0],rawr_zerocol[1],rawr_zerocol[2],SDL_ALPHA_OPAQUE);

        SDL_RenderDrawPoint(r, cx, cy);
    }
    memset(cpixeldata,0,sizeof(byte)*(_H*_W)*3); // zero out array
    cpixels = 0; // no more pixels to be changed

    SDL_SetRenderTarget(r, NULL);
}

void rawr_draw(){
    
    const int delta = 1000 / 24; // 33ms ~= 30fps
    long long i = tms();

    // drawr ing
    rawr_drawtorawr();
    SDL_Rect destinationrectangle = {0,0, windowwidth, windowheight};
    SDL_RenderCopy(rawr_renderer, rawr_target, NULL, &destinationrectangle);
    SDL_RenderPresent(rawr_renderer);

    long long f = tms();
    int elapsed = (int)(f - i);
    int await = (int)(delta-elapsed);
    Sleep( (await>0) ? await : 0);
}