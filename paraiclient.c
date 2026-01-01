#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[2048] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    // Get paragraph input
    char paragraph[2048];
    printf("Enter a paragraph: ");
    fgets(paragraph, sizeof(paragraph), stdin);
    paragraph[strcspn(paragraph, "\n")] = '\0'; // Remove newline

    // Send paragraph to server
    send(sock, paragraph, strlen(paragraph), 0);

    // Receive response from server
    read(sock, buffer, sizeof(buffer));
    printf("Server says: %s\n", buffer);

    close(sock);
    return 0;
}
