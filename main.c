#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 4080
int main(int argc, char const *argv[]) {
    
    int server_fd;

    //We are creating a socket based on AF_INET address family (IPv4), SOCK_STREAM (used by TCP), and 0 as our protocol variation
    //socket(address_family, type, protocol)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed.");
        return 0;
    }

    /* Creating our data for binding to our socket */
    struct sockaddr_in address;
    memset((char *)&address, '\0', sizeof(address));

    address.sin_family = AF_INET; //Setting our address family
    address.sin_addr.s_addr = htonl(INADDR_ANY); //Letting the machine tell us our IP (basically 0.0.0.0)
    address.sin_port = htons(PORT); //Declaring our port

    int addrlen = sizeof(address);

    //Binding our address to our socket
    //We declare our socket from above, use our sockaddr_in struct, and the sockaddr_in struct length to bind
    //bind(socket, sockaddr struct, address length socklen_t)
    if (bind(server_fd, (struct sockaddr *) &address, addrlen) < 0) { 
        perror("Failed to bind to socket."); 
        return 0; 
    }

    //Start listening on our socket
    if (listen(server_fd, 3) < 0)
    {
        perror("Failed to listen.");
        return 0;
    }

    int accepted_socket;
    long message_read;
    char *greeting = "Hello world!";

    //Now we will wait for connections and accept them as they come
    while(1)
    {
        printf("Waiting for connection...\n");
        //We check for connections and accept them
        //accept(socket, address struct, address length)
        if ((accepted_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
        {
            perror("Failed to accept.");
            return 0;
        }
        else{
            char buffer[30000] = {0};
            message_read = read(accepted_socket, buffer, 30000);
            printf("We got a message: %s\n", buffer);
            write(accepted_socket, greeting, strlen(greeting));
            printf("Sent our greeting! Now lets close the connection.\n");
            close(accepted_socket);
        }
    }
    return 0;
}