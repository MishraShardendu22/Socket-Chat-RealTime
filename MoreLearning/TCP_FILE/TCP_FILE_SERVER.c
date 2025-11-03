#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg){
    perror(msg);
    exit(1);
}

int main(){
    // make server
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0){
        return 1;
    }

    int port = 5000;
    struct sockaddr_in server;
    server.sin_family = AF_INET; // IPv4
    server.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    server.sin_port = htons(port); // Port number

    // bind and listen server
    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd,5);

    // make client
    struct sockaddr_in client;
    socklen_t cli_len = sizeof(client);
    int newsockfd = accept(sockfd, (struct sockaddr*)&client, &cli_len);
    if (newsockfd < 0){
        return 1;
    }

    // open file to send the file to client
    FILE* fp;
    fp = fopen("received_file.txt", "wb");
    if (fp == NULL){
        return 1;
    }

    // reads buffer size at once sends then next 
    char buffer[256];
    size_t n;
    
    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0){
        send(newsockfd, buffer, n, 0);
    }

    // close all
    fclose(fp);
    close(newsockfd);
    close(sockfd);

    return 0;
}