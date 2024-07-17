
#rawrrrrrrr
all:
	gcc -o rawr main.c rawr/rawr_shapes.c rawr/rawr_draw.c rawr/rawr_update.c rawr/rawr_light.c -Ilib/include -Llib/lib -lmingw32 -lSDL2main -lSDL2