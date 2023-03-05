// Write a multithreaded program that calculates various statistical values for a list of numbers. 
// This program will be passed a series of numbers on the command line and will then create three separate worker threads. 
// One thread will determine the average of the numbers, the second will determine the maximum value, 
// and the third will determine the median value. (Using Pthread library) also record time taken by each thread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUMBERS 100

struct stats {
    int* numbers;
    int count;
    double average;
    int maximum;
    int median;
};

void* compute_average(void* arg) {
    struct stats* data = (struct stats*)arg;
    double sum = 0.0;
    clock_t start_time = clock();
    for (int i = 0; i < data->count; i++) {
        sum += data->numbers[i];
    }
    data->average = sum / data->count;
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Average computation took %f seconds.\n", elapsed_time);
    pthread_exit(NULL);
}

void* compute_maximum(void* arg) {
    struct stats* data = (struct stats*)arg;
    int maximum = data->numbers[0];
    clock_t start_time = clock();
    for (int i = 1; i < data->count; i++) {
        if (data->numbers[i] > maximum) {
            maximum = data->numbers[i];
        }
    }
    data->maximum = maximum;
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Maximum computation took %f seconds.\n", elapsed_time);
    pthread_exit(NULL);
}

void* compute_median(void* arg) {
    struct stats* data = (struct stats*)arg;
    int n = data->count;
    int* numbers = data->numbers;
    clock_t start_time = clock();
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (numbers[j] < numbers[i]) {
                count++;
            } else if (numbers[j] == numbers[i] && j < i) {
                count++;
            }
        }
        if (count == (n + 1) / 2) {
            data->median = numbers[i];
            break;
        }
    }
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Median computation took %f seconds.\n", elapsed_time);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc <= 1 || argc > MAX_NUMBERS + 1) {
        printf("Usage: %s <number1> <number2> ... <number%d>\n", argv[0], MAX_NUMBERS);
        return 1;
    }
    int count = argc - 1;
    int* numbers = malloc(count * sizeof(int));
    if (numbers == NULL) {
        printf("Error: Failed to allocate memory for numbers.\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i+1]);
    }
    struct stats data = { numbers, count, 0.0, 0, 0 };
    pthread_t threads[3];
    pthread_create(&threads[0], NULL, compute_average, (void*)&data);
    pthread_create(&threads[1], NULL, compute_maximum, (void*)&data);
    pthread_create(&threads[2], NULL, compute_median, (void*)&data);
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Average = %.2f\n", data.average);
    printf("Maximum = %d\n", data.maximum);
    printf("Median = %d\n", data.median);
    free(numbers);
    return 0;
}
