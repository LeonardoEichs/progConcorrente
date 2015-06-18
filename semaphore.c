#include <semaphore.h>
sem_t semaphore;

void *func_thread(void *arg) {
	sem_wait(&semaphore);
	// Trecho a ser executado
	sem_post(&semaphore);
	return 0;
}

int main(int argc, char **argv) [
	sem_init(semaphore, 0, 2);

	// Criação das threads : pthread_create() + pthread_join()

	sem_destroy(&semaphore);
	return 0;
}
