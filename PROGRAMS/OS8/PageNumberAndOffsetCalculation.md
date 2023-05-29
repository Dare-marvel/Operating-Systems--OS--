## Problem:
Write a C program to calculate the Page Number and Page Offset with given virtual address

## Code:
```c
#include <stdio.h>
#include <math.h>

int main()
{
    printf("Page size is in:\n# Enter 1 for KB\n# Enter 2 for MB\n# Enter 3 for GB\n");
    int choice;
    scanf("%d", &choice);
    printf("Enter the magnitude of page size: ");
    int page_size;
    scanf("%d", &page_size);
    printf("Enter the virtual address: ");
    int virtual_address;
    scanf("%d", &virtual_address);

    int count = 0, temp = page_size;
    while (temp != 1)
    {
        temp /= 2;
        count++;
    }
    printf("\nPage size power of 2: %d\n", count);

    if (choice == 1)
    {
        page_size = 10;
    }
    else if (choice == 2)
    {
        page_size = 20;
    }
    else if (choice == 3)
    {
        page_size = 30;
    }
    page_size += count;
    printf("\nPage size in bits: %d\n", page_size);

    int binary_address[32];
    for (int i = 0; i < 32; i++)
    {
        binary_address[i] = 0;
    }

    for (int i = 0; i < 32; i++)
    {
        binary_address[i] = virtual_address % 2;
        virtual_address /= 2;
    }

    double offset = 0;
    for (int i = 0; i < page_size; i++)
    {
        offset += ((pow(2, i)) * binary_address[i]);
    }

    double page_number = 0;
    int j = 0;
    for (int i = page_size; i < 32; i++)
    {
        page_number += ((pow(2, j)) * binary_address[i]);
        j++;
    }

    printf("The offset is: %.lf\n", offset);
    printf("The page number is: %.lf", page_number);

    return 0;
}

```
