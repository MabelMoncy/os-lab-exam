#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t room;              // Limits philosophers (N-1)
sem_t chopstick[N];      // One semaphore per chopstick
sem_t mutex;             // For synchronized printing

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is THINKING\n", id);
        sleep(1);

        // Enter room (limit to N-1 philosophers)
        sem_wait(&room);

        // Pick up chopsticks
        sem_wait(&chopstick[id]);                 // Left
        sem_wait(&chopstick[(id + 1) % N]);       // Right

        // Eating (protected print)
        sem_wait(&mutex);
        printf("Philosopher %d is EATING\n", id);
        sem_post(&mutex);

        sleep(2);

        // Put down chopsticks
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        // Leave room
        sem_post(&room);
    }

    return NULL;
}

int main() {
    pthread_t tid[N];
    int phil[N];

    // Initialize semaphores
    sem_init(&room, 0, N - 1);  // Allow only 4 philosophers
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }

    // Join threads (runs indefinitely)
    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}