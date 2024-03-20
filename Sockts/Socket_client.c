// sockets a way to compunicate between two computers
// networking protoclos set on top TCP UDP low level
// server clients
//

#include <stdio.h>  // standard I/O
#include <stdlib.h> // standard libray
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main()
{
    // create a network socket

    /*This part is the client side */
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0); // IP v 4 , type of socket

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);       // convert the poort to the value taht out strct understands
    server_address.sin_addr.s_addr = INADDR_ANY; // multiple strcutures our local host

    if (connect(sock_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        printf("erro with connecting!");
    }
    // send or recive data
    char server_buff[256];
    recv(sock_fd, &server_buff, sizeof(server_buff), 0); // last prameter is optional flag

    // Print out the data we got from the server
    printf("the server send the data: %s\n", server_buff);

    // and then close the socket
    close(sock_fd);

    return 0;
}
