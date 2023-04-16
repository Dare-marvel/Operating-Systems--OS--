## Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sstf(int initial_head, int requests[], int num_requests, int lower, int higher, int sequence[])
{
    // make a copy of the requests array so we can modify it without affecting the original
    int *reqs = malloc(num_requests * sizeof(int));
    for (int i = 0; i < num_requests; i++)
    {
        reqs[i] = requests[i];
    }

    // initialize variables for tracking movement and seek time
    int movement = 0;
    int seek_time = 0;

    // loop until all requests have been processed
    int index = 0;
    while (num_requests > 0)
    {
        // find the request with the shortest seek time from the current head position
        int shortest_seek_time = INT_MAX;
        int next_req;
        for (int i = 0; i < num_requests; i++)
        {
            int seek = abs(reqs[i] - initial_head);
            if (seek < shortest_seek_time)
            {
                shortest_seek_time = seek;
                next_req = i;
            }
        }

        // update variables for tracking movement and seek time
        movement += abs(reqs[next_req] - initial_head);
        seek_time += shortest_seek_time;
        sequence[index++] = reqs[next_req];

        // move the head to the next request and remove it from the array
        initial_head = reqs[next_req];
        for (int i = next_req; i < num_requests - 1; i++)
        {
            reqs[i] = reqs[i + 1];
        }
        num_requests--;
    }

    // calculate and return the total seek time
    int total_seek_time = seek_time + (higher - lower);
    return total_seek_time;
}

int main()
{
    int max_requests = 200;
    int num_requests;
    printf("Enter the number of requests: ");
    scanf("%d", &num_requests);
    if (num_requests > max_requests)
    {
        num_requests = max_requests;
    }
    printf("Enter %d requests:\n", num_requests);
    int requests[max_requests];
    for (int i = 0; i < num_requests; i++)
    {
        scanf("%d", &requests[i]);
    }

    int initial_head, lower, higher;
    printf("Enter the initial R/W head position: ");
    scanf("%d", &initial_head);
    printf("Enter the lower bound: ");
    scanf("%d", &lower);
    printf("Enter the higher bound: ");
    scanf("%d", &higher);

    int sequence[num_requests];
    int total_seek_time = sstf(initial_head, requests, num_requests, lower, higher, sequence);
    int movement = total_seek_time - (higher - lower);
    float avg_seek_time = (float)total_seek_time / num_requests;

    printf("Total movement of R/W head: %d\n", movement);
    printf("Total seek time: %d\n", total_seek_time);
    printf("Average seek time: %f\n", avg_seek_time);
    printf("Sequence of requests: ");
    for (int i = 0; i < num_requests; i++)
    {
        printf("%d ", sequence[i]);
        if(i != num_requests-1){
            printf("=> ");
        }
    }
    printf("\n");

    return 0;
}

```
