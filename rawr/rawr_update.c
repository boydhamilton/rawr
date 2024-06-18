


#include"rawr_update.h"

#include<stdio.h>

byte rawr_keys[6]; // im definetly bitshifting you later on

byte rawr_runupdate = 1;
byte rawr_quit = 0;

byte rawr_continuouslysweepforcontroller = 1;

SDL_GameController* controller = ((void*)0);


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

    memset(rawr_keys, 0, sizeof(byte) * 6);

    if(controller==((void*)0) && rawr_continuouslysweepforcontroller)
        rawr_lookforcontroller(); // we look for controller 

    while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT)
            rawr_quit = 1;

        // if(event.type == SDL_JOYBUTTONDOWN){
        //     switch(event.jbutton.button){
        //         case 0:
        //             joystickdown[4] = 1;
        //             break;
        //         case 1:
        //             joystickdown[5] = 1;
        //             break;
        //         case 2:
        //             joystickdown[6] = 1;
        //             break;
        //         case 3:
        //             joystickdown[4] = 1;
        //             break;
        //     }
        // }


        // if(event.type == SDL_JOYAXISMOTION){
        //     if(( event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 )){

        //         if(event.jaxis.axis == 0){
        //             if(event.jaxis.value < 0)
        //                 joystickdown[3] = 1;
        //             else if(event.jaxis.value > 0)
        //                 joystickdown[2] = 1;
        //         }

        //         if(event.jaxis.axis == 1){
        //             if(event.jaxis.value < 0)
        //                 joystickdown[1] = 1;
        //             else if(event.jaxis.value > 0)
        //                 joystickdown[0] = 1;
        //         }
        //     }
        // }


        // for(int i=0; i<6; i++){
        //     rawr_keys[i] = joystickdown[i];
        // }


        switch(event.key.keysym.sym){
            case SDLK_UP:
                rawr_keys[0] = 1;
                break;

            case SDLK_DOWN:
                rawr_keys[1] =1;
                break;
            
            case SDLK_RIGHT:
                rawr_keys[2]= 1;
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
        }
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
    return rawr_keys[keyindex];
}