# PDC-PracticeTasks

## Note: All these files are separate from each other except for the socket files.

### 1. server.c and client.c
demonstrates a basic TCP client–server application in C, where the server listens on port 8080, receives a message from a client, replies with a greeting, and then closes the connection.

 - Compile: *gcc server.c -o server* and *gcc client.c -o client*
 - start the server first: *./server*
 - In another terminal, run the client: *./client*

### 2. server2.c and client2.c
program implements a TCP client–server interaction where the server randomly asks the client a question (name or SAP ID), receives the answer, and responds with a personalized greeting.

 - Compile: *gcc server2.c -fopenmp -o server2* and *gcc client2.c -o client2*
 - start the server first: *./server2*
 - In another terminal, run the client: *./client2*

### 3. para-server.c and paraiclient.c
program implements a TCP client–server application in C where the client sends a paragraph to the server, and the server counts the number of characters and sends the result back.

 - Compile: *gcc para-server.c -o para-server* and *gcc para-client.c -o para-client*
 - start the server first: *./para-server*
 - In another terminal, run the client: *./para-client*
