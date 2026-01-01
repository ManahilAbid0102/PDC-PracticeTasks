#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <omp.h>
int PORT = 8080;

void process_client(int client_sock){
    
    char buffer[1024] = {0};
    
    int r =read(client_sock, buffer, sizeof(buffer));
    
    printf("The client says:  %s ",buffer);
    char *message = "Hello from Server";
    send(client_sock, message, strlen(message), 0);

    // Close the connection
    close(client_sock);
    printf("Client disconnected.\n");

}
void start_server(){
    int server_fd, client_sock, *new_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // 1️⃣ Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // 2️⃣ Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 3️⃣ Bind socket to IP/port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4️⃣ Listen for clients
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);
    
    client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        
            if (client_sock < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
                close(server_fd);
            }
    process_client(client_sock);
            
    


}


int main(){
    start_server();
    
    return 0;
}