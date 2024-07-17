

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

static int losfrompoint(byte xo, byte yo, byte xp, byte yp, byte b_coll){
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
    float circumf = (r<<1) * PI_VIA_RAWR;

    int tx, ty; // test point

    for(int i=0; i < area; i++){ 
        tx = (i % rr) - r;
        ty = (i / rr) - r;

        if(rawr_getpixel(xc + tx, yc + ty)!=bi && tx * tx + ty * ty < r2 && losfrompoint(xc, yc, xc+tx, yc+ty, bc)){ // x^2 + y^2 = r^2 check
            rawr_setpixel(xc + tx, yc + ty, bi);
            lightmap[yc+ty][xc+tx] = 1;
        }
    }
   
}