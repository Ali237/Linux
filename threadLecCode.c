// #define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void *athread(void *arg)
{
    int i;
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("Process ID: %d, thread ID: %u, arg: %s\n", (int)pid, (unsigned int)pthread_self(), (char *)arg);
}
int main(int argc, char *argv[])
{
    int i, rval;
    pthread_t ntid;
    for (i = 0; i < argc; ++i)
    {
        rval = pthread_create(&ntid, NULL, athread, (void *)argv[i]);
        if (rval)
        {
            fprintf(stderr, "thr_create: %s\n", strerror(rval));
            exit(1);
        }
    }
    pthread_exit(0);
}