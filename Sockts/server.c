/*
# ------------------------------------------------------------
# server.c - a simple concurrent server using AF_STREAM sockets
#     Compilation:
#     	Linux 		        gcc server.c -o server
#
#     Usage:		server
#     Features:		- use of setrlimit() to limit the CPU time
#			  note: time spent while sleeping, or waiting
#			        for input is not user CPU time
#			- use of I/O multiplexing to read from the
#			  managing socket, as well as data sockets
#
# [U. of Alberta, CMPUT379, E.S. Elmallah]
# ------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>     /* required by setrlimit() */
#include <sys/resource.h> /* required by setrlimit() */

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>

#define MAXBUF 80
#define CPU_LIMIT 120 /* secs */
#define CLIENT_LIMIT 5
#define MYPORT 2222

int main(int argc, char **argv)
{

    int i, N, len, port, rval, timeout, s, fromlen;
    int newsock[CLIENT_LIMIT + 1];
    char buf[MAXBUF];
    struct rlimit cpuLimit;
    struct pollfd pfd[CLIENT_LIMIT + 1];
    struct sockaddr_in sin, from;
    FILE *sfp[CLIENT_LIMIT + 1];

    /* set a cpu limit */

    cpuLimit.rlim_cur = cpuLimit.rlim_max = CPU_LIMIT;

    if (setrlimit(RLIMIT_CPU, &cpuLimit) < 0)
    {
        fprintf(stderr, "%s: setrlimit \n", argv[0]);
        exit(1);
    }
    getrlimit(RLIMIT_CPU, &cpuLimit);
    printf("cpuLimit: current (soft)= %lu, maximum (hard)= %lu \n",
           cpuLimit.rlim_cur, cpuLimit.rlim_max);

    /* create a managing socket */

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        fprintf(stderr, "%s: socket \n", argv[0]);
        exit(1);
    }

    /* bind the managing socket to a name */

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(MYPORT);

    if (bind(s, (struct sockaddr *)&sin, sizeof sin) < 0)
    {
        fprintf(stderr, "%s: bind \n", argv[0]);
        exit(1);
    }

    /* indicate how many connection requests can be queued */

    listen(s, 5);

    /* prepare for nonblocking I/O polling from the master socket  */

    timeout = 0;
    pfd[0].fd = s;
    pfd[0].events = POLLIN;
    pfd[0].revents = 0;

    N = 1; /* N descriptors to poll */
    while (1)
    {
        rval = poll(pfd, N, timeout);

        /* check master socket */
        if ((N < CLIENT_LIMIT) && (pfd[0].revents & POLLIN))
        {

            /* accept a new connection */

            fromlen = sizeof(from);
            newsock[N] = accept(s, (struct sockaddr *)&from, &fromlen);

            /* we may also want to perform STREAM I/O */

            if ((sfp[N] = fdopen(newsock[N], "r")) < 0)
            {
                fprintf(stderr, "%s: fdopen \n", argv[0]);
                exit(1);
            }

            pfd[N].fd = newsock[N];
            pfd[N].events = POLLIN;
            pfd[N].revents = 0;
            N++;
        }

        for (i = 1; i < N; i++)
        {
            if (pfd[i].revents & POLLIN)
            { /* check data socket */
                if (fgets(buf, MAXBUF, sfp[i]) != NULL)
                    printf("%s", buf);
            }
        }
    }

    close(s);
    for (i = 1; i < N; i++)
        close(newsock[i]);
    printf("\n");
    return 0;
}