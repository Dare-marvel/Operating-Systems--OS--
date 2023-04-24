## Code:
```c
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>

int main()
{
    FILE *fp; // declare a file pointer variable named fp
    fp = fopen("/home/spit/Desktop/Adwait/trial.txt", "rw+"); // open a file named trial.txt in read-write mode and assign the file stream to fp
    int fd = fileno(fp); // get the file descriptor of the file associated with fp
    flock(fd, LOCK_SH); // obtain a shared lock on the file using the file descriptor fd
    char c; // declare a character variable named c
    while (1) // enter an infinite loop
    {
        c = fgetc(fp); // read the next character from the file stream and assign it to c
        if (feof(fp)) // if the end of the file has been reached
        {
            break; // break out of the loop
        }
        printf("%c\n", c); // print the character to the console followed by a newline character
        sleep(1); // pause the program for 1 second
    }
    fclose(fp); // close the file stream associated with fp

    return 0; 
}

```
