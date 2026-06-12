#include <stdio.h>#include <pthread.h>#include <unistd.h>
#define N 5
pthread_mutex_t chopstick[N];pthread_t philosophers[N];
void* philosopher(void* num){    int id = *(int*)num;
    while (1)    {        printf("Philosopher %d is thinking\n", id);        sleep(1);
        pthread_mutex_lock(&chopstick[id]);        sleep(1);        pthread_mutex_lock(&chopstick[(id + 1) % N]);
        printf("Philosopher %d is eating\n", id);        sleep(2);
        pthread_mutex_unlock(&chopstick[id]);        pthread_mutex_unlock(&chopstick[(id + 1) % N]);    }}
int main(){    int i, ids[N];
    for (i = 0; i < N; i++)        pthread_mutex_init(&chopstick[i], NULL);
    for (i = 0; i < N; i++)    {        ids[i] = i;        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);    }
    for (i = 0; i < N; i++)        pthread_join(philosophers[i], NULL);
    for (i = 0; i < N; i++)        pthread_mutex_destroy(&chopstick[i]);
    return 0;}#include <stdio.h>#include <pthread.h>#include <unistd.h>
#define N 5
pthread_mutex_t chopstick[N];pthread_t philosophers[N];
void* philosopher(void* num){    int id = *(int*)num;
    while (1)    {        printf("Philosopher %d is thinking\n", id);        sleep(1);
        if (id % 2 == 0) {            pthread_mutex_lock(&chopstick[id]);            pthread_mutex_lock(&chopstick[(id + 1) % N]);        } else {            pthread_mutex_lock(&chopstick[(id + 1) % N]);            pthread_mutex_lock(&chopstick[id]);        }
        printf("Philosopher %d is eating\n", id);        sleep(2);
        pthread_mutex_unlock(&chopstick[id]);        pthread_mutex_unlock(&chopstick[(id + 1) % N]);    }}
int main(){    int i, ids[N];
    for (i = 0; i < N; i++)        pthread_mutex_init(&chopstick[i], NULL);
    for (i = 0; i < N; i++)    {        ids[i] = i;        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);    }
    for (i = 0; i < N; i++)        pthread_join(philosophers[i], NULL);
    for (i = 0; i < N; i++)        pthread_mutex_destroy(&chopstick[i]);
    return 0;}
