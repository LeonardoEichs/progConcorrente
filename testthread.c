#include <unistd.h>#include <sys/types.h>#include <stdio.h>#include <pthread.h>#define MAX_THREADS 8pthread_mutex_t global_mutex;int global = 0;void *PrintHello(void	*arg)	{  long int val = (long int) arg;  pthread_t tid = pthread_self();  int i;  pthread_mutex_lock(&global_mutex);  for(i = 0; i < 100 ; i++){    global++;  }  pthread_mutex_unlock(&global_mutex);  printf("Nova thread criada. TID = %u \nGlobal = %d \n", (unsigned int)tid, global);  pthread_exit(NULL);}int main(int argc, char **argv){  pthread_t thread[MAX_THREADS];  long int arg = 10;  int i;  for(i = 0; i < MAX_THREADS; i++){    arg++;    pthread_create(&thread[MAX_THREADS], NULL, PrintHello, (void*)arg);  }  for(i = 0; i < MAX_THREADS; i++){    pthread_join(thread[MAX_THREADS], NULL);  }  pthread_exit(NULL);}