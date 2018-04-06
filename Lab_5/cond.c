#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------
    
#define MAXVAL 100
    
int globalvariable = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;
    
void* increment(void*);
void* printinfo(void*);
// ----------------------------------------------------------
    
int main(){
    
        pthread_t t1, t2, t3;
        pthread_attr_t attr;
    
        // mutex initialization
        pthread_mutex_init(&mutex, NULL);
    
        // conditional initialization
        pthread_cond_init(&cond, NULL);
    
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
        pthread_create(&t1, &attr, increment, NULL); 
        pthread_create(&t2, &attr, increment, NULL);
        pthread_create(&t3, &attr, printinfo, NULL);  
    
        pthread_join(t1, NULL);
        printf("t1 finished!\n");
        pthread_join(t2, NULL);
        printf("t2 finished!\n");
        pthread_join(t3, NULL);
        printf("t3 finished!\n");
    
        printf("Finishing...\n");
        return 0;
}
// ----------------------------------------------------------
    
void* increment(void* arg) {
        pthread_exit((void*) 0);
}
// ----------------------------------------------------------
    
void* printinfo(void* arg) {
        pthread_exit((void*) 0);
}
// ----------------------------------------------------------

