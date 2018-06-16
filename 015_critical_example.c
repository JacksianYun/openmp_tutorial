//015_critical example
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(){
	int n = 100;
	int i, TID;
	int sum, sumlocal;

	sum = 0;

	#pragma omp parallel private(i,TID, sumlocal) shared (n,sum)
	{
		TID = omp_get_thread_num();
		sumlocal = 0;

		#pragma omp for 
		for(i = 0 ; i< n ; i++){
			sumlocal += i;
		}

		#pragma omp critical
		{
			sum += sumlocal;
			printf("TID : %d: sumlocal= %d, sum %d\n",TID,sumlocal,sum);
		}
	}
	printf("Value of sum after parallel region : %d\n", sum);
}