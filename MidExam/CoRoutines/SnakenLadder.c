#include <stdio.h> 
#include <string.h> 
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
#include <sys/time.h>


// Global Variables
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
int co_create(void *(*func)(void *)){
	pthread_create(&(th_id[th_count++]), NULL, func, NULL);
	pthread_mutex_lock(&MainLock);
	return th_count - 1;
}

// Send data to a co routine and continue execution
void co_send(int co_id, char * msg){
	strcpy(Msg, msg);
	pthread_mutex_unlock(&(th_locks[co_id]));
	pthread_mutex_lock(&MainLock);
}

// Breakpoints within functions
void co_breakpoint(int co_id){
	pthread_mutex_unlock(&MainLock);
	pthread_mutex_lock(&(th_locks[co_id]));
}

// Kill a co routine
void co_kill(int co_id){
	pthread_cancel(th_id[co_id]);
	pthread_mutex_destroy(&(th_locks[co_id])); 
}

/*SUBROUTINES FOR SNAKE & LADDER*/
int PlayerLocation[100];
int snake_s[9] = {8,  18, 26, 39, 51, 55, 78, 85, 99};
int snake_d[9] = {4, 1, 10, 5, 6,  20, 30, 55, 9};
int ladder_s[10] =      {5, 6, 11, 15, 17,24 ,36, 41, 50, 80};
int ladder_d[10] = {20, 14, 23, 36, 76,77, 51, 62, 72, 97};
int PlayerWin[100];
int Wins[100];
int WinCount = 0;

// Rolls a die
int roll_dice(){
	return (rand()%6) + 1;
}

int get_ind(int v, int * l, int len){
	int i = 0;
	for(i = 0; i < len; i++){
		if(l[i] == v) return i;	
	}
	return -1;
}

////////////// CO-ROUTINES FOR SNAKE & LADDER
// Plays a round
void* player(void *arg) 
{ 
	int co_id = th_count - 1;
	int player_id = co_id;
	PlayerLocation[player_id] = 0;
	PlayerWin[player_id] = 0;
	
	while(1){
		co_breakpoint(co_id);
		printf("Player %d at %d playing a turn\n", co_id, PlayerLocation[player_id]);
		int die_roll = roll_dice();
		printf("\t--Rolled a %d\n", die_roll);
		PlayerLocation[player_id] += die_roll;

		while(1){
			// exit if no snake_s or ladder_ss
			if(get_ind(PlayerLocation[player_id], snake_s, 10) == -1 && get_ind(PlayerLocation[player_id], ladder_s, 10) == -1){
				break;
			// Check for snake
			}else if(get_ind(PlayerLocation[player_id], snake_s, 10) != -1){
				int i = get_ind(PlayerLocation[player_id], snake_s, 10);
				PlayerLocation[player_id] = snake_d[i];
				printf("\t--Met a snake\n");
			// Check for ladder_s
			}else if(get_ind(PlayerLocation[player_id], ladder_s, 10) != -1){
				int i = get_ind(PlayerLocation[player_id], ladder_s, 10);
				PlayerLocation[player_id] = ladder_d[i];	
				printf("\t--Climbed a ladder_s\n");
			}	
		}
		
		// Print location
		printf("\t--New location is %d\n",  PlayerLocation[player_id]);

		// Check for win
		if(PlayerLocation[player_id] >= 100){
			printf("Player %d Wins!\n", co_id);
			Wins[WinCount++] = player_id;
			PlayerWin[player_id] = 1;
			while(1){
				co_breakpoint(co_id);
			}
		}
	
	}

	return NULL; 
} 

/* Main */

int main(void) 
{ 	
	struct timeval stop, start;
	srand(time(0)); 
	// Init
	co_init();
	gettimeofday(&start, NULL);

	// Create some co-routines 
	int p1 = co_create(&player);
	int p2 = co_create(&player);
	int p3 = co_create(&player);
	int p4 = co_create(&player);
	
	// Send some messages to co-routines
	while(PlayerWin[p1] == 0 | PlayerWin[p2] == 0 | PlayerWin[p3] == 0 | PlayerWin[p4] == 0){
		//delay(1);
		if(PlayerWin[p1] == 0)co_send(p1, "Play");
		if(PlayerWin[p2] == 0)co_send(p2, "Play");
		if(PlayerWin[p3] == 0)co_send(p3, "Play");
		if(PlayerWin[p4] == 0)co_send(p4, "Play");
	}

	// Winners
	printf("Winners\n");
	printf(" 1st place : %d\n", Wins[0]);
	printf(" 2nd place : %d\n", Wins[1]);
	printf(" 3rd place : %d\n", Wins[2]);
	printf(" 4th place : %d\n", Wins[3]);

	// Kill the routines
	co_kill(p1);
	co_kill(p2);
	co_kill(p3);
	co_kill(p4);

	gettimeofday(&stop, NULL);
	printf("Total turnaround time: %lu\n", stop.tv_usec - start.tv_usec);
		
	return 0; 
} 
