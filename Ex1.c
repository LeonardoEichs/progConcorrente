#include <stdio.h>
#include <unistd.h>

main(){
  int i = 0;
  for(i = 0; i < 3; i++)
    fork();

  printf("Novo processo criado!\n");
}
