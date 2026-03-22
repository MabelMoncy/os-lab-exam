#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semaphores
sem_t mutex;     // Protects read_count
sem_t rw_mutex;  // Controls access to shared resource
sem_t queue;     // Ensures writer priority

int read_count = 0;

// Reader function
void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&queue);   // Block if writer is waiting
    sem_wait(&mutex);

    read_count++;

    if (read_count == 1)
        sem_wait(&rw_mutex); // First reader blocks writers

    sem_post(&mutex);
    sem_post(&queue);

    // Reading section
    printf("Reader %d is READING\n", id);
    sleep(1);
    printf("Reader %d has FINISHED READING\n", id);

    sem_wait(&mutex);

    read_count--;

    if (read_count == 0)
        sem_post(&rw_mutex); // Last reader allows writer

    sem_post(&mutex);

    return NULL;
}

// Writer function
void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&queue);     // Writer gets priority
    sem_wait(&rw_mutex);  // Exclusive access

    // Writing section
    printf("\tWriter %d is WRITING\n", id);
    sleep(2);
    printf("\tWriter %d has FINISHED WRITING\n", id);

    sem_post(&rw_mutex);
    sem_post(&queue);

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    int id[5];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    sem_init(&queue, 0, 1);

    // Create threads
    for (int i = 0; i < 5; i++) {
        id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &id[i]);
        pthread_create(&writers[i], NULL, writer, &id[i]);
    }

    // Join threads
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    sem_destroy(&queue);

    return 0;
}