// 02_loop construct

#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int main(int argc, char* argv){
	int n = 8;
	int i ;

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel shared(n) private(i)
	{
		#pragma omp for 
			for (int i = 0; i < n; ++i)
			{
				printf(" Threads %d executes loop iteration %d\n", omp_get_thread_num(), i);
			}
			
	}
}