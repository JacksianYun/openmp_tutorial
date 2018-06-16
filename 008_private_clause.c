//008_private clause
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 4

int main(int argc, char* argv){
	int n = 8;
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel private(n)
	{
		printf("n is %d ; Thread %d \n", n, omp_get_thread_num());
	}
}