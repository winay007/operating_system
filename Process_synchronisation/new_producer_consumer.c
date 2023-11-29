// #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
// #include <unistd.h>
sem_t mutex;
sem_t full;
sem_t empty;

int in = 0, out = 0;
int item_produced = 0, item_consumed = 0;
int n = 20;
int buff[20];

void *producerfn(void *arg)
{

	int id = (*(int *)arg);
	while (item_produced < n)
	{
		int item = rand() % 100;
		sem_wait(&empty);
		sem_wait(&mutex);
		// add itemm
		buff[in] = item;
		printf("\nProducer %d  produce  %d ", id, item);
		// incrment
		in = (in + 1) % n;
		item_produced++;
		sem_post(&mutex);
		sem_post(&full);
		usleep(1000);
	}
	pthread_exit(NULL);
}

void *consumer(void *arg)
{
	int id = *((int *)arg);
	while (item_consumed < n)
	{
		sem_wait(&full);
		sem_wait(&mutex);

		int item = buff[out];
		out = (out + 1) % n;

		printf("\n Consumer %d  consume %d", id, item);
		item_consumed++;
		sem_post(&mutex);
		sem_post(&empty);
		usleep(10000);
	}
	pthread_exit(NULL);
}

int main()
{

	srand(time(NULL));
	sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, n);
	int p = 5;
	int c = 3;
	pthread_t producerThread[p];
	pthread_t consumerThread[c];

	int pthread[p];
	int cthread[c];

	for (int i = 0; i < p; i++)
	{
		pthread[i] = i + 1;
		pthread_create(&producerThread[i], NULL, producerfn, &pthread[i]);
	}

	for (int i = 0; i < c; i++)
	{
		cthread[i] = i + 1;
		pthread_create(&consumerThread[i], NULL, consumer, &cthread[i]);
	}

	for (int i = 0; i < p; i++)
	{
		pthread_join(producerThread[i], NULL);
	}

	for (int i = 0; i < c; i++)
	{
		pthread_join(consumerThread[i], NULL);
	}
	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}
