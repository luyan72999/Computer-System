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
			close(STDOUT_FILENO);
			printf("test");
		default:
	}

}
