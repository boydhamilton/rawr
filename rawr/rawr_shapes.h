

#ifndef RAWR_SHAPESH_
#define RAWR_SHAPESH_

#define PI_VIA_RAWR 3.14159265359

/*
draw line, approximate a line across the screen matrix between two points
*/
void rawr_drawline(byte x1, byte y1,byte x2, byte y2, byte b);


/*
draw line, approximated using only the 4 cardinal directions
*/
void rawr_drawlinecardinal(byte x1, byte y1, byte x2, byte y2, byte b);

/*
draw circle, approximate an unfilled circle with given radius on screen matrix
coordinates are for the centre of the circle
*/
void rawr_drawcircle(byte xc, byte yc, byte r, byte b);

/*
draw filled circle. 
note: DOES NOT USE MIDPOINT CIRCLE VARIATIONS TO DO SO, the filled circle drawn by drawcirclefilled of a given radius
can be different than the circle drawn by drawcircle of the same radius 
*/
void rawr_drawcirclefilled(byte xc, byte yc, byte r, byte b);

/*
draw rectangle
*/
void rawr_drawrect(byte x, byte y, byte w, byte h, byte b);

/*
draw an arc from startangle to endangle
*/
void rawr_drawarc(byte xc, byte yc, byte r, float startangle, float endangle, byte b);

/*
draw polygon from points
*/
void rawr_drawpolygon(byte** points, byte amntpoints, byte b);


void rawr_drawrectfilled(byte x, byte y, byte w, byte h, byte b);

#endif