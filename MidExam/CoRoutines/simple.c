#include <stdio.h> 
#include <string.h> 
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 




//Global  Variables
#define MaxCoRout 100
pthread_t th_id[MaxCoRout]; 
long int th_count = 0;
pthread_mutex_t th_locks[MaxCoRout]; 
pthread_mutex_t MainLock;
char Msg[100] = "\0";

// Co-Routine Functions
//initialisation
void co_init(){
	
	int i = 0; 
	for(i = 0; i < 100; i++){
		pthread_mutex_init(&(th_locks[i]), NULL);
		pthread_mutex_lock(&(th_locks[i]));
	}

	pthread_mutex_lock(&MainLock);
}

// Create a co-routine by passing function pointer
int co_create(void *(*f)(void *)){
	pthread_create(&(th_id[th_count++]), NULL, f, NULL);
	pthread_mutex_lock(&MainLock);
	return th_count - 1; 
}

// Send data to a co routine and continue execution
void co_send(int cr_id, char * msg){
	strcpy(Msg, msg);
	pthread_mutex_unlock(&(th_locks[cr_id]));
	pthread_mutex_lock(&MainLock);
}

// Breakpoints within functions
void co_breakpoint(int cr_id){
	pthread_mutex_unlock(&MainLock);
	pthread_mutex_lock(&(th_locks[cr_id]));
}
// Kill a co routine
void co_kill(int cr_id){
	pthread_cancel(th_id[cr_id]);
	pthread_mutex_destroy(&(th_locks[cr_id])); 
}

////////////// SUBROUTINES

void* print_add1(void *arg) 
{ 
	int cr_id = th_count - 1;
	
	while(1){
		co_breakpoint(cr_id);
		printf("print_add1 co-routine #%d recieved message %d\n", cr_id, atoi(Msg) +1 );  
	}

	return NULL; 
} 


////////////// MAIN

int main(void) 
{ 	
	// Init
	co_init();

	// Create some co routines 
	int cr1 = co_create(&print_add1);
	int cr2 = co_create(&print_add1);
	int cr3 = co_create(&print_add1);
	
	
	// Send some messages to co routines
	co_send(cr1, "10");
	co_send(cr3, "1");
	co_send(cr2, "5");
	co_send(cr1, "2");
	co_send(cr3, "7");
	co_send(cr2, "31");
	
	// Kill the routines
	co_kill(cr1);
	co_kill(cr2);
	co_kill(cr3);
		
	return 0; 
} 
