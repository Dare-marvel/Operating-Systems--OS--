## Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cscan(int initial_head, int requests[], int num_requests, int lower, int higher, int *sequence)
{
    // make a copy of the requests array so we can modify it without affecting the original
    int *reqs = malloc(num_requests * sizeof(int));
    for (int i = 0; i < num_requests; i++)
    {
        reqs[i] = requests[i];
    }

    // sort the requests in ascending order
    for (int i = 0; i < num_requests - 1; i++)
    {
        for (int j = 0; j < num_requests - i - 1; j++)
        {
            if (reqs[j] > reqs[j + 1])
            {
                int temp = reqs[j];
                reqs[j] = reqs[j + 1];
                reqs[j + 1] = temp;
            }
        }
    }

    // find the index of the first request larger than the initial head position
    int next_req = 0;
    while (next_req < num_requests && reqs[next_req] < initial_head)
    {
        next_req++;
    }

    // initialize variables for tracking movement and seek time
    int movement = 0;
    int seek_time = 0;

    // move the head to the first request larger than the initial head position
    if (next_req < num_requests)
    {
        movement += abs(reqs[next_req] - initial_head);
        seek_time += movement;
        initial_head = reqs[next_req];
        sequence[0] = initial_head;
        next_req++;
    }
    else
    {
        movement += higher - initial_head;
        seek_time += movement;
        initial_head = higher;
        sequence[0] = initial_head;
        next_req = 0;
    }

    // scan from the initial head position to the highest request
    int i = 1;
    while (initial_head < higher)
    {
        if (next_req < num_requests && reqs[next_req] <= higher)
        {
            movement += abs(reqs[next_req] - initial_head);
            seek_time += movement;
            initial_head = reqs[next_req];
            sequence[i] = initial_head;
            i++;
            next_req++;
        }
        else
        {
            movement += higher - initial_head;
            seek_time += movement;
            initial_head = higher;
            sequence[i] = initial_head;
            i++;
            next_req = 0;
        }
    }

    // scan from the lowest request to the initial head position
    while (initial_head > lower)
    {
        if (next_req < num_requests && reqs[next_req] >= lower)
        {
            movement += abs(reqs[next_req] - initial_head);
            seek_time += movement;
            initial_head = reqs[next_req];
            sequence[i] = initial_head;
            i++;
            next_req++;
        }
        else
        {
            movement += initial_head - lower;
            seek_time += movement;
            initial_head = lower;
            sequence[i] = initial_head;
            break;
        }
    }

    // calculate and return the total seek time
    return seek_time;
}

int main()
{
    int max_requests = 200;
    int num_requests;
    printf("Enter the number of requests: ");
    scanf("%d", &num_requests);
    if (num_requests > max_requests)
    {
        printf("Error: too many requests.\n");
        return 1;
    }

    int *requests = malloc(num_requests * sizeof(int));
    printf("Enter the requests:\n");
    for (int i = 0; i < num_requests; i++)
    {
        scanf("%d", &requests[i]);
    }

    int initial_head;
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    int lower, higher;
    printf("Enter the lower bound and higher bound of the cylinder: ");
    scanf("%d %d", &lower, &higher);

    int *sequence = malloc((num_requests + 1) * sizeof(int));
    int seek_time = cscan(initial_head, requests, num_requests, lower, higher, sequence);

    printf("The sequence of head movement is:\n");
    for (int i = 0; i <= num_requests; i++)
    {
        printf("%d ", sequence[i]);
        if (i != num_requests)
        {
            printf("=> ");
        }
    }
    printf("\n");

    printf("The total seek time is %d\n", seek_time);

    free(requests);
    free(sequence);

    return 0;
}
```
