#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h> // Unix Standard
#include <stdlib.h>
#include <string.h>

#define MAX_SEQUENCE 10

typedef struct {
  long fib_sequence[MAX_SEQUENCE];
  int sequence_size;
}shared_data;

int main(){

  shared_data fib;
  printf("請輸入數列顯示個數：");
  scanf("%d", &fib.sequence_size);

  while (fib.sequence_size > MAX_SEQUENCE || fib.sequence_size <= 0){

	if (fib.sequence_size > MAX_SEQUENCE){
	  printf("The number of the  input is too more.\n");  
	  printf("請輸入數列顯示個數：");
	  scanf("%d", &fib.sequence_size);
    }else{		
      printf("Please input a positive number.\n");
	  printf("請輸入數列顯示個數：");
	  scanf("%d", &fib.sequence_size);
	}
  }

  if (fib.sequence_size > 0 && fib.sequence_size <= MAX_SEQUENCE){
 
    /*idntfier*/
    int segment_id;

    /*pointer*/
    char* shared_memory;

    /*sharded memory segment size*/
    int segment_size;
    printf("請輸入sharded memory segment size: ");
    scanf("%d", &segment_size);

    /*allocate a segment*/
    segment_id = shmget(IPC_PRIVATE, segment_size, S_IRUSR | S_IWUSR);

    /*attach to shm*/
    shared_memory = (char*) shmat(segment_id, NULL, 0);

    /*Create Child Process*/
    pid_t pid;
    pid = fork(); /*create a new process*/

    if (pid < 0) { /*error occur*/
      printf("Fork Failed\n");
      exit(-1);
    }else if (pid == 0) { /*child process*/

      int i = 0;
      int a1 = 0;
	  int a2 = 1;

	  int a3 = 0;
	  fib.fib_sequence[0] = 0;
	  fib.fib_sequence[1] = 1;
	  for(i = 1; i < fib.sequence_size-1; i ++){
		a3 = a1 + a2;
		fib.fib_sequence[i+1] = a3;

		a1 = a2;
		a2 = a3;
	  }
	  /*message to the shm*/
	  for(i = 0; i < fib.sequence_size; i ++){	
		sprintf(shared_memory + 4 * i , "%ld ", fib.fib_sequence[i]);
	  }

	  /*detach shm*/
	  shmdt(shared_memory);

	  /*remove*/
	  shmctl(segment_id, IPC_RMID, NULL);
	}else { /*praent process*/

	  wait(NULL);
	  printf("Child Complete\n");

	  /*output the result*/
	  int i;
	  for(i = 0; i < fib.sequence_size; i ++){	
		printf("%s", shared_memory + 4 * i);
	  }
	  printf("\n");

	  /*detach shm*/
	  shmdt(shared_memory);

	  /*remove*/
	  shmctl(segment_id, IPC_RMID, NULL);
	  exit(0);
	}
  }
}
