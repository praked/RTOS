/*
** msgQ_server.c -------
** multiple users would like to run this this application  through a client. 
** Design a client and server model to implement this app.
** server of the App. This server performs Arithmetic operation.
** client name and answer is stored in a file. 
**
*/

#include <stdio.h>	/* standard I/O routines.               */
#include <stdlib.h>	/* exit(), etc.                         */
#include <errno.h>	/* defines integer value for errorno	*/
#include <sys/types.h>	/* various type definitions.            */
#include <sys/ipc.h>	/* general SysV IPC structures          */
#include <sys/msg.h>	/* message queue structures 		*/
#include <signal.h>	/* handling signals			*/
#include <unistd.h>	/* fork()                               */

int msqid;				/* message queue ID */

struct my_msgbuf {
    	long mtype;	/* message type to be received from message queue */
    	char mtext[200];/* message to be received from message queue */
};

/* when CTRL-C is pressed server shutdown and message queue is deleted */
void 
my_handler_for_sigint(int signumber)
{
  	if (signumber == SIGINT)
  	{
   		printf("received SIGINT\n");
    		printf("Program received a CTRL-C\n"); 
       		printf("Existing ....\n");
		if (msgctl(msqid, IPC_RMID, NULL) == -1) 
    		{
        		perror("msgctl");
        		exit(1);
    		}
       		exit(0); 
  	}
}

int main(void)
{

   	/* Registering the Signal handler */
  	if (signal(SIGINT, my_handler_for_sigint) == SIG_ERR)
	{
      		printf("\ncan't catch SIGINT\n");
	}

	struct my_msgbuf buf;
    	key_t key;
	int answer, i, number1, number2;	/* to store answer, counter to iterate over message and two numbers */
	int str_length;				/* length of the number provided by client */
	char name[50], ch;			/* Name of the client and operation */
	char buffer[32];			/* filename buffer */
	int k = 1;				/* filename counter*/

    	FILE *f;				/* file where output has to be written */
    	f = fopen("out.txt", "w");
	if(f == NULL)
	{
		perror("file");
		exit(1);
	}

	key = ftok("msgQ_client.c", 'B');
    	if (key == -1) 
	{
        	perror("ftok");
        	exit(1);
    	}

	msqid = msgget(key, 0644 | IPC_CREAT);	/* creating a message queue */
    	if (msqid == -1) 
	{
        	perror("msgget");
        	exit(1);
    	}
    
    	printf("Server: ready to receive. \nArithmetic operation will be performed\n");
	printf("This server can handle maximum of 5 clients\n");

    	for(;;)  	/* server never quits! */
	{
		number1 = 0;
		number2 = 0;
		answer = 0;

		/* Receiving the message */
        	if (msgrcv(msqid, &buf, sizeof buf.mtext, 0, 0) == -1) 
        	{
			fprintf(f, "\n");
        	}

		/* Extracting the name of the client */
		for(i = 0; buf.mtext[i] != ':'; i++)
		{
			name[i] = buf.mtext[i];
		}
		name[i] = '\0';
		i++;

		/* Extracting the first number */
		while(1)
		{
			number1 = buf.mtext[i] - 48 + number1 * 10;
			i++;
			if((buf.mtext[i]-48 < 0) || (buf.mtext[i]-48 > 9))
			{	
				break;
			}
		}

		/* Finding the operation to be performed */
		ch = buf.mtext[i];
		i++;

		/* Extracting the second number */
		while(buf.mtext[i] != '\0')
		{
			if((buf.mtext[i]-48 < 0) || (buf.mtext[i]-48 > 9))
			{	
				break;
			}
			number2 = buf.mtext[i] - 48 + number2 * 10;
			i++;
		}
		
		/* Performing arithmetic operation */
		switch(ch)
		{
			case '+':
				answer = number1 + number2;
				fprintf(f, "Client ID: %ld, Name: %s, Answer: %d\n",buf.mtype, name, answer);
				fflush(f);
				break;
			case '-':
				answer = number1 - number2;
				fprintf(f, "Client ID: %ld, Name: %s, Answer: %d\n",buf.mtype, name, answer);
				fflush(f);
				break;
			case '*':
				answer = number1 * number2;
				fprintf(f, "Client ID: %ld, Name: %s, Answer: %d\n",buf.mtype, name, answer);
				fflush(f);
				break;
			case '/':
				answer = number1 / number2;
				fprintf(f, "Client ID: %ld, Name: %s, Answer: %d\n",buf.mtype, name, answer);
				fflush(f);
				break;
			default:
				printf("This operation cannot be performed\n");
		}

    	}

    	return 0;
}