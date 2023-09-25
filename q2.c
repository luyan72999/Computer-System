#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int fd = open("./q2.txt", O_RDWR);
	pid_t pid = fork();	
	switch(pid){
		case -1:
			printf("Error: fork failed\n");
			exit(1);
		case 0:
			// child
			printf("Child access to file descriptor: %d\n", fd);
	    char* buffer_one = "I am child";
			write(fd, buffer_one, strlen(buffer_one));	
		default:
			// parent
			printf("Parent access to file descriptor: %d", fd);
	    char* buffer_two = "I am parent";
			write(fd, buffer_two, strlen(buffer_two));	
	}
}
