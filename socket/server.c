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
//---------------//
#define addr "127.0.0.1" //local IP address//
#define port 8081 //port//

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
//Setup server//
    //Create socket//
    printf("Creating socket...\n");
    SOCKET sock = INVALID_SOCKET;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock == INVALID_SOCKET){
        printf("ERROR - Socket setup failed: %d\n", WSAGetLastError());
        return 1;
    }else {
        printf("Socket setted up...\n");
    }
    //Bind to address//
    printf("Socket binding to address...\n");
    struct sockaddr_in addrinfo;
    addrinfo.sin_family = AF_INET;
    addrinfo.sin_port = htons(port);
    addrinfo.sin_addr.s_addr = inet_addr(addr);
    res = bind(sock, (struct sockaddr *) &addrinfo, sizeof(addrinfo));
    if(res == SOCKET_ERROR){
        printf("ERROR - Bind failed: %d\n" ,WSAGetLastError());
        cleanupsocket(sock);
        return 1;
    }else{
        printf("Socket Binded to address...\n");
    }
    //set as listener//
    //SOMAXCONN - maximum connenction//
    res = listen(sock, SOMAXCONN);
    if(res == SOCKET_ERROR){
        printf("ERROR - Listen failed: %d\n", WSAGetLastError());
        cleanupsocket(sock);
        return 1;
    }else{
        printf("Listening as %s:%d\n", addr, port);
    }
//Handle client//
    //accept client//
    SOCKET client;
    struct sockaddr_in clientaddr;
    int clientaddrlen;
    client = accept(sock, NULL, NULL);
    if(client == INVALID_SOCKET){
        printf("ERROR - Could not accept client: %d", WSAGetLastError());
        cleanupsocket(sock);
        
    }
    //get client info//
    getpeername(client, (struct sockaddr *) &clientaddr, &clientaddrlen);
    printf("Client connected...\n");

    //Send message to client//
    char *message = "Hello my client :)";
    res = send(client, message, strlen(message), 0);
    if(res != strlen(message)){
        printf("ERROR - Could not send data to client\n");
    }else{
        printf("Message sent\n");
    }
    //receive data from client//
    int response;
    char recvbuf[1024];
    do{
        response = recv(client, recvbuf, 1024, 0);
        if(response >0){
            printf("Data received: %s \n", recvbuf);
            memset(recvbuf, 0, 1024);
        }else if (response == 0){
            //shutdown client//
            printf("Shutting down client...");
            res = shutdown(client, SD_BOTH);
            break;
        }
    }while(res>0);
    
    
    
    cleanupsocket(sock);
    return 0;
}
int cleanupsocket(SOCKET sock){
//Cleanup//
    //shutdown server socket//
    printf("Shutting down server...\n");
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
