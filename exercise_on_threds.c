#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 0;
void *runner(void *parm)
{
    value = 5;
    // pthread_exit(0);
}

int main()
{
    pid_t pid;
    pthread_t tid;
    pthread_attr_t attr;

    pid = fork();

    if (pid == 0)
    {
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);
        pthread_join(tid,NULL);
        printf("Child value %d\n", value);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("parent value: %d\n", value);
    }
    return 0;
}