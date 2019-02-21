#include <stdio.h> 
#include <sys/ipc.h> 
#include<unistd.h>
#include <sys/msg.h> 
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
  
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
	    //extract the filename i.e ignore 'GET'	
	    char filename[10];
    	    memset(filename,'\0',sizeof(char)*10); 
	    int i;
	    int count=0;		    
	    //getting file name
	    for(i=4;i<14;i++)
	    {
		if(msg1.msg_txt.data[i]!='\n'){
			filename[i-4]=msg1.msg_txt.data[i];
			count++;
		}		
		else
	        	break;
	    }

	    char ch[100];
	    int fd;
	    int al_read;
	    //  file reading 
	    char path[100]="/home/anshuk/8th_sem/RTOS/assigns/ASSIGNMENT-1/Database_Engine/server/";
	    strcat(path,filename);	
	    
            fd=open(path,O_RDONLY);
	    printf("filename is:%s\n",path);
	    if (fd == -1)

	    {
	    	char reply[30]="data not found";
		
		for(int i=0;i<30;i++)
			msg1.msg_txt.data[i]=reply[i];

	    }
	    else
	    {
		 printf("%d\n",fd);
		 al_read=read(fd,&ch,100);
                 int i=0;
		 ch[al_read]='\0';
		 //printf("%d\n",al_read);
		 while (i<100)

		 {
			if(ch[i]!='\0')
				msg1.msg_txt.data[i]=ch[i];
			//printf("%c",ch[i]);

			
			else
				msg1.msg_txt.data[i]='\0';
			i++;
			

		  }

		 close(fd);
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
