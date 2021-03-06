#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_THREADS 8
//pthread_mutex_t global_mutex;
sem_t semaphore;
int global = 0;


void *PrintHello(void *arg) {

  long int val = (long int) arg;
  pthread_t tid = pthread_self();
  int i;
  for (i = 0; i < 100; i++) {
    //pthread_mutex_lock(&global_mutex);
    sem_wait(&semaphore);
    global++;
    sem_post(&semaphore);
    //pthread_mutex_unlock(&global_mutex);
  }
  pthread_exit(NULL);

}


main(int argc, char *argv){

  sem_init(&semaphore, 0, 1);
  pthread_t thread[MAX_THREADS];
  long int arg = 10;
  int i;
  for (i = 0; i < MAX_THREADS; i++) {
    arg++;
    pthread_create(&thread[i], NULL, PrintHello, (void*) arg);
  }

  for (i = 0; i < MAX_THREADS; i++) {
    pthread_join(thread[i], NULL);
  }

  printf("Global = %d\n", global);

  sem_destroy(&semaphore);
  pthread_exit(NULL);


}
