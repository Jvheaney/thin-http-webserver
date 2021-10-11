#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 4080
#define SERVER_ADDRESS "127.0.0.1"
int main(int argc, char const *argv[])
{
    int client_fd;
    struct sockaddr_in address;

    //Similar to the server, we create are creating a socket based on AF_INET, SOCK_STREAM, and protocol 0.
    //This creates a socket that accepted IPv4 TCP.
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Failed to create socket.");
        return 0;
    }
    
    memset(&address, '\0', sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    int addrlen = sizeof(address);

    long message_read;
    char *greeting = "Salutations, server!";
    char buffer[1024] = {0};
    
    //Here we convert our IP address from a string to binary. 
    if(inet_pton(AF_INET, SERVER_ADDRESS, &address.sin_addr)<=0)
    {
        printf("Address failed to convert to binary.");
        return 0;
    }
    
    //Here we attempt to establish a connection to the server
    if (connect(client_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        printf("Failed to connect to server.");
        return 0;
    }

    //We have connected, lets send a message and see what we get.
    send(client_fd, greeting, strlen(greeting), 0);
    printf("We sent our greeting.\n");
    message_read = read(client_fd, buffer, 1024);
    printf("Message from server: %s\n",buffer);
    return 0;
}