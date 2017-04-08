#include <stdio.h> 
#include <string.h> 
#include <mpi.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int my_rank, np, origem, destino, tag = 0; 
    char msg[100]; 
    MPI_Status status; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &np); 
    if (my_rank != 0) {
        sprintf(msg, "Processo %d está vivo !", my_rank); 
        destino = 0; 
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, destino, tag, MPI_COMM_WORLD); 
    } else { // if (my_rank == 0)
        for (origem = 1; origem < np; origem++) {
            MPI_Recv(msg, 100, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status); 
            printf("%s\n", msg); 
        }
    }
    MPI_Finalize();
    return 0;
}
