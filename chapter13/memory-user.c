#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// this program takes 1 argument: amount of megabyte it uses
int main(int argc, char* argv[]) {
	int pid = getpid();
	printf("Pid of this process is %d",pid);
	
	if (argc != 2) {
		printf("Error, one argument expected.");
		exit(1);
	}
	int user_mega = atoi(argv[1]);
	// i megabyte = 1000000 bytes
	int* int_array = (int*)malloc(user_mega * 1000000);
	while (1) {
		for (int i = 0; i < user_mega * 1000000 / 4; i++) {
			int_array[i] = 1;
		}
	}
	free(int_array);
	return 0;
}
