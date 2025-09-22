#include <stdio.h>
#include <omp.h>

static long int num_steps = 1000;

int main(){

	int i;
	double pi, sum = 0.0, step = 1.0 /(double) num_steps;

	double time1 = omp_get_wtime();

	#pragma omp parallel
	{
		double x;
		#pragma omp for schedule(static) reduction(+:sum)
		for(i = 0; i < num_steps; i++){
			x = (i + 0.5) * step;
			sum += 4.0 / (1.0 + x * x);
		}
	}

	double time2 = omp_get_wtime();

	pi = step * sum;

	printf("Pi: %lf, time: %lf\n", pi, time2 - time1);
	return 0;
}

