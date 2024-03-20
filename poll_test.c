#include<stdio.h>
#include<poll.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int counter =0;
	struct pollfd mypoll;

	memset(&mypoll,0, sizeof(mypoll));
	mypoll.fd =0;
	mypoll.events =POLLIN ;
	poll(mypoll,,counter) ;
	char name[100];
	

	while(1)
	{
	printf("what is you name?\n");

	read(0,name,sizeof(name));
	printf("hello %s",name);
	}
	return 0;



}

