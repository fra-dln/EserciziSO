/*
Scrivere un programma in C che prende
inizialmente N (a piacere) stringhe rappresentanti
N directory corrette, e che fork-a quindi N processi
che andranno a stampare ognuno il contenuto di
una directory differente.
Il processo padre termina dopo i processi figli (non
serve la verifica).
(Hint: è necessario utilizzare execlp)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 4

int main(int argc, char **argv){

    char path[N][512];
    pid_t pid;
	int status, count = 0;

    for (int i = 0; i < N; i++)
    {
        printf("Insert Path: ");
        scanf("%s", path[i]);
        printf("\n");
    }

    for (int i = 0; i < N; i++)
    {
        pid= fork();
        if(pid<0){printf("cant fork\n"); exit(-1);}
        
        else if(pid==0){//processo figlio
            printf("Hi! i'm a kiddo");
            execlp("ls", "ls", path[i], NULL);
			exit(0);
        }
        else{
            count++;
        } 
    }
    
    for (int i=0; i<count; i++){
		wait(&status);
	}
    
    return 0;
}