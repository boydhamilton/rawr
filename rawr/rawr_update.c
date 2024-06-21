


#include"rawr_update.h"

#include<stdio.h>

byte rawr_keys[6] = {0}; // init to 0

byte rawr_quit = 0;

byte rawr_continuouslysweepforcontroller = 1;

SDL_GameController* controller = NULL;


static byte joystickdown[6];


int rawr_lookforcontroller(){
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            controller =  SDL_GameControllerOpen(i);
            return 1;
        }
    }
    return 0;
}

void rawr_updateevents(){

    SDL_Event event;

    if(controller==NULL && rawr_continuouslysweepforcontroller)
        rawr_lookforcontroller(); // we look for controller 

    while(SDL_PollEvent(&event)){
        
        switch (event.type)
        {
            case SDL_QUIT:
                rawr_quit = 1;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        rawr_keys[0] = 1;
                        break;

                    case SDLK_DOWN:
                        rawr_keys[1] = 1;
                        break;

                    case SDLK_RIGHT:
                        rawr_keys[2] = 1;
                        break;
                    
                    case SDLK_LEFT:
                        rawr_keys[3] = 1;
                        break;
                    
                    case SDLK_c:
                        rawr_keys[4] = 1;
                        break;
                    
                    case SDLK_x:
                        rawr_keys[5] = 1;
                        break;

                    case SDLK_z:
                        rawr_keys[6] = 1;
                        break;
                    
                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        rawr_keys[0] = 0;
                        break;

                    case SDLK_DOWN:
                        rawr_keys[1] = 0;
                        break;

                    case SDLK_RIGHT:
                        rawr_keys[2] = 0;
                        break;
                    
                    case SDLK_LEFT:
                        rawr_keys[3] = 0;
                        break;
                    
                    case SDLK_c:
                        rawr_keys[4] = 0;
                        break;
                    
                    case SDLK_x:
                        rawr_keys[5] = 0;
                        break;

                    case SDLK_z:
                        rawr_keys[6] = 0;
                        break;
                    
                    default:
                        break;
                }
                break;

            
            default:
                break;
        }
        

        SDL_Delay(2); // 2ms for cpu kindness
    }
    
}


/*
0 up
1 down
2 right
3 left
4 c
5 x
6 z
*/
byte rawr_getkeystate(byte keyindex){
    // comes more into play when i have gamepad connected and return gamepad buttons from different array
    return rawr_keys[keyindex];
}