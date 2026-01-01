#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <omp.h>
#include <time.h>

#define PORT 8080

void process_client(int client_sock) {
    char buffer[1024] = {0};
    char question[100];

    // Randomly choose a question
    srand(time(NULL));
    int choice = rand() % 2; // 0 or 1

    if (choice == 0) {
        strcpy(question, "What is your name?");
    } else {
        strcpy(question, "What is your SAP ID?");
    }

    // Send question to client
    send(client_sock, question, strlen(question), 0);

    // Receive answer
    int r = read(client_sock, buffer, sizeof(buffer));
    buffer[r] = '\0';  // Ensure string ends properly

    printf("Client answered: %s\n", buffer);

    char response[200];
    if (choice == 0)
        sprintf(response, "Hello %s!", buffer);
    else
        sprintf(response, "Hello SAP ID %s!", buffer);

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

        #pragma omp parallel sections
        {
            #pragma omp section
            process_client(client_sock);
        }
    }

    close(server_fd);
}

int main() {
    start_server();
    return 0;
}
