//019_reduction example
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 8

int main(){
	int n = 10;
	int i, sum;
	float multout,f[n];

	omp_set_num_threads(NUM_THREADS);

	sum = 0;
	multout = 1.0;

	for (i = 0 ; i<= n ; i++) f[i] = 0.1 + ((float) i) * 0.1;


	#pragma omp parallel for private(i) shared(n) reduction(+:sum)
	for (i = 0 ; i<= n ; i++){
		sum += i;
	}

	printf("Value of sum after parallel region: %d\n", sum);

	#pragma omp parallel for private(i) shared(n) reduction(*:multout) 
	for(i =0; i<= n ; i++){
		multout *= f[i];
	}

	printf("Multiplication output = %.16f\n", multout);

	multout = 1.0;
	#pragma omp parallel for reduction(*:multout) 
	for(i =0; i<= n ; i++){
		multout *= f[i];
	}

	printf("Multiplication output = %.16f\n", multout);
}
