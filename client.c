#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5100
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        exit(EXIT_FAILURE);
    }

    printf("✅ Connected to server! Type messages below.\n");

    while (1) {
        printf("🧑 Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sockfd, buffer, strlen(buffer), 0);
        if (strncmp(buffer, "/quit", 5) == 0) break;

        memset(buffer, 0, BUFFER_SIZE);
        recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (strncmp(buffer, "/quit", 5) == 0) break;

        printf("👤 Server: %s", buffer);
    }

    close(sockfd);
    printf("🔒 Disconnected from server.\n");

    return 0;
}
