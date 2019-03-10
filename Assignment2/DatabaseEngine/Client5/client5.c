

#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <time.h>
#include<string.h>
#include<unistd.h>
#define BILLION  1000000000.0;
 
  
// structure for msg1 queue 

struct msg_txt
{
   int qid;//client id
   char data[100];	
};
struct msg { 
    long msg_typ; 
    struct msg_txt msg_txt; 
} msg1; 
  
int main() 
{ 
	key_t key;
	//server MQ id,client MQ id 
	int msgid,qid;

  
	qid=msgget(IPC_PRIVATE,0660);	
    // ftok to generate unique key 
	key = ftok("pfile", 18); 
  
    // msgget creates a msg1 queue and returns identifier 
	msgid = msgget(key, 0666 | IPC_CREAT); 


	char input[100];
	memset(input,'\0',sizeof(char)*100);
	printf("Write Data : ");  
	fgets(input,sizeof(input),stdin);

	while(1)
	{		

		struct timespec start, end;
		
		msg1.msg_typ = 1; 
		msg1.msg_txt.qid=qid;
		clock_t t; 
	  
	    // msgsnd to send msg1 
		for(int i=0;i<100;i++)
	    	msg1.msg_txt.data[i]=input[i];

		clock_gettime(CLOCK_REALTIME, &start);
		msgsnd(msgid, &msg1, sizeof(msg1), 0); 
	  
	    // display the msg1 
		printf("Data sent is : %s", msg1.msg_txt.data);
		while(msgrcv(qid, &msg1, sizeof(msg1), 1, 0)<=0); 
	  
	    // display the msg1
		clock_gettime(CLOCK_REALTIME, &end);
		double time_spent = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / BILLION;
		printf("Data Received is : %s", msg1.msg_txt.data); 

		printf("server took %f seconds to execute \n\n", time_spent); 
	}
	msgctl(qid, IPC_RMID, NULL); 

  
    return 0; 
} 

