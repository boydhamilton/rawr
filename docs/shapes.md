
# rawr_shapes.h

rawr shapes is used to provide rasterized drawing abilities, so the state of the pixel matrix is correctly updated with the shapes you draw. Reading through the function code can be a great learning experience!


NOTE: These shapes are the biggest threat for crashes

## Functions

```c
void rawr_drawline(byte x1, byte y1,byte x2, byte y2, byte b)
```
Draws an approximation of the line that would be formed between the two points, as colour specified by byte b. 

```c
void rawr_drawcircle(byte xc, byte yc, byte r, byte b);
```
Uses the midpoint circle algorithm to draw a circle outline centred around the point given with radius r as colour b.
I think max radius 64 before crashing?

```c
void rawr_drawcirclefilled(byte xc, byte yc, byte r, byte b);
```
Draws a filled circle centred at the point, with radius r and byte b. An entirely different algorithm is used, and so the outline of a filled circle and an unfilled circle with the same radius at the same point may be different. More noticable at larger radii.
Radius is clamped to 35 and 1.

```c
void rawr_drawrect(byte x, byte y, byte w, byte h, byte b);
```
Draws a rectangle, simply uses four lines drawn by `drawline`.