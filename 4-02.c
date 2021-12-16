#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*Scrivere un programma per Unix che sia in grado
di generare due Thread T 1 e T 2 , tali per cui:

T 1 chiede all’utente di inserire una messaggio da
tastiera

T 2 scrive il messaggio ottenuto dall’utente a
schermo

con la condizione che non si possono utilizzare
variabili globali.
*/

void *read(void *arg){
    char *buff;

	printf("\n stringame tutto baby: ");
	scanf("%m[^\n]", &buff);

	pthread_exit((void *) buff);

}

void *print(void *arg){
    char *buff;

    if ((buff = (char *) arg) == NULL)
		pthread_exit((void *) 1);
    else
        printf("\n\n bella stringata zi: %s\n\n", buff);
    pthread_exit((void *) 0);    
}

int main (int argc, char **argv){

    void *buff;
    void *exit_status;
    pthread_t t;

    if (pthread_create(&t, NULL, read, NULL))
	{
		printf("Unable to create thread for executing foo1. Exit.\n");
		return 1;
	}

	if (pthread_join(t, &buff))
	{
		printf("Unable to join thread executing foo1. Exit.\n");
		return 1;
	}

	if (pthread_create(&t, NULL, print, buff))
	{
		printf("Unable to create thread for executing foo2. Exit.\n");
		return 1;
	}

	if (pthread_join(t, &exit_status))
	{
		printf("Unable to join thread executing foo2. Exit.\n");
		return 1;
	}

	free(buff);

    return 0;
}