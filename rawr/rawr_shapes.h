

#ifndef RAWR_SHAPESH_
#define RAWR_SHAPESH_

/*
draw line, approximate a line across the screen matrix between two points
*/
void rawr_drawline(byte x1, byte y1,byte x2, byte y2, byte b);

/*
draw circle, approximate an unfilled circle with given radius on screen matrix
coordinates are for the centre of the circle
*/
void rawr_drawcircle(byte xc, byte yc, byte r, byte b);

/*
draw rectangle
*/
void rawr_drawrect(byte x, byte y, byte w, byte h, byte b);

#endif