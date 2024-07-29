

#include<math.h>
#include<string.h>

#include<stdio.h>

#ifndef RAWR_LIGHTH_
#include"rawr_light.h"
#endif


static byte lightmap[64][64];

void rawr_setlightingenv(){
    memset(lightmap, 0, sizeof(byte) * 4096);
}

static int ispointincircle(byte x, byte y, byte pxc, byte pxy, byte pr){
    return (x < pxc+pr && x > pxc-pr && y < pxy+pr && y < pxy-pr);
}

static int los(byte xo, byte yo, byte xp, byte yp, byte b_coll){
    int dx = xp - xo, dy = yp - yo;
    int stepsreq = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy); 

    float xinc = (float)dx / (float)stepsreq, yinc = (float)dy / (float)stepsreq;
    
    float x=xo, y=yo;

    for(int i=0; i<=stepsreq; i++){

        byte p = rawr_getpixel((byte)x, (byte)y);
        byte lm = lightmap[(byte)y][(byte)x];
        //printf("%d %d %d %d\n",p, (byte)x, (byte)y, lm);

        if(p==b_coll && !lm){
            return 0;
        }

        
        x+=xinc;
        y+=yinc;
    }
    return 1;
}

static int betterlos(byte x1, byte y1, byte x2, byte y2, byte b_coll){
    int x = x1, y = y1;
    int dx = abs(x2 - x), dy = abs(y2 - y);
    int xinc = (x1 < x2) ? 1 : -1, 
        yinc = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while(x!=x2 && y!=y2){

        if(rawr_getpixel((byte)x, (byte)y)==b_coll && !lightmap[(byte)y][(byte)x]){
            return 0;
        }
        
        int errdoubled = err << 1;

        if(errdoubled > -dy && errdoubled < dx){
            if(rawr_getpixel((byte)x-xinc, (byte)y)==b_coll && !lightmap[(byte)y][(byte)x-xinc]){
                return 0;
            }
        }

        if(errdoubled > -dy){
            err -= dy;
            x += xinc;
        }
        if(errdoubled < dx){
            err += dx;
            y += yinc;
        }
        
    }
}

/* 
have an array of pixels drawn by circle and in los check if pixel is that or nah?
*/

void rawr_pointlight(byte xc, byte yc, byte r, byte bi, byte bc){
    if(r>32) // dont need more than that!
        r = 32;
    else if(r<1)
        r = 1;

    r++; 
    
    int r2 = r * r;
    int area = r2 << 2;
    int rr = r << 1;

    int tx, ty; // test point

    for(int i=0; i < area; i++){ 
        tx = (i % rr) - r;
        ty = (i / rr) - r;

        if(rawr_getpixel(xc + tx, yc + ty)!=bi && tx * tx + ty * ty < r2 && los(xc, yc, xc+tx, yc+ty, bc)){ // x^2 + y^2 = r^2 check
            rawr_setpixel(xc + tx, yc + ty, bi);
            lightmap[yc+ty][xc+tx] = 1;
        }
    }
   
}