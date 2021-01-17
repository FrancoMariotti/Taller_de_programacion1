/*	Escriba un ejemplo en el cual un thread incremente un contador global entero de a una unidad; 
	y otro thread del mismo proceso lo imprima. Ambos threads deben coordinar el acceso a la memoria 
	y deben correr sincronizados de forma que siempre se impriman los números 1,2,3,4....
*/
#define MAX_COUNT 10

int counter;
bool incremented;
pthread_mutex_t counter_mutex;

void* add_counter() {
	while(counter < MAX_COUNT) {
		pthread_mutex_lock(&mutex_global);
		if(!incremented) {
			counter++;
			incremented = true;
	        sleep(1);
		}
		pthread_mutex_unlock(&mutex_global);
	}
}

void* print_counter() {
	while(counter < MAX_COUNT) {
		pthread_mutex_lock(&mutex_global);
		if (incremented) {
			printf("counter:%d\n",counter);
			incremented = false;
	        sleep(1);
		}
		pthread_mutex_unlock(&mutex_global);
	}
}

int main(int argc, char const *argv[]) {
	counter = 0;
	incremented = false;

	pthread_t adder;
	pthread_t printer;

	pthread_mutex_init(&counter_mutex, NULL);

	pthread_create(&adder, NULL, add_counter, NULL);
	pthread_create(&printer, NULL, print_counter, NULL);
	
	pthread_join(&adder, NULL);
	pthread_join(&printer, NULL);
	pthread_mutex_destroy(&counter_mutex);
	return 0;
}