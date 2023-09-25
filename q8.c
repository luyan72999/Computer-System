#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int fd[2];
	if (pipe(fd) == -1) {
		printf("pipe failed");
		exit(1);
	}
	pid_t pid_one = fork();
	if (pid_one == -1) {
		printf("Error: fork failed\n");
		exit(2);
	} else if (pid_one == 0) {
		close(fd[0]);
		int y = 5;
		if (write(fd[1],&y,sizeof(int)) == -1) {
			printf("Error writing");
			exit(3);
		}
		printf("Wrote to pipe: %d\n",y);
		close(fd[1]);
	} else {
		pid_t pid_two = fork();
		if (pid_two == -1) {

		} else if (pid_two == 0) {
			close(fd[1]);
			int x;
			if (read(fd[0],&x,sizeof(int)) == -1) {
				printf("Error reading");
				exit(4);
			}
			close(fd[0]);
			printf("The input from pipe: %d\n", x);
		} else {
			printf("This is parent process\n");
		}	
	}
}
