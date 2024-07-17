

#ifndef RAWR_LIGHTH_
#define RAWR_LIGHTH_



#ifndef PI_VIA_RAWR
#define PI_VIA_RAWR 3.14159265359
#endif

#ifndef RAWR_DRAWH_
#include"rawr_draw.h"
#endif

#ifndef RAWR_SHAPESH_
#include"rawr_shapes.h"
#endif

void rawr_setlightingenv();

void rawr_pointlight(byte xc, byte yc, byte r, byte b_illum, byte b_coll);

#endif