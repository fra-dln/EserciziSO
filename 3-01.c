/*Scrivere un programma in C che prende
inizialmente una stringa da input (può contenere
anche spazi bianchi) e la salva in un buffer, per
poi fork-are un processo figlio che manda in
stampa la stessa stringa acquisita dal processo
padre.
In più è richiesto che il processo padre termini
solo dopo che il processo figlio ha terminato
(verificare che tale ordine è rispettato stampando i
PID dei processi).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){

    char *buffer;
    printf("Pls gimme a string: ");
    scanf("%m[^\n]", &buffer);
    printf("\nGiven String: %s\n",buffer);

    pid_t pid=fork(); int status;

    if(pid<0){printf("Can't Fork"); return 0;}
    if(pid==0){
        //processo figlio
        printf("Hi! I'm Child! This is my pid: %d\n",getpid());
        printf("Here is my father's string: %s\nByeBye\n",buffer);
        exit(0);
    }
    else{
        //processo padre
        wait(&status);
        printf("Hi I'm father, this is my pid: %d", getpid());
        exit(0);
    }
  
    return 0;
}