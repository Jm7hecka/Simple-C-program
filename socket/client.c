#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif 

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
//Link ws2_32 file//
#pragma comment(lib, "ws2_32.lib")

#define addr "127.0.0.1"
#define port 8081

int main() {
    printf("Hello world :) \n");
//Initialization//
    WSADATA ws;
    int res;
    //MAKEWORD - request version//
    printf("Initializing...\n");
    res = WSAStartup(MAKEWORD(2, 2), &ws);
    if (res){
        //Cant find usable winsock DLL//
        printf("ERROR - WSA startup fail: %d\n", WSAGetLastError());
        return 1;
    }else{
        //Winsock DLL support Version 2.2
        printf("WSA started up...\n");
    }
//Setup client server//
    //Setup socket//
    printf("Setting up socket...\n");
    SOCKET client;
    client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(client == INVALID_SOCKET){
        printf("ERROR - Cannot setup socket, %d \n", WSAGetLastError()); 
        WSACleanup();
        return 1;
    }else{
        printf("Setted up socket...\n");
    }
    //Connect to address//
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(addr);
    address.sin_port = htons(port);
    printf("Connecting to server... \n");
    res = connect(client, (struct sockaddr *)&address, sizeof(address));
    if(res == SOCKET_ERROR || res == INVALID_SOCKET){
        printf("ERROR - cannot connect to server, %d\n", WSAGetLastError());
        cleanupsocket(client);
        return 1;
    }
    printf("Connected to server...\n");
    int recvbuflen = 1024;
    char recvbuf[1024]; //place to store received data//
    res = recv(client, recvbuf, recvbuflen, 0);
    printf("Receiving data...\n");
    if(res > 0){
        printf("Message received from server : %s\n", recvbuf);
    }else if(!res){
        printf("Connection closed\n");
        cleanupsocket(client);
    }else{
        printf("ERROR - Receive failed: %d\n", WSAGetLastError());
    }
    printf("Sending data...\n");
    char *message = "Hello server :)";
    res = send(client, message, strlen(message), 0);
    if( res == SOCKET_ERROR){
        printf("ERROR - send failed: %d\n", WSAGetLastError());
        cleanupsocket(client);
    }
    do{
        char sendbuf[1024];
        printf("Enter message: ");
        scanf(" %[^\n]", sendbuf); //%[^\n]: scan everything until \n//
        int sendbuflen = strlen(sendbuf);
        res = send(client, sendbuf, sendbuflen, 0);
        if(res != sendbuflen){
            printf("ERROR - cannot send message, %d", WSAGetLastError());

        }else{
            printf("Sent \n");
        }
    }while(1);
    return 0;
}

int cleanupsocket(SOCKET sock){
//Cleanup//
    //shutdown server socket//
    printf("Shutting down client...\n");
    shutdown(sock, SD_BOTH);
    closesocket(sock);
    printf("Cleaning up...\n");
    int res = WSACleanup();
    if(res){
        printf("Cleanup failed:%d\n", res);
    }else{
        printf("WSA cleaned up\n");
    }
    printf("Bye World :( \n");
    return 0;
}
