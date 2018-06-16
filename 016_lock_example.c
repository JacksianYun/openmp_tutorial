//016_lock example
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

omp_lock_t my_lock;

int main() {
	omp_init_lock(&my_lock);

	#pragma omp parallel num_threads(4)
	{
		int tid = omp_get_thread_num();
		int i ;

		for(i = 0 ; i< 2; i++){
			omp_set_lock(&my_lock);
			printf("Thread %d - starting locked region\n", tid);
			printf("Thread %d - end locked region\n", tid);
			omp_unset_lock(&my_lock);
		}
	}
	omp_destroy_lock(&my_lock);
}