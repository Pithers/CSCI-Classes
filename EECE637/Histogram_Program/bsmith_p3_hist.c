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
#define KEY_DIST	200
#define SEM2		"start2"
#define SEM4		"end2"


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
	//printf("Hist: Initializing Hist\n");

	//Open Semaphores
	sem_t* start2 = sem_open(SEM2, 0);
	sem_t* end2 = sem_open(SEM4, 0);

	//Define Variables
	int i;
	int j;
	int sem_check;
	float temp;
	int size;
	int binsize;
	int max;
	int quit = 1;
	
	//---------------Attach shared memory------------------------
	//printf("Hist: Setting up shared memory for hist\n");
	int shmid = shmget(KEYNUM, sizeof(struct thread_data), 0666);
	struct thread_data* st = (struct thread_data*) shmat(shmid, NULL, 0);
	//-----------------------------------------------------------

	//-------------Allocate struct->data for processes---------------
	int shmid2 = shmget(KEY_DATA, sizeof(double) * st->size, 0666);
	double* dataset = (double*) shmat(shmid2, NULL, SHM_RDONLY);
	//---------------------------------------------------------------

	//-------------Allocate struct->distribution for processes-------
	int shmid3 = shmget(KEY_DIST, sizeof(float) * st->binsize, 0666);
	float* h = (float*) shmat(shmid3, NULL, 0);
	//---------------------------------------------------------------

	//Check semaphore values
	//sem_getvalue(start2, &sem_check);
	//printf("Hist: start2 is %i\n", sem_check);
	//sem_getvalue(end2, &sem_check);
	//printf("Hist: end2 is %i\n", sem_check);

	//Wait for main
	//printf("Hist: Hist waiting for main\n");
	sem_wait(start2);
	//printf("Hist: Hist no longer waiting\n");

	while(quit != 0)
	{
		size = st->size;
		binsize = st->binsize;
		max = st->max;

		//printf("Hist: Hist accessed data structure just fine\n"); 
	
		double bin_area = max/binsize;

		//printf("Hist: Max: %i Binsize: %i Size: %i\n", max, binsize, size);
	
		for(i = 0; i < binsize; i++)			//initialize array
		{
			h[i] = 0;
		}

		//printf("Hist: Initializing distribution array\n");
	
		for(j = 0; j < size; j++)			//for every value in array
		{
			if(dataset[j] == max)			//since we start at zero, must account for max number
			{
				h[binsize-1] = h[binsize-1] + 1;
			}
			else
			{
				for(i = 0; i < binsize; i++)	//see what bin the data fits in
				{
					if(dataset[j] >= i*(bin_area) && dataset[j] <= (i+1)*(bin_area)-1)
					{
						h[i] = h[i] + 1;	
					}
				}
			}
		}
	
		for(i = 0; i < binsize; i++)	//convert bin number to a percentage
		{
			h[i] = h[i]/((float)(max * (size/1000)))*100;
		}

		//Tell main that function is done
		//printf("Hist: Telling main that hist is done\n");
		sem_post(end2);

		//Wait for main
		//printf("Hist: Hist waiting for main\n");
		sem_wait(start2);
		//printf("Hist: Hist no longer waiting\n");

		//Update quit
		quit = st->size; //Main will set size to 0 when done
		//printf("Hist: Quit in hist is...%i\n", quit);
	}

	//printf("Std: Cleaning up\n");

	//Detach from shared memory
	shmdt(&shmid);
	shmdt(&shmid2);
	shmdt(&shmid3);

	//printf("Hist: Hist quitting\n");
	return 0;
}