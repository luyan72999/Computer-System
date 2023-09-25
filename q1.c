#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int x = 100;
	pid_t pid = fork();	
	if (pid == -1) {
		printf("Error: fork failed\n");
		exit(1);
	} else if (pid == 0) {
		printf("x in child is %d\n",x);
		x = -10;
		printf("Child changed x to -10. Actual x is %d\n",x);
	} else {	
		printf("x in parent is %d\n",x);
		x = 10;	
		printf("Parent changed x to 10. Actual x is %d\n",x);
	}

}
