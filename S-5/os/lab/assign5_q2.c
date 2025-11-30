#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 1000

int arr[MAX_SIZE];
int temp[MAX_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start;
    int end;
} ThreadData;

// Error handling function
void handle_error(int ret, const char* msg) {
    if (ret != 0) {
        fprintf(stderr, "%s: %s\n", msg, strerror(ret));
        exit(EXIT_FAILURE);
    }
}

// Merge function with thread safety
void merge(int start, int mid, int end) {
    int i = start, j = mid + 1, k = start;

    pthread_mutex_lock(&mutex); // Lock the critical section
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= end) {
        temp[k++] = arr[j++];
    }
    for (i = start; i <= end; i++) {
        arr[i] = temp[i];
    }
    pthread_mutex_unlock(&mutex); // Unlock the critical section
}

// Merge sort function with multi-threading
void* merge_sort(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int start = data->start;
    int end = data->end;

    if (start < end) {
        int mid = (start + end) / 2;
        printf("Sorting indices %d to %d\n", start, end);

        // Create two sub-threads for sorting the two halves
        pthread_t left_thread, right_thread;
        ThreadData left_data = {start, mid};
        ThreadData right_data = {mid + 1, end};

        handle_error(pthread_create(&left_thread, NULL, merge_sort, &left_data), "Left thread creation failed");
        handle_error(pthread_create(&right_thread, NULL, merge_sort, &right_data), "Right thread creation failed");

        handle_error(pthread_join(left_thread, NULL), "Left thread join failed");
        handle_error(pthread_join(right_thread, NULL), "Right thread join failed");

        // Merge the sorted halves
        merge(start, mid, end);
    }
    return NULL;
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        fprintf(stderr, "Invalid array size. Please enter a number between 1 and %d.\n", MAX_SIZE);
        return EXIT_FAILURE;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Create the main thread data
    ThreadData main_data = {0, n - 1};

    // Create the main thread to start the merge sort
    pthread_t main_thread;
    handle_error(pthread_create(&main_thread, NULL, merge_sort, &main_data), "Main thread creation failed");

    // Wait for the main thread to complete
    handle_error(pthread_join(main_thread, NULL), "Main thread join failed");

    // Output the sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}