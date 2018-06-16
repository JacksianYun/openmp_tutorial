//022_copyin Clause
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 4

int x;

#pragma omp threadprivate(x)

int main(){
	int tid;
	x = 33;

	omp_set_num_threads(NUM_THREADS);

	//#pragma omp parallel private(tid) copyin(x) 
	#pragma omp parallel private(tid) 
	{
		tid = omp_get_thread_num();
		printf("Thread %d, x = %d\n", tid , x);
	}
}