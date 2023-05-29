## Problem:
Write a C program to implement Banker's Algorithm and print the safe sequence

## Code:
```c
#include <stdio.h>

void main()
{
    int k = 0, a = 0, b = 0;
    int no_of_resources, process;
    // Initialize variables
    printf("Enter the number of customers : ");
    scanf("%d", &process);
    printf("Enter the number of resources : ");
    scanf("%d", &no_of_resources);
    int instance[no_of_resources];
    int availability[no_of_resources];
    int allocated[process][no_of_resources];
    int need[process][no_of_resources];
    int MAX[process][no_of_resources];
    int P[process];
    int cnt = 0, i, j;
    int op[100];
    // Input the max number of instances for each resource
    for (i = 0; i < no_of_resources; i++)
    {
        availability[i] = 0;
        printf("Enter the max instances of resource %d : ", i);
        scanf("%d", &instance[i]);
    }
    printf("\nEnter the Allocation matrix \n");
    // Input the allocation matrix
    for (i = 0; i < process; i++)
    {
        P[i] = i;
        printf("Enter the allocation of customer %d : ", i);
        for (j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &allocated[i][j]);
            availability[j] += allocated[i][j];
        }
    }
    printf("\nEnter the Max Need matrix \n");
    // Input the maximum need matrix
    for (i = 0; i < no_of_resources; i++)
    {
        availability[i] = instance[i] - availability[i];
    }
    printf("\n");
    for (i = 0; i < process; i++)
    {
        printf("Enter the max need of customer %d : ", i);
        for (j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &MAX[i][j]);
        }
    }
    printf("\n");
// Check if granting the request for the resources will lead to a safe state or not
A:
    a = -1;
    for (i = 0; i < process; i++)
    {
        cnt = 0;
        b = P[i];
        for (j = 0; j < no_of_resources; j++)
        {
            need[b][j] = MAX[b][j] - allocated[b][j];
            if (need[b][j] <= availability[j])
                cnt++;
        }
        if (cnt == no_of_resources)
        {
            op[k++] = P[i];
            for (j = 0; j < no_of_resources; j++)
                availability[j] += allocated[b][j];
        }
        else
            P[++a] = P[i];
    }
    if (a != -1)
    {
        process = a + 1;
        goto A;
    }
    // If it does, grant the request and print the safe sequence
    printf("The safe sequence is : \n");
    printf("<");
    for (i = 0; i < k; i++)
        printf(" P[%d] ", op[i]);
    printf(">\n");
    printf("Thus request is granted\n");
}
```
