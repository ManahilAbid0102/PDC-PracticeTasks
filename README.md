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

### 4. task.c
a basic MPI application where multiple processes run in parallel and each prints its rank, total number of processes, and the processor name.

 - Compile: *mpicc task.c -o task* 
 - run: *mpirun -np 4 ./task* (You can change 4 to any number of processes.)

### 5. openmp.c
program uses OpenMP to perform parallel element-wise multiplication of two arrays, computes their sum, and compares sequential setup time with parallel execution time.

 - Compile: *gcc openmp.c -fopenmp -o openmp*
 - run: *./openmp*

### 6. practice.c
a basic MPI “Hello World” example where each parallel process prints its rank and the total number of processes.

 - Compile: *mpicc practice.c -o practice*
 - run: *mpirun -np 4 ./practice* (You can change 4 to any number of processes.)

### 7. sum_openmp.c
program uses OpenMP to compute the sum of an array in parallel with different thread counts and compares execution time and speedup against serial execution.

 - Compile: *gcc sum_openmp.c -fopenmp -o sum_openmp*
 - run: *./sum_openmp*
