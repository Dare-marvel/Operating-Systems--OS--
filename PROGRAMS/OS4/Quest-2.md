### Question - 2
Write a program that creates a single thread that generates random numbers between 1 and 100. The
thread should run for a specified number of iterations, printing each generated number to the screen.
After the specified number of iterations, the thread should stop and the main program should print the
sum of all the generated numbers.Also record and display time taken by each thread

### Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_ITERATIONS 10

void* generate_random_numbers(void* arg);

int main() {
    pthread_t thread;
    srand(time(NULL));
    int sum = 0;
    clock_t start_time, end_time;
    start_time = clock();
    pthread_create(&thread, NULL, generate_random_numbers, (void*)&sum);
    pthread_join(thread, NULL);
    end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Total sum: %d\n", sum);
    printf("Time taken: %f seconds\n", time_taken);
    return 0;
}

void* generate_random_numbers(void* arg) {
    int* sum = (int*)arg;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int rand_num = rand() % 100 + 1;
        printf("Random number %d: %d\n", i+1, rand_num);
        *sum += rand_num;
    }
    pthread_exit(NULL);
}
```
