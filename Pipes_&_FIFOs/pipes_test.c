#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h> /* POSIX.2 Symbolic Constants */

int main()
{
    int fd[2];
    // fd[0] read form 
    // fd[1] write to 
    if (pipe(fd) == -1)
    {
        printf("erro with opening pipe");
    }

    int pid = fork();

    if (pid == 0)
    {
        close(fd[0]);
        int x;
        printf("Input your number: ");
        scanf("%d", &x);
        write(fd[1], &x,sizeof(int));
        close(fd[1]);
    }
    else 
    {
        close(fd[1]);   // close one of the end that is not used starndard poprceduger 
        int y;
        wait(NULL);
        read(fd[0],&y,sizeof(int)); // & pas the address 
        y*=-5;
        printf("value of x passed to parent: %d\n",y);
        close(fd[0]);
    }

    return 0;
}
