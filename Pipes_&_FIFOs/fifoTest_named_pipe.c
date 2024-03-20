#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[])
{

   // create fifo on the current dir with pirmision 
	if (mkfifo("myfifo1",0777) == -1)
	{
	if(errno != EEXIST){                             // if the fifo alrady exist we are fine with that acn keep going 
							// only if there is 
	perror("fifo could not created\n");
	}
	return 1;
	}

 	printf("Opening  ...\n");
	int fd =open("myfifo1", O_RDWR);
	int x = 'Z';
	
 	printf("Opened ...\n");
	write(fd,&x,sizeof(x));

	printf("writen  ...\n");
	close(fd);   
	return 0;
}
