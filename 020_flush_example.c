//020_flush example
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 256

// i don't understand about this clause
int main(){
	int new_data, local_data, TID, signal;

	omp_set_num_threads(NUM_THREADS);

	signal = 0;
	new_data = 0;

	#pragma omp parallel default(none) shared(signal, new_data) private(TID,local_data)
	{
		TID = omp_get_thread_num();
		if (TID == NUM_THREADS-1) {
			new_data = 10;
			signal = 1;
			#pragma omp flush(new_data, signal) 
		} else {
			printf("[before flush] Thread %d has %d\n" , TID , local_data);
			while (signal == 0){sleep(1000);} ;
			local_data = new_data;
			printf("[after flush] Thread %d has %d\n" , TID , local_data);
		}
	}
}