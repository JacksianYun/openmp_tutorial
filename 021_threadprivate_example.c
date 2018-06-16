//021_threadprivate example
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define TRUE 1 
#define FALSE 0

int calculate_sum (int length);

int *pglobal;

#pragma omp threadprivate(pglobal) 

int main(){
	int i, j, sum, TID, n = 5;
	int length[n];

	for (i=0; i< n ;i++) length[i] = 10 * (i+1) ;

	#pragma omp parallel for shared(n,length) private(TID, i, j, sum) 
	for (i = 0 ; i< n ; i++){
		TID = omp_get_thread_num();

		if ((pglobal = (int *) malloc(length[i]*sizeof(int))) != NULL ) {
			for ( j = 0 ; j< length[i] ; j++) pglobal[j] = j+1;
			sum = calculate_sum(length[i]);

			printf("TID %d : value of sum for i = %d is %d\n", TID, i ,sum) ;
			free(pglobal);
		}
	}
	return 0;
}

int calculate_sum(int length) {
	int sum = 0;
	int j ;
	for (j = 0 ; j < length ; j++) sum += pglobal[j];
	return sum;
}
