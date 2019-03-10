#include <stdio.h> 
#include <sys/ipc.h> 
#include <unistd.h>
#include <sys/msg.h> 
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
  
// structure for msg1 queue 

struct msg_txt
{
   int qid;
   char data[100];	
};
struct msg { 
    long msg_typ; 
    struct msg_txt msg_txt; 
} msg1; 
  
int main() 
{ 
    key_t key; 
    int msgid;
    int i; 
  
    // ftok to generate unique key which acts as an indentifier for the message queue
    //so that different processes can access it with the identifier
    key = ftok("pfile", 18); 
  
    // msgget creates a msg1 queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
  

    while(1)
    {
    	   // msgrcv to receive msg1 
	    while(msgrcv(msgid, &msg1, sizeof(msg1), 1, 0)<=0); 
	  
	    // display the msg1 
	    printf("Data Received is : %s \n",  
		            msg1.msg_txt.data); 
	    
            for(i=0;i<100;i++){
            	if(msg1.msg_txt.data[i]>='a' && msg1.msg_txt.data[i]<='z'){
            		msg1.msg_txt.data[i]=msg1.msg_txt.data[i]-32;
            	}
            	else if(msg1.msg_txt.data[i]>='A' && msg1.msg_txt.data[i]<='Z'){
            		msg1.msg_txt.data[i]=msg1.msg_txt.data[i] + 32;
            	}
            }		
	    printf("Data sent is : %s \n", msg1.msg_txt.data);  
            int qid=msg1.msg_txt.qid;
	    msg1.msg_txt.qid=msgid;
	    msgsnd(qid, &msg1, sizeof(msg1), 0); 
    }
   
    // to destroy the msg1 queue 
    //msgctl(msgid, IPC_RMID, NULL); 
  
    return 0; 
} 
