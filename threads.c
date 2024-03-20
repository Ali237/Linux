#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// function decleration
void *myturn(void *arg);
void *yourturn();

void *myturn(void *arg)
{
    for (int i = 0; i < 8; i++)
    {
        printf("my turn\n");
        sleep(1);
    }
    return NULL;
}
void *yourturn()
{
    for (int i = 0; i < 3; i++)
    {
        printf("your turn\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t mythread; // helps us keep track of the thread ww will create
    pthread_create(&mythread, NULL, myturn, NULL);
    // function that creats threads you pass a function pointer
    // thread functions they have to look a certain why they have to return a void prt
    // and take a void prt as an argument
    yourturn();
    // we need to wait for the thread in case the main finsh befor my thread
    pthread_join(mythread, NULL);
    return 0;
}
