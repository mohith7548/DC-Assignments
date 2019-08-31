#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void myFunA ( void *ptr );
void myFunB ( void *ptr );

sem_t aArrived, bArrived;

int main(int args, char *argv[]) {

	pthread_t threadA;
	pthread_t threadB;

	char *msg1 = "Thread A";
	char *msg2 = "Thread B";

	sem_init(&aArrived, 0, 0);
	sem_init(&bArrived, 0, 0);

	pthread_create (&threadA, NULL, (void *) &myFunA, (void *) msg1);
	pthread_create (&threadB, NULL, (void *) &myFunB, (void *) msg2);

	pthread_join(threadA, NULL);
	pthread_join(threadB, NULL);

	sem_destroy(&aArrived);
	sem_destroy(&bArrived);

	return 0;
}

void myFunA(void *ptr) {
	char *msg = (char *)ptr;
//	printf("%s\n", msg);
	sleep(1);
	printf("%s\n", "a1");
	sem_post(&aArrived);
	sem_wait(&bArrived);
//	sem_post(&aArrived);
	sleep(2);
	printf("%s\n", "a2");

	pthread_exit(0);
}

void myFunB(void *ptr) {
	char *msg = (char *)ptr;
//	printf("%s\n", msg);
	sleep(10);
	printf("%s\n", "b1");
	sem_post(&bArrived);
	sem_wait(&aArrived);
//	sem_post(&bArrived);
	sleep(1);
	printf("%s\n", "b2");

	pthread_exit(0);
}
