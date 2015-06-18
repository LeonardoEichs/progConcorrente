#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define N_PRODUTORES 5
#define N_CONSUMIDORES 10
#define N_BUFFER 30


int buffer[N_BUFFER];

sem_t pos_ocup;
sem_t pos_vazia;
sem_t lock_prod;
sem_t lock_cons;

int inicio = 0;
int final = 0;
int contador = 0;
void *produz() {
	while(1){
		sem_wait(&pos_vazia);
		sem_wait(&lock_prod);
		printf("PRODUZIR\n");
		final = (final + 1) % N_BUFFER;
		buffer[final] = 1;
		sem_post(&lock_prod);
		sem_post(&pos_ocup);
	}
}

void *consome(){
	while(1){
		sem_wait(&pos_ocup);
		sem_wait(&lock_cons);
		inicio = (inicio + 1) % N_BUFFER;
		printf("CONSOME\n");
		sem_post(&lock_cons);
		sem_post(&pos_vazia);
	}
}

int main(int argc, char **argv) {
	pthread_t thread_produtor[N_PRODUTORES];
	pthread_t thread_consumidor[N_CONSUMIDORES];

	sem_init(&pos_vazia,0 , N_BUFFER);
	sem_init(&pos_ocup,0 , 0);
	sem_init(&lock_prod, 0, 1);
	sem_init(&lock_cons, 0, 1);

	int i;

	for(i = 0; i < N_BUFFER; i++){
    pthread_create(&thread_produtor[i], NULL, produz, NULL);
  }

	for(i = 0; i < N_BUFFER; i++){
    pthread_create(&thread_consumidor[i], NULL, consome, NULL);
  }

	for(i = 0; i < N_BUFFER; i++){
    pthread_join(thread_produtor[i], NULL);
  }

	for(i = 0; i < N_BUFFER; i++){
    pthread_join(thread_consumidor[i], NULL);
  }

	sem_destroy(&pos_vazia);
	sem_destroy(&pos_ocup);
	sem_destroy(&lock_prod);
	sem_destroy(&lock_cons);


	pthread_exit(NULL);


	return 0;
}
