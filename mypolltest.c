#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>

int main()
{

    char name[100];
    struct pollfd mypoll;
    int counter = 0;
    /*mypoll init*/
    memset(&mypoll,0,sizeof(mypoll));

	mypoll.fd =0;
	mypoll.events = POLLIN;

	printf("what is you name?\n");
	while (1)
	{
        if(poll(&mypoll,1,100)) 
            {
                read(0, name, sizeof(name));
                printf("hello %s\n", name);
                break;
            }
        else
        counter ++;
        putc('.',stdout);
        fflush(stdout);
	}
     printf("\n");
    printf("it took you %d ms to type your name",100*counter);
	return 0;
}
