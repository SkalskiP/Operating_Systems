#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *PrintHello(void *arg);

int main(int argc, char *argv[]) {
    pthread_t thread[10];
    int rc = 0, i = 0;
    for (i = 0; i < 10; i++) {
        rc = pthread_create(&thread[i], NULL, PrintHello, (void *) &i);
        if (rc) {
            printf("Return code: %d\n", rc);
            exit(-1);
        }
    }
    for (i = 0; i < 10; i++) {
        pthread_join(thread[i], NULL);
    }
    printf("End of the main thread!\n");
    return 0;
}

void *PrintHello(void *arg) {
    sleep(1);
    printf("%d\n", *((int*) arg));
    printf("Next boring 'Hello World!' version!\n");
    return NULL;
}