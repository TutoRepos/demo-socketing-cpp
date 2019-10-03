#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> //avoid implicit declaration of function ‘read’


/**
 * 
 * FIRST COMPILE AND RUN THE SERVER, AFTER THE CLIENT
 * 
 * 
 * compile gcc server.c -o SERVER
 * run ./ SERVER
 * server will keep listening at defined port
 * 
 * 
 */



int main() 
{
char server_message[256] = "You have reached the server!";
char buffer[256] = {0};

// create the server socket file descriptor
int server_socket;
if ((server_socket = socket(AF_INET, SOCK_STREAM, 0))== 0)
{
    perror("socket failed");
    exit(EXIT_FAILURE);
}

// define the server address
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(8080);
server_address.sin_addr.s_addr = INADDR_ANY;

// bind the socket to our specified IP and port
if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0)
{
    perror("error bind");
    exit(EXIT_FAILURE);
}

// listen method takes two args 
// first arg is the socket to listen on, the second is max umber of connections
if (listen(server_socket, 5) < 0)
{
    perror("eror listen");
    exit(EXIT_FAILURE);
}

//accept method waits for a connection and wakes up when one is estabilished
int client_socket;
int addrlen = sizeof(server_address); 
if((client_socket = accept(server_socket, (struct sockaddr*) &server_address, (socklen_t*)&addrlen)) < 0)
{
    perror("error accept");
    exit(EXIT_FAILURE);
}
int valread = read( client_socket , buffer, 1024); 
printf("COOL, I GOT YOUR DATA, YOU SENT ME:\n%s\n", buffer);
send(client_socket, server_message, sizeof(server_message), 0);
close(server_socket);

return 0;
}