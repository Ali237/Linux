#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int turn = 0;
    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            // while (turn == 0)

            printf("First line \n");
            turn = 0;
        }
    }
    else
    {
        while (1)
        {
            // while (turn == 1)

            printf("second line \n");
            turn = 1;
        }
    }

    return 0;
}