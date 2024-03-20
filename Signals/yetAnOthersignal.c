#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        return 1;
    }
    if (pid == 0)
    {
        while (1)
        {
            printf("I am here \n");
            usleep(50000);
        }
    }
    else
    {
        sleep(2);
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}