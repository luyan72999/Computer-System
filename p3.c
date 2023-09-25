#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	printf("hello world (pid: %d)\n", (int) getpid());
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed.\n");
		exit(1);
	} else if (rc == 0) {	
		printf("hello, I am a child (pid: %d)\n", (int) getpid());
		char* myargs[3];
		myargs[0] = strdup("wc");   // strdup() returns a pointer to the duplicated string
		myargs[1] = strdup("p3.c");
		myargs[2] = NULL;           // marks end of array
		execvp(myargs[0],myargs);
		 // execvp pass the control to the command line
		// the first param is the command to execute, the second param is the list of args to the command line
 		printf("this shouldn't be printed\n");
	} else {
		int rc_wait = wait(NULL); // block the current process until the child exit
		// by passing NULL, we specify that no exit code of child is wanted
		// this call only returns when child sucessfully finished	
 		printf("hello, I'm parent of pid %d (rc_wait: %d), my pid is %d\n", rc, rc_wait, (int) getpid());
	}	
	return 0;
}
