
# rawr_draw.h

rawr is made for bringing your arcade-game creativity to life, fostering new and different ideas through the inherent limitations present. It is important to know just how the framework brings your code to life. The most fundemental aspect of rawr is how it limits drawing to just 2 colours, and 64x64 pixels.

rawr is built on SDL2, which makes all of the drawing code very easy to understand.

## Exposed variables
```c
byte rawr_pixelmatrix[_H][_W/8];
```
Exposed 2D array responsible for keeping track of the states of all the different pixels on the screen. Because each pixel has a state of just a `1` or `0`, it is most space efficient to keep track of them using bits instead of bytes, which gives us the `_W/8` (8 bits per byte, so 8 states tracked per element).

## Functions

```c
int rawr_initdraw(int width, int height, char* title)
```
Initiates the rawr and SDL2 drawing enviroment and window, `width`, `height`, and `title` are all with respect to the window. 

```c
void rawr_free()
```
Quits SDL2 enviroment and cleans up resources used by rawr. Necessary to call at the end of any rawr program.

```c
byte rawr_getpixel(byte x, byte y)
```
Returns the state of the pixel at the given position as a byte `1` or `0`. 

```c
void rawr_setpixel(byte x, byte y, byte b)
```
Sets the pixel at the given position as least significant bit of byte `b`.

```c
void rawr_setonecol(byte r, byte g, byte b)
```
While each pixel can only be two colours, the two colours are mutable. The `1` state of the pixel will be represented with the rgb colour specified in the function.

```c
byte* rawr_getonecol()
```
Returns the current colour representing the `1` state.

```c
void rawr_setzerocol(byte r, byte g, byte b)
```
Same as above, but for `0` state.

```c
byte* rawr_getzerocol()
```
Same as above, but for `0` state.

```c
void rawr_clearmatrixto(byte b)
```
Clears the matrix to specified byte, uses renderer clearing and memset, so much faster than using `setpixel` for each pixel.

```c
void rawr_draw()
```
Using the unexposed `drawtorawr` function, the pixels that were changed the previous frame are all drawn to the texture. In `draw`, the texture is presented to the screen, and timeclamped to 33 fps. 