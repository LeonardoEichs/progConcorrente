#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int size, rank, buffer[2] = {1,2};
  MPI_Status st;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int i;
  if(rank == 0) { // rank 0 envia para todos outros processos
    for (i = 1; i<size; i++)
      MPI_Send(&buffer, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
  }

  else { // todos outros processos recebem do rank 0
    MPI_Recv(&buffer,2,MPI_INT,0,MPI_ANY_TAG, MPI_COMM_WORLD, &st);
    MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  int tmp;
  if (rank == 0){
    for(i = 1; i < size; i++) {
      MPI_Recv(&tmp,1,MPI_INT,i,0, MPI_COMM_WORLD, &st);
      printf("Rank escravo: %d\n", tmp);
    }
  }

  MPI_Finalize();
  return 0;

}
