//013_barrier
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_THREADS 4

double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;
     
    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
     
    diff = (double)y_ms - (double)x_ms;
     
    return diff;
}

int main() {
	int n = 9;
	int i , TID, a[10];
	struct timeval before , after;

	gettimeofday(&before , NULL);

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel private(TID,after)
	{
		TID = omp_get_thread_num();

		printf("Before : %d\n", omp_get_thread_num());
		gettimeofday(&after , NULL);
		printf("Total time elapsed : %.0lf us \n" , time_diff(before , after) );

		if(TID < omp_get_num_threads()/2 ) system("sleep 3");

		#pragma omp barrier 

		printf("After : %d\n", omp_get_thread_num());
		gettimeofday(&after , NULL);
		printf("Total time elapsed : %.0lf us \n" , time_diff(before , after) );
	}

	//barrier implemnetation 

	int arrive = NUM_THREADS;
	printf("Another Implementation\n");
	#pragma omp parallel private(TID)
	{
		TID = omp_get_thread_num();

		printf("Before : %d\n", omp_get_thread_num());
		gettimeofday(&after , NULL);
		printf("Total time elapsed : %.0lf us \n" , time_diff(before , after) );

		if(TID < omp_get_num_threads()/2 ) system("sleep 3");

		#pragma omp atomic 
		arrive--;

		while(arrive>0){}

		printf("After : %d\n", omp_get_thread_num());
		gettimeofday(&after , NULL);
		printf("Total time elapsed : %.0lf us \n" , time_diff(before , after) );
	}
}