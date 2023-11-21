#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common_threads.h"

sem_t s; 

void *child(void *arg) {
    sleep(1);
    printf("child\n");
    // use semaphore here
    sem_post(&s); // signal: child is done
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    // init semaphore here
    sem_init(&s, 0, 0); // init semaphore to 0
    Pthread_create(&p, NULL, child, NULL);
    // use semaphore here
    sem_wait(&s); // wait for child to complete and signal
    printf("parent: end\n");
    return 0;
}

