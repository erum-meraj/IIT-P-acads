#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 10

// Shared buffer and synchronization variables
int buffer[BUFFER_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

int is_generated = 0;
int is_sorted = 0;

// Error handling function
void handle_error(int ret, const char* msg) {
    if (ret != 0) {
        fprintf(stderr, "%s: %s\n", msg, strerror(ret));
        exit(EXIT_FAILURE);
    }
}

// Thread 1: Generates a list of random integers
void* generate_numbers(void* arg) {
    srand(time(NULL));
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = rand() % 100;  // Generate random integers between 0 and 99
    }
    is_generated = 1;
    printf("Generated numbers: ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    pthread_cond_signal(&cond1); // Notify Thread 2
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Thread 2: Sorts the integers in the shared buffer
void* sort_numbers(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!is_generated) {
        pthread_cond_wait(&cond1, &mutex); // Wait until numbers are generated
    }

    // Sorting using bubble sort
    for (int i = 0; i < BUFFER_SIZE - 1; i++) {
        for (int j = 0; j < BUFFER_SIZE - 1 - i; j++) {
            if (buffer[j] > buffer[j + 1]) {
                int temp = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = temp;
            }
        }
    }
    is_sorted = 1;
    printf("Sorted numbers: ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    pthread_cond_signal(&cond2); // Notify Thread 3
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Thread 3: Calculates the sum and average of the integers in the sorted buffer
void* calculate_sum_and_average(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!is_sorted) {
        pthread_cond_wait(&cond2, &mutex); // Wait until numbers are sorted
    }

    int sum = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        sum += buffer[i];
    }
    double average = sum / (double)BUFFER_SIZE;

    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", average);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    // Creating threads
    handle_error(pthread_create(&thread1, NULL, generate_numbers, NULL), "Thread 1 creation failed");
    handle_error(pthread_create(&thread2, NULL, sort_numbers, NULL), "Thread 2 creation failed");
    handle_error(pthread_create(&thread3, NULL, calculate_sum_and_average, NULL), "Thread 3 creation failed");

    // Joining threads
    handle_error(pthread_join(thread1, NULL), "Thread 1 join failed");
    handle_error(pthread_join(thread2, NULL), "Thread 2 join failed");
    handle_error(pthread_join(thread3, NULL), "Thread 3 join failed");

    // Destroying mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);

    return 0;
}