#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 10

int buffer[SIZE];
int in = 0, out = 0;

pthread_mutex_t mutex;
sem_t empty, full;
pthread_t pprod[SIZE], pcons[SIZE];

void initialize()
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, SIZE);  // empty slots
    sem_init(&full, 0, 0);      // filled slots
}

void write_item (int item){
    buffer[in] = item;
    in = (in+1)%SIZE;
};

int read_item() {
    int item = buffer[out];
    out = (out+1)%SIZE;
    return item;
};

void *producer (void *p){
    int item = rand()%5;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    
    write_item(item);
    printf("Producer produced item: %d\n", item);

    pthread_mutex_unlock(&mutex);
    sem_post(&full);

    pthread_exit(NULL);
};

void *consumer (void *p){
    int deleted_item;
    sem_wait(&full);

    pthread_mutex_lock(&mutex);
    deleted_item = read_item();
    printf ("Consumer consumed item : %d\n", deleted_item);

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    pthread_exit(NULL);
}

int main ()
{
    int i, n1, n2;
    initialize();
    printf("Enter number of producers: ");
    scanf("%d", &n1);
    printf("Enter number of consumers: ");
    scanf("%d", &n2);

    for (i = 0; i < n1; i++)
    pthread_create(&pprod[i], NULL, producer, NULL);

    for (i = 0; i < n2; i++)
        pthread_create(&pcons[i], NULL, consumer, NULL);

    for (i = 0; i < n1; i++)
        pthread_join(pprod[i], NULL);

    for (i = 0; i < n2; i++)
        pthread_join(pcons[i], NULL);

    return 0;
}


