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
#include<sys/shm.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<semaphore.h>
#include<errno.h>
#include<string.h>

#define STD_PATH 	"/home/pi/Desktop/std"
#define HIST_PATH 	"/home/pi/Desktop/hist"

#define DEBUG		0
#define DATA_RANGE 	1000
#define MULT 		1000
#define BIN 		10 
#define KEYNUM		8675
#define KEY_DATA	150
#define KEY_DIST	200	
#define SEM1		"start1"
#define SEM2		"start2"
#define SEM3		"end1"
#define SEM4		"end2"

//Structure for data passed to processes
struct thread_data
{
	int size;
	int binsize;
	int max;
	float s_dev;
};

int main(int argc, char* argv[])
{
	//Check for command line arguments
	if(argc != 3)
	{
		printf("Wrong number of arguments\n");
		exit(1);
	}

	//Create four semaphores
	sem_t* start1 = sem_open(SEM1, O_CREAT, 0777, 0);
	sem_t* start2 = sem_open(SEM2, O_CREAT, 0777, 0);
	sem_t* end1 = sem_open(SEM3, O_CREAT, 0777, 0);
	sem_t* end2 = sem_open(SEM4, O_CREAT, 0777, 0);

	if(start1 == SEM_FAILED || start2 == SEM_FAILED || end1 == SEM_FAILED || end2 == SEM_FAILED)
	{
		printf("Semaphore create failed\n");
		printf("Errno: %s", strerror(errno));
		exit(1);
	}
	
	//Create Variables
	float std;
	int size  = atoi(argv[1]) * MULT;
	float temp;
	int sem_check;
	int j;
	int i;
	struct timespec t_start, t_end;

	//-------------Allocate shared memory for processes--------------
	//printf("Main: Creating shared memory\n");
	int shmid = shmget(KEYNUM, sizeof(struct thread_data), IPC_CREAT | 0666);
	struct thread_data* shm_ptr = (struct thread_data*) shmat(shmid, NULL, 0);
	//---------------------------------------------------------------

	//Initialize structure
	shm_ptr->size = size;
	shm_ptr->binsize = BIN;
	shm_ptr->max = DATA_RANGE;

	size_t testing = size * sizeof(double);
	
	//-------------Allocate struct->data for processes---------------
	int shmid2 = shmget(KEY_DATA, (size * sizeof(double)), IPC_CREAT | 0666);
	if(shmid2 < 0)
	{
		printf("Shmget failure\n");
		printf("Errno: %s", strerror(errno));
		exit(1);
	}
	double* data = (double*) shmat(shmid2, NULL, 0);
	if((int)data == -1)
	{
		printf("Shmat failure\n");
		printf("Errno: %s", strerror(errno));
		exit(1);
	}
	//---------------------------------------------------------------

	//-------------Allocate struct->distribution for processes-------
	int shmid3 = shmget(KEY_DIST, sizeof(float) * BIN, IPC_CREAT |0666);
	if(shmid3 < 0)
	{
		printf("Shmget failure\n");
		printf("Errno: %s", strerror(errno));
		exit(1);
	}
	float* histogram = (float*) shmat(shmid3, NULL, 0);
	if((int)histogram == -1)
	{
		printf("Not allocated\n");
		printf("Errno: %s", strerror(errno));
		exit(1);
	}
	//---------------------------------------------------------------

	//-------------Create Processes--(might need to chance directory)---------------------------
	pid_t process_std;
	pid_t process_hist;

	//printf("Main: Creating first process\n");
	process_std = fork();
	if(process_std == 0)
	{
		execl(STD_PATH, NULL);
		perror("execl() failure!\n");
		exit(1);
	}

	//printf("Main: Creating second process\n");
	process_hist = fork();
	if(process_hist == 0)
	{
		execl(HIST_PATH, NULL);
		perror("execl() failure!\n");
		exit(1);
	}
	//---------------------------------------------------------------

	//Seed Random
	srand(time(0));
	
	//Main Loop
	for(j = 0; j < atoi(argv[2]); j++)
	{
		temp = 0;
		
		//Get start time
		clock_gettime(CLOCK_REALTIME, &t_start);  	

		//Fill data with random numbers
		for(i = 0; i < size; i++)
		{
			data[i] = rand() % DATA_RANGE;
		}

		//Check semaphore values
		//sem_getvalue(start1, &sem_check);
		//printf("Main: before start1 is %i\n", sem_check);
		//sem_getvalue(start2, &sem_check);
		//printf("Main: before start2 is %i\n", sem_check);

		//Tell other processes data is ready	
		//printf("Main: Telling other processes data is ready\n");
		sem_post(start1);
		sem_post(start2);	
		
		//Check semaphore values
		//sem_getvalue(start1, &sem_check);
		//printf("Main: start1 is %i\n", sem_check);
		//sem_getvalue(start2, &sem_check);
		//printf("Main: start2 is %i\n", sem_check);
		//sem_getvalue(end1, &sem_check);
		//printf("Main: end1 is %i\n", sem_check);
		//sem_getvalue(end2, &sem_check);
		//printf("Main: end2 is %i\n", sem_check);
		//printf("Waiting on other processes\n");

		//Wait for other processes	
		sem_wait(end1);
		sem_wait(end2);

		//printf("Main: Main no longer waiting\n");

		//Grab Updated Data
		std = shm_ptr->s_dev;

		//Print Results
		printf("Standard Deviation: %.2f\n", std);
		printf("Distribution: ");
		for(i = 0; i < BIN; i++)
		{
			temp = temp + histogram[i];
			printf(" %.2f%%", histogram[i]);
		}
		printf("  Total: %.2f%%\n", temp);

		//Get end time
		clock_gettime(CLOCK_REALTIME, &t_end);
		printf("Time elapsed was %.2f milliseconds\n\n",
			((double)t_end.tv_sec-(double)t_start.tv_sec)*1000 + 
			((double)t_end.tv_nsec - (double)t_start.tv_nsec)/1000000);
	}

	//Let other processes quit
	shm_ptr->size = 0;
	sem_post(start1);
	sem_post(start2);

	//--------------------------Cleanup---------------------------------
	//printf("Cleaning up\n");	

	//Delete semaphores
	sem_unlink(SEM1);
	sem_unlink(SEM2);
	sem_unlink(SEM3);
	sem_unlink(SEM4);
	
	//Change shared memory so it detaches and delets on shmdt
	shmctl(shmid, IPC_RMID, NULL);
	shmctl(shmid2, IPC_RMID, NULL);
	shmctl(shmid3, IPC_RMID, NULL);

	//Detach shared memory
	shmdt(&shmid);
	shmdt(&shmid2);
	shmdt(&shmid3);
	//------------------------------------------------------------------
	
return 0;
}





