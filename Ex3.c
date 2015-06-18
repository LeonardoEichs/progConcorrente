#include <stdio.h>
#include <unistd.h>

main(){

  int pid_pai;
  pid_t pid = fork();

  if(pid > 0){
    pid_pai = pid;
    pid = fork();
  }

  if(pid == 0){
    pid = fork();
    if(pid > 0)
      pid = fork();
  }

  printf("Processo %d filho de %d\n",getpid(), getppid());

}
