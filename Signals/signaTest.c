#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(int code)
{
    write(STDOUT_FILENO, "I won't die!\n", 13);
}
int main()
{
    while (1)
    {
        signal(SIGINT, handler);
        write(STDOUT_FILENO, "13", 12);
        printf("Wasting you cycles. %d\n", getpid());
        sleep(1);
    }
    return 0;
}