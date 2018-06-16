//009_firstprivate clause
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define n 3

int main(){

	int offset, i;
	int a[n];

	for(i = 0 ; i< n ; i++) a[i] = 1;
	for(i = 0 ; i <n ; i++) printf("Before : a[%d] = %d\n" , i, a[i]);

	offset = 10;

	#pragma omp parallel for firstprivate(offset)
	for (i=0 ; i<n ; i++){
		if ( i == 0 || i == n-1)
			offset = offset + 2; 
		a[i] = a[i] + offset;
	}
	for (i = 0 ; i<n ;i++) printf("After: a[%d] = %d\n" , i, a[i]);
}