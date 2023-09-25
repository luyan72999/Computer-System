#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	// create a pipe before creating any child
	// declare the array of the 2 file descriptors
	int fd[2];
	// after calling pipe, fd should contains 2 file descriptors, 0 for read, 1 for write
	if (pipe(fd) == -1) {
		printf("pipe failed");
		exit(1);
	}
	pid_t pid = fork();	
	if (pid == -1) {
		printf("Error: fork failed\n");
		exit(2);
	} else if (pid == 0) {
		printf("Hello\n");
		// close the read file for security
		close(fd[0]);
		// write to the virtual file (pipe)
		int y = 5;
		if (write(fd[1],&y,sizeof(int)) == -1) {
			printf("Error writing");
			exit(3);
		}
		// close the write end
		close(fd[1]);
	} else {	
		// close the write file for security
		close(fd[1]);
		int x;
		// read from vitual file
		// sychronization: this process will wait until it gets the written signal from 
		// the other end of pipe
		if (read(fd[0],&x,sizeof(int)) == -1) {
			printf("Error reading");
			exit(4);
		}
		printf("Good bye\n");
	}

}
