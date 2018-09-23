#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

double average;
double min;
double max;
int n;

void *calculateAverage(void *param);
void *findMin(void *param);
void *findMax(void *param);

int main(int argc, char *argv[]){
	n = argc - 1;

	// allocate memory
	double *input = (double*)malloc(n * sizeof(double));
	int i;
	for (i = 0; i < n; i ++){
		input[i] = atof(argv[i + 1]);
	}

	/*create thread*/
	pthread_t tid[3];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
	// arg is passed as the sole argument of start_routine()
	int error = 0;
	error = pthread_create(&tid[0], NULL, calculateAverage, (void*)input);
	if (error != 0){
		printf("Thread Creation Failed\n");
		exit(0);
	}
	error = pthread_create(&tid[1], NULL, findMin, (void*)input);
	if (error != 0){
		printf("Thread Creation Failed\n");
		exit(0);
	}
	error = pthread_create(&tid[2], NULL, findMax, (void*)input);
	if (error != 0){
		printf("Thread Creation Failed\n");
		exit(0);
	}

	int close;
	/*wait for children*/
	for (close = 2; close >= 0; close --){
		pthread_join(tid[close], NULL);
	}

	printf("average = %lf\n", average);
	printf("minimum = %lf\n", min);
	printf("maximum = %lf\n", max);

	return 0;
}

void *calculateAverage(void *param){
	double *arrayAverage = (double*)param;
	double sum = 0;
	int i;

	for (i = 0; i < n; i++){
		sum = sum + arrayAverage[i];
		}

	average = sum / n;

	pthread_exit(0);
}

void *findMin(void *param){
	double *arrayMin = (double*)param;

	int i,j;
	double temp;
	for (i = (n - 2); i >= 0; i --){
		for (j = 0; j <= i; j ++){
			if (arrayMin[j + 1] < arrayMin[j]){
				temp = arrayMin[j + 1];
				arrayMin[j + 1] = arrayMin[j];
				arrayMin[j] = temp;
				}
			}
		}

	min = arrayMin[0];

	pthread_exit(0);
}

void *findMax(void *param){	
	double *arrayMax = (double*)param;

	int i,j;
	double temp;
	for (i = (n - 2); i >= 0; i --){
		for (j = 0; j <= i; j ++){
			if (arrayMax[j + 1] < arrayMax[j]){
				temp = arrayMax[j + 1];
				arrayMax[j + 1] = arrayMax[j];
				arrayMax[j] = temp;
			}
		}
	}

	max = arrayMax[n - 1];

	pthread_exit(0);
}

