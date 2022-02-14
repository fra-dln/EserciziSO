/*
Scrivere un programma in ambiente UNIX che,
utilizzando le funzioni messe a disposizione dalla
libreria stdio:
• apre gli streams per un file sorgente e per un
file destinazione (può essere creato all’atto
dell’apertura);
• legge il contenuto dal file sorgente;
• filtra tutte e sole le parole di lunghezza
superiore a 6 caratteri;
• scrive quest’ultime nel file di destinazione.
*/
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const char *destination = "destination-7-06.txt";
static const char *source = "source-7-06.txt";

void main (int argc, char **argv){
    FILE *dest;
    FILE *src;

    if(dest=fopen(destination, "w") == NULL){
        printf("Unable to open destination file\n");
        exit(-1);
    }

     if(src=fopen(source, "r") == NULL){
        printf("Unable to open source file\n");
        exit(-1);
    }

    



        }