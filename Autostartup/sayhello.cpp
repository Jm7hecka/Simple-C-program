#include "windows.h"

int main(){
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    MessageBox(NULL, "Hello, Welcome to PC", "Start-Up notice", MB_OK);
    return 0;
}