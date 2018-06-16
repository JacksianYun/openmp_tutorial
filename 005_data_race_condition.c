//005_data race condition

#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 128

int main(int argc, char* argv){
	for(int i = 0 ; i< 10000 ; i++){
		int Xshared;

		omp_set_num_threads(NUM_THREADS);

		#pragma omp parallel
		{
			int Xlocal = omp_get_thread_num();
			Xshared = omp_get_thread_num();

			if(Xlocal != Xshared){
				printf("Xlocal is %d; Xshared %d \n", Xlocal, Xshared);
			}
		}
	}
}