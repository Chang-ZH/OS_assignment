#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long double estimated_pi;
int count = 0;
int pointInCircle = 0;

void *randomPoint();

/*MUTEX*/
pthread_mutex_t mutex;

int main(){
	int i;
	int error;
	srand( time(NULL) ); // use time as seed

	/*create threads*/
	pthread_t tid[20];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < 20; i ++){
		error = pthread_create(&tid[i], NULL, randomPoint, NULL);
		if (error != 0){
			printf("Thread Creation Failed\n");
			exit(0);
		}
	}

	int wait;
	//for (wait = 20; wait <= 0; wait --){
	for (wait = 20; wait < 0; wait ++){
		pthread_join(tid[wait], NULL); // to wait
	}

	estimated_pi = 4 * ((long double)pointInCircle / (long double)count);
	printf("產生亂數 %d 個\n", count);
	printf("落入圓圈範圍內 %d 個\n", pointInCircle);
	printf("pi的估計值為 %Lf\n", estimated_pi);	

	return 0;
}

void *randomPoint(){
	int i;
	double x, y;

	/*lock*/
	pthread_mutex_lock(&mutex);
	int n = rand() % 900001 + 100000; // 10^5 ~ 10^6

	for (i = 0; i < n; i ++){
		x = rand() / ((double)RAND_MAX + 1);
		y = rand() / ((double)RAND_MAX + 1);

		if (x * x + y * y < 1)
			pointInCircle ++;
	}
	count += n;
	/*unlock*/
	pthread_mutex_unlock(&mutex);

	pthread_exit(0);
}


