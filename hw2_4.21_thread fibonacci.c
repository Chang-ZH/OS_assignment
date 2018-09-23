#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 93

long fib_sequence[MAX_SIZE];

void *showFib(void *param);

int main(int argc, char *argv[]){
	int	size = atoi(argv[1]);

	/*create thread*/
	pthread_t tid;
	pthread_attr_t attr;

	if (argc != 2){
		fprintf (stderr, "Error: the number of the input is incorrect\n");
		return -1;
		}
	if (size < 1){
		fprintf (stderr, "Argument %d must be non-negative\n", atoi(argv[1]));
		return -1;
		}

	pthread_attr_init(&attr);

	int error = 0;
	// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
	// arg is passed as the sole argument of start_routine()
	error = pthread_create(&tid, &attr, showFib, (void*)argv[1]);
	if (error != 0){
		printf("Thread Creation Failed\n");
		exit(0);
		}

	/*wait for child*/
	pthread_join(tid, NULL);

	int i;
	for (i = 0; i < size; i++){
		printf("%ld ", fib_sequence[i]);
	}
	printf("\n");

	return 0;
	}

void *showFib(void *param){
	int n;
	n = atoi(param);

	fib_sequence[0] = 0;
	fib_sequence[1] = 1;

	int i;
	for (i = 2; i < n; i ++){
		fib_sequence[i] = fib_sequence[i - 2] + fib_sequence[i -1];
	}

	pthread_exit(0);
}
