/*
Scrivere un programma che una volta aperto un
file F in scrittura, genera altri N processi figli,
ognuno dei quali scrive su file F una stringa che lo
contraddistingue dagli altri processi (e.g. il suo
pid) per W volte.
Ognuno dei processi scrittori deve poter lavorare
in maniera esclusiva sull’intero file F, senza
interferire con gli altri scrittori (per poter ottenere
questo comportamento avrete bisogno di fcntl
che potete consultare sul man ed utilizzare quindi
il comando più adatto per il vosto scopo).
*/
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define W 4
#define N 5

static const char *filename = "file-7-03.txt";

void main(int argc, char **argv){

    int fd,len,status;
    pid_t pid, mypid;
    char buff[20];
    struct flock fl;


    if ((fd = open(filename, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO)) == -1) {
		printf("Unable to create and open file %s\n", filename);
		exit(-1);
	}

    for(int i=0; i<N; i++){
        pid=fork();
        if(pid==-1){
            printf("Unable to fork process number %d",i+1);
            exit(-1);
        }
        else if(pid==0){
            mypid=getpid();
            len = sprintf(buff,"My pid: %d\n",(int)mypid);

            /*
			 * Advisory Record Locking
			 * -----------------------
			 * Linux implementa un sistema UNIX recod lock per files
			 * come previsto dalle specifiche POSIX.
			 *
			 * Permette di definire ed utilizzare dei locks per un
			 * sotto-insieme di records del file o tutto il file.
			 *
			 * l_type = FWRLCK : richiede un write-lock sul file.
			 * l_type = F_UNLCK : richiede il rilascio del lock.
			 *
			 * l_whnce = SEEK_SET, l_start = 0, l_len = 0 : il lock
			 * è definito per tutti i records che vanno dall'inizio
			 * del file alla sua fine, indipendentemente da quanto
			 * questo possa crescere.
			 *
			 * F_SETLKW : richiede di settare il lock e, in caso fosse
			 * già acquisito, attende il suo rilascio.
			 */
			fl.l_type = F_WRLCK;
			fl.l_whence = SEEK_SET;
			fl.l_start = 0;
			fl.l_len = 0;
			fl.l_pid = 0;

            if (fcntl(fd, F_SETLKW, &fl) == -1) {  
				printf("Unable to lock file %s\n", filename);
				exit(-1);
			}

            for (i=0; i<W; i++) {
				if (write(fd, buff, (size_t)len) == -1) {
					printf("Unable to write on file\n");
				}
			}
            if (write(fd, "\n", 1) == -1) {
				printf("Unable to write on file\n");
			}

            fl.l_type = F_UNLCK;

            if (fcntl(fd, F_SETLKW, &fl) == -1) {  
				printf("Unable to unlock file %s\n", filename);
				exit(-1);
			}

			close(fd);
			exit(0);
        }        
    }
    for (int j = 0; j < N; j++) {
        if(wait(&status)==-1){
            printf("Wait has failed\n");
            exit(-1);
        }
    }
    close(fd);
    exit(0);

}