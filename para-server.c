#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void process_client(int client_sock) {
    char buffer[2048] = {0};

    // Receive paragraph from client
    int r = read(client_sock, buffer, sizeof(buffer));
    if (r <= 0) {
        printf("Failed to read from client.\n");
        close(client_sock);
        return;
    }

    buffer[r] = '\0';  // Null-terminate received text
    printf("Received paragraph: %s\n", buffer);

    // Count characters (excluding '\0')
    int count = strlen(buffer);

    // Prepare response
    char response[100];
    sprintf(response, "The paragraph contains %d characters.", count);

    // Send response to client
    send(client_sock, response, strlen(response), 0);

    close(client_sock);
    printf("Client disconnected.\n");
}

void start_server() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected.\n");
        process_client(client_sock);
    }

    close(server_fd);
}

int main() {
    start_server();
    return 0;
}
