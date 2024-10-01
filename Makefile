
# rawrrrrrrr really good makefile

# build to exe
all:
	gcc -o rawr main.c rawr/rawr_shapes.c rawr/rawr_draw.c rawr/rawr_update.c rawr/rawr_light.c -Iextern/include -Lextern/lib -lmingw32 -lSDL2main -lSDL2


# build to dll
# all:
# 	gcc -shared -o rawr.dll -DBUILD_DLL main.c rawr/rawr_shapes.c rawr/rawr_draw.c rawr/rawr_update.c rawr/rawr_light.c -Iextern/include -Lextern/lib -lmingw32 -lSDL2main -lSDL2 -Wl,--out-implib,librawr.a
