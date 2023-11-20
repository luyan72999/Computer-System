#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define NUMCPUS 4

int max_count = 1000000;
int number_of_thread = 1;
int THRESHOLD = 1024;

typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    int local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int threshold;
} counter_t;

void init(counter_t *c) {
    c->threshold = THRESHOLD;
    c->global = 0;
    pthread_mutex_init(& c->glock, NULL);
    for ( int i = 0; i < NUMCPUS; i++ ) {
        pthread_mutex_init(& c->llock[i], NULL);
    }
}

void update(counter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(& c->llock[cpu]);
    c->local[cpu] += amt;
    // only after local value >= threshold will update global value
    if ( c->local[cpu] >= THRESHOLD ) {
        pthread_mutex_lock(& c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(& c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(& c->llock[cpu]);
}

int get(counter_t *c) {
    pthread_mutex_lock(& c->glock);
    int val = c->global;
    pthread_mutex_unlock(& c->glock);
    return val;
}

void print_info(struct timeval tv_before, struct timeval tv_after, counter_t *c) {
    long long int expected_value = max_count * number_of_thread;
    long long int count_value = get(c);
    printf("Expected Value:\t\t %lld\n", expected_value);
    printf("Count Value:\t\t %lld\n", count_value);
    printf("Number of Threads:\t %d\n", number_of_thread);
    printf("Threshold:\t\t %d\n", THRESHOLD);
    // printf("Time Before:\t %ld%ld\t microseconds\n", tv_before.tv_sec, tv_before.tv_usec);
    // printf("Time After:\t %ld%ld\t microseconds\n", tv_after.tv_sec, tv_after.tv_usec);
    long long int time_used = (tv_after.tv_sec * 1000000 + tv_after.tv_usec) - (tv_before.tv_sec * 1000000 + tv_before.tv_usec);
    printf("Time Used:\t\t %lld\t\t microseconds\n", time_used);
}

void *run(void *ptr) {
    counter_t *c = (counter_t *)ptr;
    pthread_t threadID = pthread_self();
    for( int i = 0; i < max_count; i++ ) {
        update(c, threadID, 1);
    }
}

void test_simple_concurrent_approximate_counter() {
    struct timeval tv_before;
    struct timeval tv_after;

    pthread_t thread_list[number_of_thread];

    counter_t *c = (counter_t *)malloc(sizeof(counter_t));
    init(c);

    gettimeofday(&tv_before, NULL);

    for ( int i = 0; i < number_of_thread; i++ ) {
        pthread_create(& (thread_list[i]), NULL, run, (void *)c);
    }

    for ( int i = 0; i < number_of_thread; i++ ) {
        pthread_join(thread_list[i], NULL);
    }

    gettimeofday(&tv_after, NULL);

    print_info(tv_before, tv_after, c);
    free(c);
}

int main(int argc, char *argv[]) {
    printf("Q3: test_simple_concurrent_approximate_counter\n");
    if ( argc != 3 ) {
        printf("Usage:\n\t./a.exe  [number_of_thread]  [THRESHOLD]\n");
        return 0;
    }

    number_of_thread = atoi(argv[1]);
    THRESHOLD = atoi(argv[2]);
    test_simple_concurrent_approximate_counter();

    printf("\n");
    return 0;
}
