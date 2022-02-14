/*Scrivere due programmi server e client per ambiente
UNIX, tali per cui il processo-server utilizza una FIFO
predefinita (server_fifo) per leggere i messaggi scritti dal
processo-client.
Inoltre il processo-client è in grado di generare un
numero arbitrario (argomento del programma client) di
client-threads, ognuno dei quali utilizza una FIFO privata
(client_fifo_x) per leggere/scrivere in modo esclusivo
dal/al server.
A sua volta il processo-server delega un server-thread
apposito per comunicare con il client-thread che lo ha
richiesto per mezzo della FIFO di uso esclusivo di
quest’ultimo.*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

int main(int argc, char **argv){
    int nt;
    char *arg;
    char fifonamec[32];
    int fd;
    const char *fifonames = "server_fifo";

    if(argc<2){
        printf("Client recieved no arguments. Please execute with how many threads you want as argument");
        return(-1);
    }
    if(nt=atoi(argv[1])<1){
        printf("Can't execute client with less than one thread, retry.");
        return(-1);
    }

	pthread_t threads[nt];

    if(fd=open(fifonames, O_WRONLY)<0){
        printf("Unable to open %s client side", fifonames);
        return(-1);
    }

    

    return 0;
}