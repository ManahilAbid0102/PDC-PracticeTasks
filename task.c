//MPI_HOME="/usr/lib/x86_64-linux-gnu/openmpi"
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Hello from rank %d of %d running on %s\n",
           rank, size, processor_name);

    MPI_Finalize();
    return 0;
}
