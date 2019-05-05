#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{
	int cli_sock;
	struct sockaddr_in serv_add;
	char buff[1024], receive[1024];
	struct timeval start, end;

	// Creating the socket
	printf("Creating the socket\n");
	if((cli_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Socket error");
		exit(1);
	}

	// Setting server address
	printf("Setting server address\n");
	memset(&serv_add, 0, sizeof(serv_add));
	serv_add.sin_family = AF_INET;
    serv_add.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_add.sin_port = htons(8000);

    // Sending the connection request to server
	printf("Waiting for connection\n");
    if((connect(cli_sock, (struct sockaddr *)&serv_add, sizeof(serv_add))) < 0){
    	perror("Connection failed");
    	exit(1);
    }
    printf("Connection established\n\n");

    // Message sending and receiving
    while(1){
    	strcpy(buff, "");
    	// Getting the user response
    	printf("\nPlease enter the message to be sent to server: ");
    	fgets(buff, sizeof(buff), stdin);
    	
    	// Removong \n in the end to end of string 
	    int len = strlen(buff);
	    if (buff[len-1] == '\n') buff[len-1] = '\0';

	    // Getting time at which message is send 
	    gettimeofday(&start, NULL);

	    // Sending the message
	    write(cli_sock,buff, sizeof(buff));
	     
	    // Receiving message from server   
	    strcpy(receive, "");
	    printf("Receiving message from server\n");
	    read(cli_sock,receive,sizeof(receive));
	    
	    // Getting time at which message is received
	    gettimeofday(&end, NULL);

	    // Printing reply from server and time taken by servver to respond back
	    printf("Reply from Server: %s\n",receive);
	    printf("Time taken by server(in microseconds): %lu\n", end.tv_usec - start.tv_usec);
    }
    
    return 0;
}