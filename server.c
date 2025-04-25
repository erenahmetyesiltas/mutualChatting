#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5100
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t client_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("💬 Server listening on port %d...\n", PORT);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("🚀 Client connected!\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (strncmp(buffer, "/quit", 5) == 0) break;

        printf("👤 Client: %s\n", buffer);

        printf("🧑 Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(client_fd, buffer, strlen(buffer), 0);
        if (strncmp(buffer, "/quit", 5) == 0) break;
    }

    close(client_fd);
    close(server_fd);
    printf("🔒 Connection closed.\n");

    return 0;
}
