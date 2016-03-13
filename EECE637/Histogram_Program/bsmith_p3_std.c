//EECE 637
//Brandon Smith
//Project 3

//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<semaphore.h>

#define KEYNUM		8675
#define KEY_DATA	150
#define SEM1		"start1"
#define SEM3		"end1"

//Structure for data passed to processes
struct thread_data
{
	int size;
	int binsize;
	int max;
	float s_dev;
};

int main()
{
	//printf("Std: Initializing Std\n");

	//Open Semaphores
	sem_t* start1 = sem_open(SEM1, 0);
	sem_t* end1 = sem_open(SEM3, 0);
	
	//Define Variables
	int i;
	int sem_check;
	double sum = 0;
	float std = 0;
	double mean;
	int size;
	int quit = 1;

	//---------------Attach shared memory------------------------
	//printf("Std: Setting up shared memory for std\n");
	int shmid = shmget(KEYNUM, sizeof(struct thread_data), 0666);
	struct thread_data* st = (struct thread_data*) shmat(shmid, NULL, 0);
	//-----------------------------------------------------------

	//-------------Allocate struct->data for processes---------------
	int shmid2 = shmget(KEY_DATA, sizeof(double)* st->size, 0666);
	double* dataset = (double*) shmat(shmid2, NULL, SHM_RDONLY);
	//---------------------------------------------------------------

	//Get semaphore values
	//sem_getvalue(start1, &sem_check);
	//printf("Std: start1 is %i\n", sem_check);
	//sem_getvalue(end1, &sem_check);
	//printf("Std: end1 is %i\n", sem_check);

	//Wait for main initially
	//printf("Std: Std waiting for main\n");
	sem_wait(start1);
	//printf("Std: Std no longer waiting\n");

	while(quit != 0)
	{
		size = st->size;
		sum = 0;

		//printf("Std: Std accessed data structure just fine\n");
		//printf("Std: Size is %i\n", size);
		
		for(i = 0; i < size; i++)
		{
			sum = sum + dataset[i];
		}

		//printf("Std: Std summed data set just fine\n");
	
		mean =  sum/(double)size;		//calculate average

		//printf("Std: mean is %f\n", mean);
	
		std = 0;
		for(i = 0; i < size; i++)
		{
			std = std + pow((dataset[i]-mean), 2);
		}

		st->s_dev = sqrt(std/(size-1));	//calculate std and update structure
	
		//Tell main that function is done
		//printf("Std: Telling main that std is done\n");
		sem_post(end1);

		//Wait for main
		//printf("Std: Std waiting for main\n");
		sem_wait(start1);
		//printf("Std: Std no longer waiting\n");

		//Update quit
		quit = st->size; //Main will set size to 0 when done
		//printf("Std: Quit in std is...%i\n", quit);
	}

	//printf("Std: Cleaning up\n");

	//Detach from shared memory
	shmdt(&shmid);
	shmdt(&shmid2);
	
	//printf("Std: Std quitting\n");
	return 0;
}