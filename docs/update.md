
# rawr_update.h


# Exposed variables

```c
byte rawr_keys[6];
```
The key states gathered in [updateevents](#functions). Shows the current state of a given key, is 1 if it's down, only switching to 0 once it is released.

```c
byte rawr_quit;
```
1 if a quit event is triggered (closing the window etc.), otherwise 0. It should be used as the condition a game loop.
e.x.
```c
while(!rawr_quit){
    rawr_updateevents();
    rawr_draw();
}
rawr_free()
```

```c
byte rawr_continuouslysweepforcontroller;
```
Set to 1 if you want to check for a controller every frame, 0 otherwise.

# Functions

```c
int rawr_lookforcontroller();
```
Scans ports to find a controller, returns 1 if a controller is found, and 0 otherwise.

```c
void rawr_updateevents();
```
Poll SDL2, update keystates etc. call before updating stuff like key updates
e.x.
```c
while(!rawr_quit){
    rawr_updateevents();
    /*update stuff*/
    if(rawr_getkeystate(0))
        // do stuff 
    rawr_draw();
}
rawr_free()
```

```c
byte rawr_getkeystate(byte keyindex);
```
Return the state of the key specified. 
Key state indicies:
```
0 up arrow
1 down arrow
2 right arrow
3 left arrow
4 c
5 x
6 z
```