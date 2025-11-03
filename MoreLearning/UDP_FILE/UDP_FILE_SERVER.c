#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
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

    // bind 
    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    // make client 
    struct sockaddr_in client;
    socklen_t cli_len = sizeof(client);

    // read file and send to client
    char buffer[256];
    size_t n;
    FILE *fp;

    fp = fopen("file.txt", "rb");
    if (!fp) return 1;

    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &cli_len);

    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0){
        sendto(sockfd, buffer, n, 0, (struct sockaddr *)&client, cli_len);
    }

    fclose(fp);
    close(sockfd);
    return 0;
}
