//018_Incorrect use of master
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 4

int main(){
	int Xinit = 0, Xlocal;

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
		// It is similar to the single construct , 
		//but it does not have implied barrier on entry or exit
		#pragma omp master
		{ Xinit = 10; }

		Xlocal = Xinit;
		printf("TID %d , Xlocal = %d\n", omp_get_thread_num(), Xlocal);
	}
}