//014_ordered example
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 4

int main(){
	int n = 9;
	int i , TID, a[10];

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel for default(none) ordered schedule(runtime) private(i,TID) shared(n,a)
	for( i = 0 ; i< n ; i++){
		TID = omp_get_thread_num();

		printf("Thread %d updates a[%d]\n", TID, i);

		a[i] = i; 

		#pragma omp ordered // print ordered. it's performance penalty
		{
			printf("Thread %d prints value of a[%d] = %d\n", TID, i ,a[i]);
		}
	}
}