#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

void *PrintHello(void	*arg)	{

  long int val = (long int) arg;
  pthread_t tid = pthread_self();
  printf("Nova thread criada. TID = %u \n", (unsigned int)tid);
  pthread_exit(NULL);

}

int main(){

  pthread_t thread;
  long int arg = 10;
  pthread_create(&thread, NULL, PrintHello, (void*)arg);
  pthread_join(thread, NULL);
  pthread_exit(NULL);


}
