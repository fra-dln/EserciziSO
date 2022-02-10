/*
Scrivere un programma per Windows/Unix che una volta mandato in esecuzione sia in grado
di creare ed attendere la terminazione di N threads in sequenza

(create(T0) → join(T0) → create(T1) → join(T1) → …)

in maniera tale che ogni thread T i sia affine alla CPU-core (i % #CPU ).
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CPUs 4

void *foo(void *args){
    char *retval;
    retval=strdup("Tutt'appò");
    sleep(5);

    pthread_exit((void *)retval);
}

int main(int argc, char **argv){
    pthread_t t; 
    pthread_attr_t attr;
    cpu_set_t cpus;
    void *exit;

    for(int i=0; i<CPUs;i++){
        if(pthread_attr_init(&attr)){
            printf("Unable to allocate attributes for thread %d",i);
            return 1;
        }

        CPU_ZERO(&cpus);
        CPU_SET(i, &cpus);
        
        if(pthread_attr_setaffinity_np(&attr,sizeof(cpu_set_t), &cpus)){
            printf("Unable to set thread %d affinity", i);
            return 1;
        }
        
        if(pthread_create(&t,NULL,foo,NULL)){
            printf("Unable to spawn thread %d",i);
            return 1;
        }
        
        if (pthread_attr_destroy(&attr)){
            printf("unable to destroy attributes of thread %d", i);
            return 1;
        }

        if(pthread_join(t,&exit)){
            printf("Unable to join thread %d",i);
            return 1;
        }

        printf("Joined with thread. Returned value was: %s.\n", (char *) exit);
		free(exit);

		sleep(2);
    }



    return 0;
}