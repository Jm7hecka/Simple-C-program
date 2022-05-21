#include <xinput.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int vibrate(int leftmotorspeed, int rightmotorspeed){ //handle vibration//
    XINPUT_VIBRATION vibrate; //struct of vibration//
    ZeroMemory(&vibrate, sizeof(XINPUT_VIBRATION));
    vibrate.wLeftMotorSpeed = leftmotorspeed; //left motor's speed//
    vibrate.wRightMotorSpeed = rightmotorspeed; //right motor's speed//
    XInputSetState(0, &vibrate);    
    return 0;
}
int buttonpressed(WORD button){ //handle button pressed//
    switch(button){
            case XINPUT_GAMEPAD_A:
                printf("A button pressed\n");
                return 0;
            case XINPUT_GAMEPAD_B:
                printf("B button pressed \n");
                return 0;
            case XINPUT_GAMEPAD_Y:
                printf("Y button pressed \n");
                return 0;
            case XINPUT_GAMEPAD_X:  
                printf("X button pressed \n");
                return 0;
            case XINPUT_GAMEPAD_DPAD_DOWN: 
                printf("Dpad down\n");
                return 0;
            case XINPUT_GAMEPAD_DPAD_LEFT:
                printf("Dpad left\n");
                return 0;
            case XINPUT_GAMEPAD_DPAD_RIGHT:
                printf("Dpad right\n");
                return 0;
            case XINPUT_GAMEPAD_DPAD_UP:
                printf("Dpad up\n");
                return 0;
            case XINPUT_GAMEPAD_LEFT_SHOULDER:
                printf("Left shoulder pressed \n");
                return 0;
            case XINPUT_GAMEPAD_LEFT_THUMB:     
                printf("Left thumb pressed \n");
                return 0;
            case XINPUT_GAMEPAD_RIGHT_SHOULDER:
                printf("Right shoulder pressed \n");
                return 0;
            case XINPUT_GAMEPAD_RIGHT_THUMB:    
                printf("Right thumb pressed \n");
                return 0;  
            case XINPUT_GAMEPAD_START:
                printf("Start(Menu) button pressed \n");
                return 0;
            case XINPUT_GAMEPAD_BACK:
                printf("Back(View) button pressed \n");
                return 0;
        }
}
int rthumb(XINPUT_STATE state){ 
    float rx = state.Gamepad.sThumbRX, ry = state.Gamepad.sThumbRY; //get the value of thumb location(maxium 32767)// 
    float distance = sqrt(rx*rx + ry*ry); //find the distance of it (a^2 + b^2 = c^2)//
    float deadzone = 10000; //set your deadzone//
    float rxdir =  rx /distance; //check x's direction//
    float rydir = ry /distance; //check y'x direction/
    float rs =0;
    char xdirect[100];
    char ydirect[100];
    if(distance > deadzone){
        if(distance >32767) distance = 32767; //the maxium of value should be 32767//
        if(rx <-32767) rx = -32767; //maxium distance of left//
        if(ry <-32767) ry = -32767; //maxium distance of down//
        distance -= deadzone; //distance outside deadzone//
        rs = distance /(32767 - deadzone); //kinda percentage//
        if(rxdir > 0) { 
            strcpy(xdirect, "Right"); //the distance will be >0 if thumb goes right// 
        }else {
            strcpy(xdirect, "Left");
                rx *=  -1; // change from negative to positive//
        }
        if(rydir > 0){
            strcpy(ydirect, "Up"); //the distance will be >0 if thumb goes up//
        }else{
            strcpy(ydirect, "Down"); 
            ry*=-1; //change from negative to positive//
        }   
        printf("Right thumb: %s %f, %s %f\n", xdirect, (rx-deadzone)/(32767 - deadzone), ydirect, (ry-deadzone)/(32767 - deadzone));
    }else{
        distance = 0.0; 
        rs = 0.0;
    }
    return 0;
}
int lthumb(XINPUT_STATE state){ 
    float lx = state.Gamepad.sThumbLX, ly = state.Gamepad.sThumbLY;
    float distance = sqrt(lx *lx  + ly*ly);
    float deadzone = 10000;
    float lxdir =  lx  /distance;
    float lydir = ly /distance;
    float rs =0;
    char xdirect[100];
    char ydirect[100];
    if(distance > deadzone){
        if(distance >32767) distance = 32767;
        if(lx  <-32767) lx  = -32767;
        if(ly <-32767) ly = -32767;
        distance -= deadzone;
        rs = distance /(32767 - deadzone);
        if(lxdir > 0) {
            strcpy(xdirect, "Right");
        }else {
            strcpy(xdirect, "Left");
                lx  *=  -1;
        }
        if(lydir > 0){
            strcpy(ydirect, "Up");
        }else{
            strcpy(ydirect, "Down"); 
            ly*=-1;
        }   
        printf("Left thumb: %s %f, %s %f\n", xdirect, (lx -deadzone)/(32767 - deadzone), ydirect, (ly-deadzone)/(32767 - deadzone));
    }else{
        distance = 0.0; 
        rs = 0.0;
    }
    return 0;
}
int main(){
    DWORD status;
    int id = -1;
    printf("Waiting for connection...\n");
    for(DWORD i=0; i< XUSER_MAX_COUNT & id == -1; i++){
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        status = XInputGetState(0, &state); //check if controller connected to computer//
        if(status == ERROR_SUCCESS){ //return ERROR_SUCCESS if controller connected//
            printf("Connected \n");
            id = i;
            break;
        }
    }
    while(1){
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        XInputGetState(id, &state); //get the state of controller//
        if(state.Gamepad.wButtons){ //if button pressed//
            buttonpressed(state.Gamepad.wButtons);
            Sleep(200);
        }
        if(state.Gamepad.bLeftTrigger){ //if left trigger pressed//
            int value = ((float)state.Gamepad.bLeftTrigger /255) * 100; //calculate the percentage of trigger pressed//
            printf("Left trigger: %d%\n", value);
            Sleep(50);
        }
        if(state.Gamepad.bRightTrigger){ //if right trigger pressed//
            int value = ((float)state.Gamepad.bRightTrigger /255) * 100;
            printf("Right trigger: %d%\n", value);
            Sleep(50);
        }
        rthumb(state);
        lthumb(state);
    }
}

