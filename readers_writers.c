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

    sem_wait(&queue);     // Wait if writers are waiting
    sem_wait(&mutex);

    read_count++;
    if (read_count == 1) {
        sem_wait(&rw_mutex);  // First reader blocks writers
    }

    sem_post(&mutex);
    sem_post(&queue);

    // Critical Section (Reading)
    printf("Reader %d is READING\n", id);
    sleep(1);
    printf("Reader %d has FINISHED READING\n", id);

    sem_wait(&mutex);

    read_count--;
    if (read_count == 0) {
        sem_post(&rw_mutex);  // Last reader allows writers
    }

    sem_post(&mutex);
    return NULL;
}

// Writer function
void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&queue);     // Writers get priority
    sem_wait(&rw_mutex);  // Exclusive access

    // Critical Section (Writing)
    printf("\tWriter %d is WRITING\n", id);
    sleep(2);
    printf("\tWriter %d has FINISHED WRITING\n", id);

    sem_post(&rw_mutex);
    sem_post(&queue);

    return NULL;
}

int main() {
    int n = 5;  // Number of readers and writers

    pthread_t readers[n], writers[n];
    int id[n];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    sem_init(&queue, 0, 1);

    // Create threads
    for (int i = 0; i < n; i++) {
        id[i] = i + 1;

        pthread_create(&readers[i], NULL, reader, &id[i]);
        pthread_create(&writers[i], NULL, writer, &id[i]);
    }

    // Join threads
    for (int i = 0; i < n; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    sem_destroy(&queue);

    return 0;
}