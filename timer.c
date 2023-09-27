#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
	struct timeval current_time_one;	
	struct timeval current_time_two;
	int fd = open("empty.txt", O_RDONLY);
	char buffer[0];	
	int counter = 100;
	gettimeofday(&current_time_one, NULL);
	
	while (counter > 0) {	
		read(fd,buffer,0);
		counter--;
	}
	gettimeofday(&current_time_two, NULL);
	close(fd);
	printf("time start 100 read: %li s, %li ms\n", current_time_one.tv_sec,current_time_one.tv_usec);	
	printf("time end 100 read: %li s, %li ms\n", current_time_two.tv_sec,current_time_two.tv_usec);
	return 0;
}
