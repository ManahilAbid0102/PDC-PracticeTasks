#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Receive question from server
    read(sock, buffer, sizeof(buffer));
    printf("Server asks: %s\n", buffer);

    // User answers
    char answer[100];
    printf("Your answer: ");
    fgets(answer, sizeof(answer), stdin);
    answer[strcspn(answer, "\n")] = '\0'; // remove newline

    // Send answer back to server
    send(sock, answer, strlen(answer), 0);

    // Receive greeting from server
    read(sock, buffer, sizeof(buffer));
    printf("Server says: %s\n", buffer);

    close(sock);
    return 0;
}
