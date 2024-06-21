

#include<stdlib.h>
#include<math.h>

#ifndef RAWR_DRAWH_
#include"rawr_draw.h"
#endif

// implementation of raster shape algorithms for rawr

// draw an approximate line across matrix
void rawr_drawline(byte x1, byte y1,byte x2, byte y2, byte b){

    int dx = x2 - x1, dy = y2 - y1; // change
    int stepsreq = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy); // find which is greater difference, take maximum steps required

    float xinc = (float)dx / (float)stepsreq, yinc = (float)dy / (float)stepsreq; // bomboclatt get incrememtn per step
    
    float x=x1, y=y1;
    float xe=x2, ye=y2;

    for(int i=0; i<=stepsreq/2; i++){ // work from both ends
        rawr_setpixel((int)x, (int)y, b);
        rawr_setpixel((int)xe, (int)ye, b);

        x+=xinc;
        y+=yinc;
        xe-=xinc;
        ye-=yinc;
    }
}

// draw a circle using midpoint circle algorithm, x and y are coordinates of centre
void rawr_drawcircle(byte xc, byte yc, byte r, byte b){
    if(r<0)
        return;
    
    int x = r, y=0;
    int p = 1-r;

    rawr_setpixel(xc+r,yc,b);
    rawr_setpixel(xc-r,yc,b);
    rawr_setpixel(xc,yc+r,b);
    rawr_setpixel(xc,yc-r,b);

    while(x>y){
        y++;
        if(p<=0){ // magic determination formula derived from the classic x^2 + y^2 = r^2
            p = p+ 2*y + 1;
        }else{
            x--;
            p = p + 2*y - 2*x + 1;
        }

        if(x<y)
            break; // all points done :)

        rawr_setpixel(x + xc, y + yc, b);
        rawr_setpixel(-x + xc, y + yc, b);
        rawr_setpixel(x + xc, -y + yc, b);
        rawr_setpixel( -x + xc, -y + yc, b);
        rawr_setpixel(y + xc, x + yc, b);
        rawr_setpixel(-y + xc, x + yc, b);
        rawr_setpixel(y + xc, -x + yc, b);
        rawr_setpixel(-y + xc, -x + yc, b);
    }
   
}


void rawr_drawcirclefilled(byte xc, byte yc, byte r, byte b){
    if(r<0)
        return;

    // s/o my stack overflow for the algorithm i <3 you for not using sqrt

    r++; // has irregularities with the <= equality, so am just doing <, which gives a smooth circle, and adding one to radius
    
    int r2 = r * r; 
    int area = r2 << 2; // psychotic bitshift estimation for 4*r^2 to give bounding box area
    int rr = r << 1; // width/ height of bb

    int tx, ty; // test point

    for(int i=0; i < area; i++){ // this leads to square-y circle, try solving the problem of edges being straight lines
        tx = (i % rr) - r; // collumn
        ty = (i / rr) - r; // row

        if (tx * tx + ty * ty < r2) // x^2 + y^2 = r^2 check
            rawr_setpixel(xc + tx, yc + ty, b);
    }
   
}

void rawr_drawrect(byte x, byte y, byte w, byte h, byte b){
    rawr_drawline(x,y,x+w,y, b);
    rawr_drawline(x,y+h,x+w,y+h, b);
    rawr_drawline(x,y,x,y+h, b);
    rawr_drawline(x+w,y,x+w,y+h, b);
}