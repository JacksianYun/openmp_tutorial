//006_data race condition_compute
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

double p_compute(int n);
double s_compute(int n);
void asum(int n);

int main(){

	double sum = p_compute(1000000);
	printf("pritvate compute %lf \n", sum);

	sum = s_compute(1000000);
	printf("shared compute %lf \n", sum);

	asum(100);
}

double p_compute(int n){
	int i ;
	double h,x,sum;

	sum = 0.0;
	h = 1.0 / (double) n;


	#pragma omp parallel for reduction(+:sum) shared(h) private(x)
	//#pragma omp parallel for reduction(+:sum) shared(h,x)
	for(i = 0 ; i<= n; i++){
		// x value will be change when move to next line if state on shared
		x = h * ((double)i + 0.5);  
		sum += (4.0 / (1.0 + x* x)) / n;
	}

	return sum;
}

double s_compute(int n){
	int i ;
	double h,x,sum;

	sum = 0.0;
	h = 1.0 / (double) n;


	//#pragma omp parallel for reduction(+:sum) shared(h) private(x)
	#pragma omp parallel for reduction(+:sum) shared(h,x)
	for(i = 0 ; i<= n; i++){
		// x value will be change when move to next line if state on shared
		x = h * ((double)i + 0.5);  
		sum += (4.0 / (1.0 + x* x)) / n;
	}

	return sum;
}

void asum(int n){
	int pri[n];
	int shr[n];
	int pidx;
	int sidx;
	for(int i = 0 ; i < n ; i++) pri[i]= shr[i]=0;
	int i; 
	#pragma omp parallel for shared(pri) private(i,pidx)
		for(i =0 ; i< n ;i++){
			pidx = i;
			pri[pidx] = pri[pidx] + i;	
		} 
	
	
	#pragma omp parallel for shared(shr,i,sidx) 
		for(i =0 ; i< n ;i++){
			sidx = i;
			shr[sidx] = shr[sidx] + i;	
		} 
	

	for(i = 0 ; i<n ;i++){
		if(pri[i] != shr[i])
			printf("pri[%d] : %d , shr[%d] : %d \n", i,pri[i],i,shr[i]);
	}
}