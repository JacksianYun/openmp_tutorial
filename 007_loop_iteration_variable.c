//007_loop iteration variable
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define M 1024
#define N 1024*1024

int main(){
	int i,j;
	int sum, local_sum;
	int * a;

	a = (int*) malloc(N*sizeof(int));

	sum = 0; 

	for(i = 0 ; i< N ; i++) a[i] = i;

	#pragma omp parallel private(local_sum) num_threads(4)
	{
		local_sum = 0;

		#pragma omp for private(j)
		//#pragma omp for 
		for( i = 0 ; i < M ;i++)
			for(j = 0 ; j< M ;j++)
				local_sum += a[j];

		#pragma omp critical
		{
			sum += local_sum;			
		}
	}
	printf("sum is %d \n", sum);
	free(a);
}