//03_section construct

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 8

void funcA();
void funcB();

int main(int argc, char* argv){
	int n = 8;
	int i ;

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel sections
	{
		#pragma omp section
			funcA();
		#pragma omp section
			{
				funcB();
			}
		#pragma omp section
			funcB();
		
	}
}

void funcA()
{
	printf("in funcA: this section is executed by thread %d\n", omp_get_thread_num());
}

void funcB()
{
	printf("in funcB: this section is executed by thread %d\n", omp_get_thread_num());
}