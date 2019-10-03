#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


/**
 * 
 * FIRST COMPILE AND RUN THE SERVER, AFTER THE CLIENT
 * 
 * 
 * compile  gcc client.c -o CLIENT
 * run ./ CLIENT
 *  
 * 
 */


int main() 
{

char request[256] = "Test Data";

// create the socket
int sock;
if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
{ 
    printf("\n Socket creation error \n"); 
    return -1; 
} 
   
// setup an address
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = INADDR_ANY;
server_address.sin_port = htons(8080);

if(connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
{
    printf("\n Socket connection error \n"); 
    return -1; 
}

send(sock, request, sizeof(request), 0);
printf("message sent..");
close(sock);

return 0;
}