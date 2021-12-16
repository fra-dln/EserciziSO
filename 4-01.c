#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

/*Scrivere un programma per Windows/Unix che
permette al processo principale P di create un
nuovo thread T il cui percorso di esecuzione è
associato alla funzione “thread_function”.
Il processo principale P ed il nuovo thread T
dovranno stampare ad output una stringa che li
identifichi rispettando l’ordine T→P, senza
utilizzare
“WaitForSingleObject”/“pthread_join”,
ma sfruttando un concetto fondamentale che
accomuna tutti i threads di un determinato
processo.*/

unsigned int shared = 1;

void *thread_function(void* arg){
    printf("2. child executing\n");
    sleep(3);
    printf("3. child terminating. Bye!\n");
    shared= 0;
    pthread_exit(NULL);
}

int main (int argc, char **argv){
    pthread_t child_t;

    printf("1. parent executing \n");

    int result = pthread_create(&child_t,NULL, thread_function, NULL);
    
    if(result!=0){
        printf("unable to create child thread");
        return 1;
    }else{
        while(shared); 
        printf("4. heyo parent terminating fuck u all \n");
    }

    return 0;
}























