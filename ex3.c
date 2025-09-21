#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

static long int num_steps = 1000;

int main(){

	int i;
	double pi = 0.0, step = 1.0 / (double) num_steps;

	double time1 = omp_get_wtime();

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
		int j, num_id, num_threads;
		double x, sum = 0.0;
		num_threads = omp_get_num_threads();
		num_id = omp_get_thread_num();

		for(j = num_id; j < num_steps; j += num_threads){
			x = (j + 0.5) * step;
			sum += 4.0 / (1.0 + x * x);
		}
		#pragma omp critical
		pi += step * sum;
		//sum *= step; #pragma omp atomic pi += sum;
	}

	double time2 = omp_get_wtime();

	printf("Pi: %lf, and parallel time: %lf\n", pi, time2 - time1);

	return 0;

}
