pthread_mutex_t mutex;

void *func_thread(void *arg){
	pthread_mutex_lock(&mutex);
	// reagiao critica
	pthread_mutex_unlock(&mutex);
	return 0;
}

int main(int argc, char **argv){
	pthread_mutex_init(&mutex, NULL);
	pthread_create(...);
	pthread_join(...);
	pthread_mutex_destroy(&mutex);
	return 0;
}
