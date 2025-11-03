#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    // create a client
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) return 1;

    struct sockaddr_in server;
    socklen_t serv_len = sizeof(server);

    int port = 5000;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");;
    server.sin_port = htons(port);

    // mkae buffer to send file
    char buffer[256];
    FILE *fp;

    fp = fopen("received.txt", "wb");
    if (!fp) return 1;

    // send request to server
    sendto(sockfd, "START", 5, 0, (struct sockaddr *)&server, serv_len);

    ssize_t n;
    while ((n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL)) > 0){
        fwrite(buffer, 1, n, fp);
    }

    fclose(fp);
    close(sockfd);
    return 0;
}
