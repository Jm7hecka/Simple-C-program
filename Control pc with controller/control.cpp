#include "windows.h"
#include "xinput.h"
#include "math.h"
#include "stdio.h"
#include "iostream"
#include "fstream"
#include "string"
#include "algorithm"

using namespace std;

int ldeadzone, rdeadzone, cursorspeed, scrollspeed;
bool pressing = 0, aenter = 0, tab=0, windowapp;

int readconfig(){ //read value from config file//
    ifstream config("controller.config"); //open config file//
    if(config.is_open()){ 
        string line;
        while(getline(config, line)){ //getline from file//
            // if(line[0] == '#' || line.empty()){continue;} //ignore line with # or empty/
            auto find = line.find('='); //find the = sign//
            auto name = line.substr(0, find-1); //get value before = //
            auto value = line.substr(find + 2); //get value after = //
            if(name == "ldeadzone"){ldeadzone = stoi(value);} //turn value into int and store it //
            if(name == "rdeadzone"){rdeadzone = stoi(value);} //turn value into int and store it //
            if(name == "cursorspeed"){cursorspeed= stoi(value);} //turn value into int and store it //
            if(name == "scrollspeed"){scrollspeed = stoi(value);} //turn value into int and store it //
        }
    }
    return 0;
} 
int button(WORD state){ //handle button//
    INPUT input[10];
    ZeroMemory(&input, sizeof(input));
    int inputsize;
    switch(state){
        
        case XINPUT_GAMEPAD_START: //if it's menu button, press and release window button//
            input[0].type = INPUT_KEYBOARD; //set type of it//
            input[0].ki.wVk = VK_LWIN; //what button to press//
            input[1].type = INPUT_KEYBOARD; //set type of it//
            input[1].ki.wVk = VK_LWIN; //what button to press//
            input[1].ki.dwFlags = KEYEVENTF_KEYUP; //it should be release//
            inputsize = 2;
            windowapp = 1;
            break;
        case XINPUT_GAMEPAD_A: //if it's A button//
            if(aenter){
                input[0].type = INPUT_KEYBOARD;
                input[0].ki.wVk = VK_RETURN;
                input[1].type = INPUT_KEYBOARD;
                input[1].ki.wVk = VK_RETURN;
                input[1].ki.dwFlags = KEYEVENTF_KEYUP;
                inputsize = 2;
                aenter = 0;
            }else if(tab){ 
                input[0].type = INPUT_KEYBOARD;
                input[0].ki.wVk = VK_LMENU;              
                input[0].ki.dwFlags = KEYEVENTF_KEYUP;
                input[1].type = INPUT_KEYBOARD;
                input[1].ki.wVk = VK_TAB;
                input[1].ki.dwFlags = KEYEVENTF_KEYUP;
                input[2].type = INPUT_KEYBOARD;
                input[2].ki.wVk = VK_SHIFT;
                input[2].ki.dwFlags = KEYEVENTF_KEYUP;
                tab = 0;
                inputsize = 3;
            }else{ //it presses and releases left mouse//
                input[0].type = INPUT_MOUSE; 
                input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                input[1].type = INPUT_MOUSE;
                input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
                inputsize = 2;
            }
            break;
        case XINPUT_GAMEPAD_BACK: //if it's back button. right click mouse//
                input[0].type = INPUT_MOUSE;
                input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
                input[1].type = INPUT_MOUSE;
                input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
                inputsize = 2;
                break;
        case XINPUT_GAMEPAD_LEFT_THUMB: //if it's left thumb, middle click mouse//
                input[0].type = INPUT_MOUSE;
                input[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
                input[1].type = INPUT_MOUSE;
                input[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
                inputsize = 2;
                break;
        case XINPUT_GAMEPAD_B: //if it's B button, press window and left arrow(go back to last page)//
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_LMENU;
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = VK_LEFT;
            input[2].type = INPUT_KEYBOARD;
            input[2].ki.wVk = VK_LMENU;
            input[2].ki.dwFlags = KEYEVENTF_KEYUP;
            input[3].type = INPUT_KEYBOARD;
            input[3].ki.wVk = VK_LEFT;
            input[3].ki.dwFlags = KEYEVENTF_KEYUP;
            inputsize = 4;
            break;
        case XINPUT_GAMEPAD_Y: //if it's Y button,  press window and M(minimize winow)//
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_LWIN;
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = 0x4D;
            input[2].type = INPUT_KEYBOARD;
            input[2].ki.wVk = VK_LWIN;
            input[2].ki.dwFlags = KEYEVENTF_KEYUP;
            input[3].type = INPUT_KEYBOARD;
            input[3].ki.wVk = 0x4D;
            input[3].ki.dwFlags = KEYEVENTF_KEYUP;
            inputsize = 4;
            break;
        case XINPUT_GAMEPAD_LEFT_SHOULDER: //if it's left shoulder, alt+shift+tab//
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_LMENU;              
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = VK_SHIFT;
            input[2].type = INPUT_KEYBOARD;
            input[2].ki.wVk = VK_TAB; 
            input[3].type = INPUT_KEYBOARD;
            input[3].ki.wVk = VK_TAB; 
            input[3].ki.dwFlags = KEYEVENTF_KEYUP;
            inputsize = 4;
            tab = 1;
            break;
        case XINPUT_GAMEPAD_RIGHT_SHOULDER: //if it's right shoulder, alt+tab//
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_SHIFT;
            input[0].ki.dwFlags = KEYEVENTF_KEYUP;
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = VK_LMENU;              
            input[2].type = INPUT_KEYBOARD;
            input[2].ki.wVk = VK_TAB;
            input[3].type = INPUT_KEYBOARD;
            input[3].ki.wVk = VK_TAB; 
            input[3].ki.dwFlags = KEYEVENTF_KEYUP;
            tab = 1;
            inputsize = 4;
            break;   
        //those are arrow button//
        case XINPUT_GAMEPAD_DPAD_DOWN: 
            if(windowapp){
                break;
            }
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_DOWN;
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = VK_DOWN;
            input[1].ki.dwFlags = KEYEVENTF_KEYUP;
            inputsize = 2;
            break;
        case XINPUT_GAMEPAD_DPAD_LEFT:
            if(windowapp){
                break;
            }
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_LEFT;
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = VK_LEFT;
            input[1].ki.dwFlags = KEYEVENTF_KEYUP;
            inputsize = 2;
            break;
        case XINPUT_GAMEPAD_DPAD_RIGHT:
            if(windowapp){
                break;
            }
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_RIGHT;
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = VK_RIGHT;
            input[1].ki.dwFlags = KEYEVENTF_KEYUP;
            inputsize = 2;
            break;
        case XINPUT_GAMEPAD_DPAD_UP:
            if(windowapp){
                break;
            }
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_UP;
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = VK_UP;
            input[1].ki.dwFlags = KEYEVENTF_KEYUP;
            inputsize = 2;
            break;
    }
    if(pressing){
        Sleep(150); //sleep for a while(prevent it detects too fast)//
        SendInput(inputsize, input, sizeof(INPUT)); //send input of key pressed//
        pressing = 0;
    }
    
    return 0;
}
bool kbd = 0;
int showkbd(){ //show keyboard(can open but cannot use by controller QwQ), just ignore it//
    INPUT input[7];
    ZeroMemory(&input, sizeof(input));
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_LWIN;
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VK_CONTROL;
    input[2].type = INPUT_KEYBOARD;
    input[2].ki.wVk = 0x4F;
    input[3].type = INPUT_KEYBOARD;
    input[3].ki.wVk = VK_LWIN;
    input[3].ki.dwFlags = KEYEVENTF_KEYUP;
    input[4].type = INPUT_KEYBOARD;
    input[4].ki.wVk = VK_CONTROL;
    input[4].ki.dwFlags = KEYEVENTF_KEYUP;
    input[5].type = INPUT_KEYBOARD;
    input[5].ki.wVk = 0x4F;
    input[5].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(6, input, sizeof(INPUT));
    return 0;
}
int scroll(XINPUT_STATE state){ //scroll when moving right thumb//
    INPUT scroll[1];
    scroll[0].type = INPUT_MOUSE; //set type//
    scroll[0].mi.dwFlags = MOUSEEVENTF_WHEEL; //set flag//
    float ry = state.Gamepad.sThumbRY; //get value of thumb pushed//
    if(ry > rdeadzone ){ //if it's more than deadzone//
        scroll[0].mi.mouseData = (ry/32767) *scrollspeed; //maxium of thumb pushed is 32767, so it is 1 * scrollspeed//
        SendInput(1, scroll, sizeof(INPUT)); //send scroll input//
    }else if(ry < rdeadzone*-1){
        scroll[0].mi.mouseData = (ry/32767) *scrollspeed;
        SendInput(1, scroll, sizeof(INPUT));
    }
    Sleep(1);
    return 0;
}
int cursormove(XINPUT_STATE state){ //this is a useful but complicate one//
    POINT cursor;
    GetCursorPos(&cursor); //get position of cursor//
    float currentx = cursor.x; //cursor's x axis//
    float currenty = cursor.y; //cursor's y axis//

    float lx = state.Gamepad.sThumbLX, ly = state.Gamepad.sThumbLY; //get the value of left thumb position//
    float distance = sqrt(lx*lx + ly*ly); //get distance by pythagoras' theorem(you should know it if you are not idiot)//
    float xdir = lx/distance, ydir = ly/distance;//get their direction(-1 to +1)//
    if(distance > ldeadzone){ //if thumb is outside deadzone//
        if(xdir>0.2){ //check if it's going left or right//
            currentx += (lx/32767) *cursorspeed; //maxium of lx is 32767, so the maxium would be 1 * cursorspeed//
        }else if(xdir<0) {
            currentx -= ((lx*-1)/32767) *cursorspeed; //*-1 is to change the value back to positive//
        }
        if(ydir >0.2){
            currenty -= (ly/32767) *cursorspeed;
        }else if(ydir <0){
            currenty += ((ly* -1)/32767) *cursorspeed;
        }
        SetCursorPos(currentx, currenty); //set cursor's position//
        Sleep(1);
    }
    return 0;
}
int control(int id){
    XINPUT_STATE state;
    XInputGetState(id, &state); //get controller state//
    if(state.Gamepad.wButtons){ //if button pressed//
        pressing = 1;
        button(state.Gamepad.wButtons);
    }
    if(state.Gamepad.bLeftTrigger > 200){ //if left trigger pressed//
        showkbd();
    }
    cursormove(state); //move cursor//
    scroll(state); //scroll//
    return 0;
}
int main(){
    int id = -1; 
    DWORD status;
    readconfig();
    printf("Connecting...\n");
    for(DWORD i=0; i< XUSER_MAX_COUNT; i++){
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        status = XInputGetState(i, &state); //check if controller connected to computer//
        if(status == ERROR_SUCCESS){ //return ERROR_SUCCESS if controller connected//
            printf("Connected \n");
            id = i;
            while(id != -1){
                control(id);
            }
        }else{
            i = -1;
        }
    }
   
}