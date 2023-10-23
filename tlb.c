#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {

	if (argc < 3) {
		exit(1);
	}
	
	// use clock_gettime with precision nanosecond
	struct timespec start;	
	struct timespec end;

	int total_pages = atoi(argv[1]);
	int trials = atoi(argv[2]);	
	int PAGESIZE = sysconf(_SC_PAGESIZE); // size of a page in bytes (>=1)
	int jump = PAGESIZE / sizeof(int);
	
	int* a = malloc(PAGESIZE * total_pages);

	clock_gettime(CLOCK_REALTIME, &start);
	for (int i = 0; i < trials; i++) {
		for (int j = 0; j < total_pages * jump; j+= jump) {
				a[j] += 1;				
		}
	}	
	clock_gettime(CLOCK_REALTIME, &end);
	
	// average page access time in nanoseconds
	long apat = (end.tv_sec * 1000000000 + end.tv_nsec - (start.tv_sec * 1000000000) - start.tv_nsec) / (trials * total_pages);
	
	printf("start: %ld, %ld\n", start.tv_sec, start.tv_nsec);	
  printf("end: %ld, %ld\n", end.tv_sec, end.tv_nsec);
	printf("Average page access time: %ld\n", apat);
	return 0;

}

