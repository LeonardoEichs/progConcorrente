#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 50000000
//  export OMP_NUM_THREADS = 8;

int main(int argc, char *argv[]) {
  int i;

  double *c = (double *) malloc (sizeof(double) * SIZE);
  omp_set_num_threads(4);
  #pragma omp parallel
  #pragma omp for

  for (i = 0; i < SIZE; i++) {
    c[i] = sqrt(i*32) + sqrt(i*16+i*8) + sqrt(i*4+i*2+i);
    c[i] -= sqrt(i*32 * i * 16 + i *4+i*2+i);
    c[i] += pow(i*32,8) + pow(i*16,12);
  }

  //for(i = 0; i < SIZE; i++){
    //printf("Resultado: %f\n",c[i]);
  //}


  free(c);
  return 0;
}
