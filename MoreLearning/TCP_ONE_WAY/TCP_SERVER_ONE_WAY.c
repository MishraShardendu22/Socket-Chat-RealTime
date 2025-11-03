#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return 1;

    int port = 5000;
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 1);

    socklen_t cli_len = sizeof(client);
    int newsockfd = accept(sockfd, (struct sockaddr *)&client, &cli_len);
    if (newsockfd < 0) return 1;

    const char *msg = "Hello from server";
    send(newsockfd, msg, strlen(msg), 0);

    close(newsockfd);
    close(sockfd);
    return 0;
}
