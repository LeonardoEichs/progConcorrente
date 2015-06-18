#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv); //  Inicializa o ambiente MPI
  printf("Hello World!\n");
  MPI_Finalize(); // Finaliza ambiente MPI
  return 0;
}

// Compilação mpicc HelloWorld1.c -o HelloWorld1
// Execução mpirun -np 3 ./HelloWorld1
