// Write a multithreaded program that calculates various statistical values for a list of numbers. 
// This program will be passed a series of numbers on the command line and will then create three separate worker threads. 
// One thread will determine the average of the numbers, the second will determine the maximum value, 
// and the third will determine the median value. (Using Pthread library) also record time taken by each thread

#include <pthread.h>  // Import the pthread library for multithreading
#include <stdio.h>    // Import standard input and output functions
#include <stdlib.h>   // Import standard library functions
#include <string.h>   // Import string manipulation functions
#include <time.h>     // Import time functions

#define MAX_NUMBERS 100  // Define the maximum number of input values

// Define a struct for storing statistical information
struct stats {
    int* numbers;  // Pointer to the array of input numbers
    int count;     // Number of input numbers
    double average;  // Average of input numbers
    int maximum;  // Maximum of input numbers
    int median;   // Median of input numbers
};

// Function for computing the average of input numbers
void* compute_average(void* arg) {
    struct stats* data = (struct stats*)arg;  // Cast the argument to the struct
    double sum = 0.0;  // Initialize the sum of input numbers to zero
    clock_t start_time = clock();  // Record the starting time of the thread
    for (int i = 0; i < data->count; i++) {  // Iterate over input numbers
        sum += data->numbers[i];  // Add each number to the sum
    }
    data->average = sum / data->count;  // Compute the average
    clock_t end_time = clock();  // Record the ending time of the thread
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;  // Compute the elapsed time
    printf("Average computation took %f seconds.\n", elapsed_time);  // Print the elapsed time
    pthread_exit(NULL);  // Exit the thread
}

// Function for computing the maximum of input numbers
void* compute_maximum(void* arg) {
    struct stats* data = (struct stats*)arg;  // Cast the argument to the struct
    int maximum = data->numbers[0];  // Initialize the maximum to the first input number
    clock_t start_time = clock();  // Record the starting time of the thread
    for (int i = 1; i < data->count; i++) {  // Iterate over input numbers
        if (data->numbers[i] > maximum) {  // If the current number is greater than the maximum
            maximum = data->numbers[i];  // Set the maximum to the current number
        }
    }
    data->maximum = maximum;  // Set the maximum value in the struct
    clock_t end_time = clock();  // Record the ending time of the thread
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;  // Compute the elapsed time
    printf("Maximum computation took %f seconds.\n", elapsed_time);  // Print the elapsed time
    pthread_exit(NULL);  // Exit the thread
}


// @param arg a void pointer to a struct stats containing the array of integers, its length, and other stats
void compute_median(void *arg)
{
    // Cast the void pointer to a struct stats pointer
    struct stats *data = (struct stats *)arg;
    // Get the length of the array of integers
    int n = data->count;
    // Get the array of integers
    int *numbers = data->numbers;
    // Start measuring the time it takes to compute the median
    clock_t start_time = clock();
    // Iterate through the array of integers to find the median
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            // Count the number of integers that are less than the current integer
            if (numbers[j] < numbers[i])
            {
                count++;
            }
            // If two integers are equal, the one that appears earlier in the array is considered smaller
            else if (numbers[j] == numbers[i] && j < i)
            {
                count++;
            }
        }
        // If the number of integers that are less than or equal to the current integer is equal to half the length of the array (rounded up), it is the median
        if (count == (n + 1) / 2)
        {
            data->median = numbers[i];
            break;
        }
    }
    // Stop measuring the time it takes to compute the median
    clock_t end_time = clock();
    // Calculate the elapsed time
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    // Print the elapsed time
    printf("Median computation took %f seconds.\n", elapsed_time);
    // Exit the thread
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    // Check if the user entered the correct number of arguments.
    if (argc <= 1 || argc > MAX_NUMBERS + 1) {
        printf("Usage: %s <number1> <number2> ... <number%d>\n", argv[0], MAX_NUMBERS);
        return 1;
    }
    // Convert the command line arguments to integers.
    int count = argc - 1;
    int* numbers = malloc(count * sizeof(int));
    if (numbers == NULL) {
        printf("Error: Failed to allocate memory for numbers.\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i+1]);
    }
    // Create a struct to hold the data for the threads.
    struct stats data = { numbers, count, 0.0, 0, 0 };
    // Create the threads and start them.
    pthread_t threads[3];
    pthread_create(&threads[0], NULL, compute_average, (void*)&data);
    pthread_create(&threads[1], NULL, compute_maximum, (void*)&data);
    pthread_create(&threads[2], NULL, compute_median, (void*)&data);
    
    // Wait for the threads to finish.
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Average = %.2f\n", data.average);
    printf("Maximum = %d\n", data.maximum);
    printf("Median = %d\n", data.median);
    
    // Free the memory that was allocated.
    free(numbers);
    return 0;
}
