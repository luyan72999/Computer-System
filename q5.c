#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	pid_t pid = fork();	
	switch(pid){
		case -1:
			printf("Error: fork failed\n");
			exit(1);
		case 0:
			pid_t rc_wait = wait(NULL);
			printf("rc_wait in child is %d\n",rc_wait);
		default:
		  int rc_wait_p = wait(NULL);
			printf("rc_wait in parent is %d\n",rc_wait_p);
	}

}
