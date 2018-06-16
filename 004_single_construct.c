//04_single construct

#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define N 8

int main(int argc, char* argv){
	int i,a,b[N];
	a = 0;
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel shared(a,b) private(i)
	{
		#pragma omp single
		{
			a=10;
			printf("Single construct executed by thread %d\n",omp_get_thread_num());
		}

		#pragma omp for 
			for( i = 0 ; i < N ; i++) b[i] = a;
	}

	printf("After the parallel region\n");
	for (int i =0 ; i< N ; i++){
		printf("b[%d] = %d \n",i,b[i]);
	}
}