#include <stdio.h>
#include <omp.h>
#define NUM 2
#define PAD 8

static long int num_steps = 1000;
double step;

int main(){

	int i;
	double pi = 0.0, sum[NUM][PAD];

	step = 1.0 / (double) num_steps;

	double time1 = omp_get_wtime();

	#pragma omp parallel num_threads(NUM)
	{
		int j, num_id, num_threads;
		double x;
		num_threads = omp_get_num_threads();
		num_id = omp_get_thread_num();
		for(j = num_id, sum[num_id][0] = 0.0; j < num_steps; j += num_threads){
			x = (j + 0.5) * step;
			sum[num_id][0] += 4.0 / (1.0 + x * x);
		}
	}

	double time2 = omp_get_wtime();
	for(i = 0; i < NUM; i++)pi += step * sum[i][0];


	printf("\n%lf that's pi and the time was %lf\n", pi, time2 - time1);

	return 0;
}
