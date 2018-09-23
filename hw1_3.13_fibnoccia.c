#include <sys/types.h> 
#include <unistd.h> // Unix Standard
#include <stdio.h>
#include <stdlib.h>

int main(){

  // pid_t is used for process IDs and process group IDs
  pid_t pid;

  /*create a new process*/
  pid = fork();

  /*error occur*/
  if (pid < 0) {
    printf("Fork Failed\n");
    exit(-1);
  /*child process*/
  }else if (pid == 0) {
    
    int i = 0;
    int input = 0;
    printf("請輸入數列顯示個數：");
    scanf("%d", &input);
	while (input <= 0){
      printf("Please input a positive number.\n");
	  printf("請輸入數列顯示個數：");
      scanf("%d", &input);
    }

    int a[input];
    a[0] = 0;
    a[1] = 1;
    if (input > 0){

      int a1 = 0;
      int a2 = 1;
  	  int a3 = 0;
      for (i = 1 ; i < input - 1 ; i ++){
		a3 = a1 + a2;
        a[i + 1] = a3;

        a1 = a2;
        a2 = a3;
      }

      for (i = 0; i <= input - 1 ; i ++){
        printf("%d ", a[i]);
      }
	  printf("\n");

    }
  /*parent process*/
  }else { // p_id > 0
    wait(NULL); // wait for child process
    printf("Child Complete \n");
    exit(0); // complete
  }
}

