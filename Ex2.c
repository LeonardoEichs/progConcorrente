#include <stdio.h>
#include <unistd.h>

main(){

  pid_t pid = fork();
  int i;
  int pid_pai;
  if(pid > 0){
    pid_pai = pid;
    for(i = 0; i < 4; i++){
      if(pid > 0)
        pid = fork();
    }
    if(pid == 0){
      printf("Processo pai %d criou %d \nProcesso filho %d\n", pid_pai, getpid(),getpid());
    }
  }



}
