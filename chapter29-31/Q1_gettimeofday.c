#include <sys/time.h>
#include <stdio.h>

void test_gettimeofday() {
    struct timeval tv_before;
    struct timeval tv_after;

    gettimeofday(&tv_before, NULL);

    for( int i = 0; i < 100000000; i++ ) {}

    gettimeofday(&tv_after, NULL);

    printf("before:\t %ld. %ld\n", tv_before.tv_sec, tv_before.tv_usec);
    printf("after:\t %ld. %ld\n", tv_after.tv_sec, tv_after.tv_usec);
    return 0;
}

int main() {
    // Q1
    test_gettimeofday();

    return 0;
}