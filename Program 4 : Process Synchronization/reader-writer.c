#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int count = 0, rcount = 0;
sem_t mutex, wrt;

void* writer(void *p){
    int *i = (int*)p;
    sem_wait(&wrt);
        printf("\n Writer %d writes page number %d \n", *i, ++count);
    sem_post(&wrt);
    pthread_exit(NULL);
};

void* reader(void *p){
    int *i = (int*)p;
    sem_wait(&mutex);
    rcount++;
    if (rcount == 1){
        sem_wait(&wrt);
    } 
    sem_post(&mutex);
    printf("\n Reader %d is reading page number : %d \n", *i, count);

    sem_wait(&mutex);
    rcount--;
    if (rcount == 0){
        sem_post(&wrt);
    }
    sem_post(&mutex);
    pthread_exit(NULL);
}

int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    
    int a[6]={1,2,3,4,5,6};
    pthread_t p[6];

    for (int i=0; i<3; i++){
        pthread_create(&p[i], NULL, writer, &a[i]);
    }

    for (int i=3; i<6; i++){
        pthread_create(&p[i], NULL, reader, &a[i]);
    }

    for (int i=0; i<6; i++){
        pthread_join(p[i], NULL);
    }

    return 0;
}
