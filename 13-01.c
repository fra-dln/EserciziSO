/*
Scrivere un programma in C in ambiente UNIX che permette a due processi P1 e P2 di scrivere a
standard output (stdout) in STRETTA ALTERNANZA.
La coordinazione tra i due processi P1 e P2 deve
essere effettuata per mezzo di appositi segnali
(e.g. SIGUSR1) al fine di comunicare al processo
concorrente la terminazione della propria attività e
dare ad esso la possibilità di effettuare la sua
propria.
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

pid_t pid1;
pid_t pid2;

void handler(int sig){
    
    exit(0);
}

int main(int argc, char **argv){
    sigset_t set;
    sigset_t oldSet;
    struct sigaction act;
    struct sigaction oldAct;

    memset((void *)&act, 0 ,sizeof(struct sigaction));

    if(sigfillset(&set)==-1){
        printf("error on sigfillset");
        exit(-1);
    }
    if(sigprocmask(SIG_BLOCK, &set, &oldSet)==-1){
        printf("error on sigprocmask");
        exit(-1);
    }

    act.__sigaction_handler = handler;
    act.sa_mask = set;
    if(sigaction(SIGUSR1, &act, &oldAct)==-1){
        printf("error on sigaction");
        exit(-1);
    }

    if(sigemptyset(&set)==-1){
        printf("error on sigemptyset");
        exit(-1);
    }
    if(sigaddset(&set, SIGUSR1)==-1 && sigaddset(&set, SIGINT)==-1){
        printf("error on sigaddset");
        exit(-1);
    } 
    if(sigprocmask(SIG_UNBLOCK, &set, NULL)==-1){
        printf("error on sigprocmask");
        exit(-1);
    }


    return 0;
}