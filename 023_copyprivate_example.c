//023_copyprivate example
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

float x, y, fGlobal = 1.0;


float get_float(){
	fGlobal += 0.1;
	return fGlobal;
}

#pragma omp threadprivate(x, y) 

int main() {
	float a, b;
	#pragma omp parallel private(a,b)
	{
		#pragma omp single copyprivate(a,b,x,y)
		{
			a = get_float();
			b = get_float();
			x = get_float();
			y = get_float();
		}

		printf("a Value = %f , thread = %d\n", a , omp_get_thread_num());
		printf("b Value = %f , thread = %d\n", b , omp_get_thread_num());
		printf("x Value = %f , thread = %d\n", x , omp_get_thread_num());
		printf("y Value = %f , thread = %d\n", y , omp_get_thread_num());
	}
}