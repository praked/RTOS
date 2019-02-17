/*
** msgQ_client.c --------
** multiple users would like to run this this application  through a client. 
** Design a client and server model to implement this app.
** client of the App
** Maximum number of clients is 5. Once this maximum number is reached then it goes back to client 1.
** during execution type client name, and opeartion to be performed without space.
*/

#include <stdio.h>	/* standard I/O routines.               */
#include <stdlib.h>	/* exit(), etc.                         */
#include <errno.h>	/* defines integer value for errorno	*/
#include <string.h>	/* manipulating arrays of characters	*/
#include <sys/types.h>	/* various type definitions.            */
#include <sys/ipc.h>	/* general SysV IPC structures          */
#include <sys/msg.h>	/* message queue structures 		*/

struct my_msgbuf {
	long mtype;	/* message type to be received from message queue */
	char mtext[200];/* message to be received from message queue */
};

int main(void)
{
    	struct my_msgbuf buf;
    	int msqid;				/* message queue ID */
	int client_no=1//, max_client_no ;		/* client number and maximum number of clients allowed */
    	key_t key;

	key = ftok("client1.c", 'B');	/* same key as msgQ_client.c */
    	if (key == -1)   
	{
        	perror("ftok");
        	exit(1);
    	}

	msqid = msgget(key, 0644); 		/* connect to the queue */
    	if (msqid == -1)  
	{
        	perror("msgget");
        	exit(1);
    	}


    printf("Enter the Letter/character\n");
	printf("Do not provide any space,\n ^D to quit:\n");
	

	/* Read the message to be sent */
     if(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) 
	{
		
		buf.mtype = client_no;
    		int len = strlen(buf.mtext);

    		/* ditch newline at end, if it exists */
    		if (buf.mtext[len-1] == '\n') 
		{
			buf.mtext[len-1] = '\0';
		}

		/* Sending the message */
    		if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
		{
        			perror("msgsnd");
		}
		

	
    }

    return 0;
}