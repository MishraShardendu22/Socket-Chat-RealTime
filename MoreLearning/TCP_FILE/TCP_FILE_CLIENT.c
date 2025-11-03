#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    // make client
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0){
        return 1;
    }

    int port = 5000;

    struct sockaddr_in server;
    server.sin_family = AF_INET; // IPv4
    server.sin_addr.s_addr = inet_addr("127.0.0.1");; // Server IP address
    server.sin_port = htons(port);

    // connect to server
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0){
        return 1;
    }

    // store received file
    FILE *fp;
    fp = fopen("received_file.txt", "wb");
    if (fp == NULL){
        return 1;
    }

    char buffer[256];
    ssize_t n;

    while ((n = recv(sockfd, buffer, sizeof(buffer), 0)) > 0){
        fwrite(buffer, 1, n, fp);
    }

    fclose(fp);

    return 0;
}