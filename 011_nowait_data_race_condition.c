//011_nowait data race condition
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 8

int main() {

	int n = 16;
	int a[n], b[n], z[n];
	int i;

	for(i = 0 ; i< n ; i++){b[i]= z[i] = 0; a[i] = i;}

	#pragma omp parallel
	{
		#pragma omp for nowait
		for( i = 1 ; i < n ; i++){
			b[i] = a[i] + a[i-1];
		}

		#pragma omp for nowait 
		for( i = 1 ; i < n ;i++) {
			z[i] = b[i] * b[i-1];
		}
	}
	
	for(i = 1 ; i< n ;i++){
		if(b[i] != a[i] + a[i-1]) printf("b[%d] : %d , expect %d \n", i, b[i], a[i]+a[i-1]);
		if(z[i] != b[i] * b[i-1]) printf("z[%d] : %d , expect %d \n", i, z[i], b[i]*b[i-1]);
		//printf("b[%d] : %d, z[%d] : %d \n", i, b[i], i, z[i]);
	}
}