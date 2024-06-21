

#ifndef RAWR_SHAPESH_
#define RAWR_SHAPESH_

/*
draw line, approximate a line across the screen matrix between two points
note: rawr's handling of pixels drawn to the screen, not setting those that are off the visible plane, leads to 
unusual behaviour with lines that extend off the screen
*/
void rawr_drawline(byte x1, byte y1,byte x2, byte y2, byte b);

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

#endif