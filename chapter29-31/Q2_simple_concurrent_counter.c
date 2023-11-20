#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int max_count = 1000000;
int number_of_thread = 1;

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(& c->lock, NULL);
}

void increment(counter_t *c) {
    pthread_mutex_lock(& c->lock);
    c->value++;
    pthread_mutex_unlock(& c->lock);
}

void decrement(counter_t *c) {
    pthread_mutex_lock(& c->lock);
    c->value--;
    pthread_mutex_unlock(& c->lock);
}

int get(counter_t *c) {
    pthread_mutex_lock(& c->lock);
    int rc = c->value;
    pthread_mutex_unlock(& c->lock);
    return rc;
}

void print_info(struct timeval tv_before, struct timeval tv_after, counter_t *c) {
    long long int expected_value = max_count * number_of_thread;
    long long int count_value = get(c);
    printf("Expected Value:\t\t %lld\n", expected_value);
    printf("Count Value:\t\t %lld\n", count_value);
    printf("Number of Threads:\t %d\n", number_of_thread);
    // printf("Time Before:\t %ld%ld\t microseconds\n", tv_before.tv_sec, tv_before.tv_usec);
    // printf("Time After:\t %ld%ld\t microseconds\n", tv_after.tv_sec, tv_after.tv_usec);
    long long int time_used = (tv_after.tv_sec * 1000000 + tv_after.tv_usec) - (tv_before.tv_sec * 1000000 + tv_before.tv_usec);
    printf("Time Used:\t\t %lld\t\t microseconds\n", time_used);
}

void *run(void *ptr) {
    counter_t *c = (counter_t *)ptr;
    for( int i = 0; i < max_count; i++ ) {
        increment(c);
    }
}

void test_simple_concurrent_counter() {
    struct timeval tv_before;
    struct timeval tv_after;

    pthread_t thread_list[number_of_thread];

    counter_t *c = (counter_t *)malloc(sizeof(counter_t));
    init(c);

    gettimeofday(&tv_before, NULL);

    for ( int i = 0; i < number_of_thread; i++ ) {
        // pthread_create(thread_list + i, NULL, run, (void *)c);
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
    printf("Q2: test_simple_concurrent_counter\n");
    if ( argc != 3 ) {
        printf("Usage:\n\t./a.exe  [number_of_thread]  [max_count]\n");
        return 0;
    }

    number_of_thread = atoi(argv[1]);
    max_count = atoi(argv[2]);
    test_simple_concurrent_counter();

    printf("\n");
    return 0;
}
