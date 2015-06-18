#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int compute_pi(unsigned int, unsigned int);

int main(int argc, char **argv) {
  unsigned int pontos;
  unsigned int pontos_no_circulo;
  unsigned int i;
  int size, rank;
  MPI_Status st;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (argc != 2) {
    printf("Uso:\n");
    printf("\t%s <numero de pontos a serem sorteados>\n", argv[0]);
    return 1;
  }

  pontos = atoi(argv[1]);

  if (rank > 0){
    pontos_no_circulo = compute_pi(rank, pontos/(size - 1));
    MPI_Send(&pontos_no_circulo, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  int tmp;
  int soma = 0;
  if (rank == 0){
    for(i = 1; i < size; i++) {
      MPI_Recv(&tmp,1,MPI_INT,i,0, MPI_COMM_WORLD, &st);
      printf("soma: %d\n",soma);
      soma = soma + tmp;
    }
      printf("Pi = %.040f\n", ((double)soma/(double)pontos)*4);
  }

  MPI_Finalize();
  return 0;
}

unsigned int compute_pi(unsigned int seed, unsigned int pontos) {
  unsigned int i;
  unsigned int pontos_no_circulo;
  double x,y;

  pontos_no_circulo = 0;
  srand(seed);

  for(i = 0; i < pontos; i++){
    x = (double) rand()/(double) (RAND_MAX);
    y = (double) rand()/(double) (RAND_MAX);

    if ((x*x + y*y) < 1) {
      pontos_no_circulo++;
    }
  }

  return pontos_no_circulo;

}
