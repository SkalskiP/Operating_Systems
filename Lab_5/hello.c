#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------
    
void *PrintHello(void *arg);
// ----------------------------------------------------------
    
int main(int argc, char *argv[]){
        pthread_t thread;
        int rc = pthread_create(&thread, NULL, PrintHello, NULL);
        if (rc){
            printf("Return code: %d\n", rc);
            exit(-1);
        }
        sleep(1);
        return 0;
}
// ----------------------------------------------------------
    
void *PrintHello(void *arg){
        printf("Next boring 'Hello World!' version!\n");
        return NULL;
}

