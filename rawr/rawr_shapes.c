

#include<stdlib.h>
#include<stdio.h>

#include<math.h>

#ifndef RAWR_DRAWH_
#include"rawr_draw.h"
#endif

#ifndef RAWR_SHAPESH_
#include"rawr_shapes.h"
#endif

// implementation of raster shape algorithms for rawr

// draw an approximate line across matrix
void rawr_drawline(byte x1, byte y1,byte x2, byte y2, byte b){

    int dx = x2 - x1, dy = y2 - y1; // change
    int stepsreq = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy); // find which is greater difference, take maximum steps required

    float xinc = (float)dx / (float)stepsreq, yinc = (float)dy / (float)stepsreq; // bomboclatt get incrememtn per step
    
    float x=x1, y=y1;

    for(int i=0; i<=stepsreq; i++){
        rawr_setpixel((int)x, (int)y, b);

        // find if diagonal, then check pixel adjacent

        x+=xinc;
        y+=yinc;
    }
}

void rawr_drawlinecardinal(byte x1, byte y1, byte x2, byte y2, byte b){
    int x = x1, y = y1;
    int dx = abs(x2 - x), dy = abs(y2 - y);
    int xinc = (x1 < x2) ? 1 : -1, 
        yinc = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while(x!=x2 && y!=y2){

        rawr_setpixel(x, y, b);

        int errdoubled = err << 1;
        if(errdoubled > -dy){
            err -= dy;
            x += xinc;
        }
        if(errdoubled < dx){
            err += dx;
            y += yinc;
        }
        if(errdoubled > -dy && errdoubled < dx){
            rawr_setpixel(x-xinc, y, b);
        }
    }
}

// draw a circle using midpoint circle algorithm, x and y are coordinates of centre
void rawr_drawcircle(byte xc, byte yc, byte r, byte b){
    if(r<0)
        return;
    
    int x = r, y=0;
    int p = 1-r; // decision over

    rawr_setpixel(xc+r,yc,b);
    rawr_setpixel(xc-r,yc,b);
    rawr_setpixel(xc,yc+r,b);
    rawr_setpixel(xc,yc-r,b);

    while(x>y){
        y++;
        if(p<=0){ // magic determination formula derived from the classic x^2 + y^2 = r^2
            p = p+ (y<<1) + 1; // x * n | n base 2 is for losers
        }else{
            x--;
            p = p + (y<<1) - (x<<1) + 1;
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
    if(r>32) // dont need more than that!
        r = 32;
    else if(r<1)
        r = 1;

    r++; // has irregularities with the <= equality, so am just doing <, which gives a smooth circle, and adding one to radius
    
    int r2 = r * r;
    int area = r2 << 2; // bitshifting multiplies by 2 for each step, r2 << 2 = r2 * 4 and is faster
    int rr = r << 1; // width of bounding square
    float circumf = (r<<1) * PI_VIA_RAWR;

    int tx, ty; // test point

    for(int i=0; i < area; i++){ // this leads to square-y circle, try solving the problem of edges being straight lines
        tx = (i % rr) - r; // collumn
        ty = (i / rr) - r; // row

        // TODO: could find a from both ends approach

        if(rawr_getpixel(xc + tx, yc + ty)!=b && tx * tx + ty * ty < r2) // x^2 + y^2 = r^2 check
            rawr_setpixel(xc + tx, yc + ty, b);
    }
   
}

// TODO: USE MIDPOINT SOMEHOW
void rawr_drawarc(byte xc, byte yc, byte r, float startangle, float endangle, byte b){

    // zero research done. absolutely atrocious but its not serious

    float step = 1/((endangle-startangle) * r);
    step=step*1.75; // huge estimations per step, need to find an actual expression to calculate the number required but this works well for now
    // printf("%f\n",endangle/step);
    float x=xc, y=0;
    float xp=0, yp=0;
    float dxdy;

    for(float i=startangle; i<endangle; i+=step){
        x = (float)xc + (r * cos(i)); // TODO: absolute "sin" to be using trig functions. need to fix
        y = (float)yc - (r * sin(i));            
            
        rawr_setpixel((byte)roundf(x), (byte)roundf(y), b);
    }
}

void rawr_drawpolygon(byte** points, byte amntpoints, byte b){
    // each point is [x,y]
    byte px, py;
    byte p_px = points[amntpoints-1][0], p_py = points[amntpoints-1][1];
    for(int i=0; i<amntpoints; i++){
        px = points[i][0];
        py = points[i][1];
        rawr_drawline(p_px, p_py, px, py, b);
        p_px = px;
        p_py = py;
    }
}

void rawr_drawrect(byte x, byte y, byte w, byte h, byte b){
    rawr_drawline(x,y,x+w,y, b);
    rawr_drawline(x,y+h,x+w,y+h, b);
    rawr_drawline(x,y,x,y+h, b);
    rawr_drawline(x+w,y,x+w,y+h, b);
}

void rawr_drawrectfilled(byte x, byte y, byte w, byte h, byte b){
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++){
            rawr_setpixel(x+j, y+i, b);
        }
}