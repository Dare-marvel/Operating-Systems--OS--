// Problem: 
// With the increasing number of devotees visiting the temple, the wait time for "Dev Darshan" has become longer, causing inconvenience to the devotees. This has resulted in a need for a more efficient system that can manage the waiting queue and reduce the wait time for "Dev Darshan".

// Goal: 
// To design and implement a CPU scheduling algorithm for the "Dev Darshan" system in the temple that can effectively manage the waiting queue, minimize the wait time for devotees, and improve the overall experience of visiting the temple.

// Scope: 
// The CPU scheduling algorithm will be implemented in the existing "Dev Darshan" system, and will consider the following factors:
// The number of devotees waiting in the queue.
// The priority of each devotee, such as senior citizens, children, and differently-abled individuals.
// The time taken by each devotee to complete "Dev Darshan".
// The availability of resources, such as the number of "Dev Darshan" counters and the capacity of the temple.
// The solution will be tested and evaluated based on its ability to reduce the wait time for devotees, improve the utilization of resources, and ensure fairness and equality in the allocation of resources.
// Give the solution with example of Dev darshan using CPU scheduling algorithm 

#include <stdio.h>
#include <stdlib.h>

//Function to swap two values
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Function to sort People according to their time taken for completion of puja
void SelectionSort(int arr[100][5], int n)
{
    int most_app, i, j;
    for (i = 0; i < n - 1; i++)
    {
        most_app = i;
        for (j = i + 1; j < n; j++)
        {
            //Checks the burst time first
            if (arr[j][1] < arr[most_app][1])
            {
                most_app = j;
            }

            //If time taken for puja(burst times) are equal , checks the priority(e.g. Differently-abled etc.)
            //Higher the number higher is the priority
            else if (arr[j][1] == arr[most_app][1])
            {
                if (arr[j][4] > arr[most_app][4])
                {
                    most_app = j;
                }
            }
        }
        //Swaps The Person id , priority and the time taken for puja(burst times)
        if (most_app != i)
        {
            swap(&arr[i][1], &arr[most_app][1]);
            swap(&arr[i][4], &arr[most_app][4]);
            swap(&arr[i][0], &arr[most_app][0]);
        }
    }
}

// Waiting Time = Turn Around Time(Time at which person leaves) – Burst Time(Time taken for puja)
int WaitingTimeCalculation(int arr[100][5], int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        arr[i][2] = 0;
        for (int j = 0; j < i; j++)
        {
            arr[i][2] += arr[j][1];
        }
        total += arr[i][2];
    }
    return total;
}

int main()
{

    int arr[100][5], n, total = 0;
    printf("Enter the number of processes: \n");
    scanf("%d", &n);

    printf("Enter the priority according to this scheme\n1 - Normal People\n2 - Children\n3 - Senior Citizens\n4 - Specially Abled\n");

    printf("Enter the burst time and priority of each process \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i][1], &arr[i][4]);
        arr[i][0] = i + 1; // Allocating ID's to people
    }

    SelectionSort(arr, n);
    total = WaitingTimeCalculation(arr, n);
    printf("Total Waiting time:%d\n", total);

    float avg_wt = (float)total / n;

    int tot_tat = 0;
    //Printing the 
    printf("PID\tBT\tWT\tTAT\tPriority\n");
    for (int i = 0; i < n; i++)
    {
        arr[i][3] = arr[i][1] + arr[i][2];
        tot_tat += arr[i][3];
        printf("%d\t%2d\t%2d\t%2d\t%2d\n", arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
    }

    float avg_tat = (float)tot_tat / n;
    printf("Average Waiting Time= %f", avg_wt);
    printf("\nAverage Turnaround Time= %f\n", avg_tat);

    //Here as we have considered that all processes arrive at the same time , so Turn around time is same as completion time

    // Gannt Chart

    printf(" -------------------------------------------------------------------------------\n");
    printf("|\t");
    for (int i = 0; i < n; i++)
    {
        //Printing the ID's of people
        printf("P%d\t|\t", arr[i][0]);
    }
    printf("\n");
    printf(" -------------------------------------------------------------------------------\n");
    printf("0\t\t");
    //Printing the completion times
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t", arr[i][3]);
    }
    printf("\n\n");

    return 0;
}
