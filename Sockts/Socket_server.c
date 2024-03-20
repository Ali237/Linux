#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main()
{
    char server_message[256] = "You have reached the server";

    // create the server sockt
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // internet sock and we are using sock stream

    // define server address
    struct sockaddr_in serveradd;

    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(9002);
    serveradd.sin_addr.s_addr = INADDR_ANY;

    // bind to ip
    bind(server_fd, (struct sockaddr *)&serveradd, sizeof(serveradd));

    listen(server_fd, 5); // the 5 does not really matter in this case

    int client_sockt = accept(server_fd, NULL, NULL); // The NULL would be struct that would save data from client where client is connecting and so on
                                                      //
    send(client_sockt, server_message, sizeof(server_message), 0);

    close(server_fd);
    return 0;
}