/*
Scrivere un programma che esegue i seguenti
passi rispettando l’ordine
1) apre un file F in R/W e quindi mantiene il suo
descritore
2) fork-a un nuovo processo che ottiene un
mesaggio dall’utente da tastiera e lo scrive sul file
F
3) legge dal file F il messaggio cha ha scritto il
processo figlio e lo stampa sul terminale
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char **argv){

    pid_t pid;
    int exitStatus;
    int fd;
    char *letto;
    size_t count,ctrl;
    

    fd=open("testfile.txt",O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO);

    if (fd==-1){
        printf("Unable to create test file. Program will be shutted down\n");
        sleep(1);
        return 1;
    }
    
    pid=fork();
    if (pid==1){
        printf("Unable to fork.\n");
        return 2;
    }

    if (pid==0){
        char *buff;
        printf("Insert a message to be writed in the file\n");

        scanf("%m[\n]", &buff);

        printf("pre-write\n");
        if (write(fd, buff, strlen(buff)) == -1) {
			printf("Unable to write on file\n");
			exit(-1);
		}
        
        free(buff);
        close(fd);
        printf("Roger that! count = %d\n exiting child process\n",count);
        exit(0);
    }
    else{
        wait(&exitStatus);
        if(exitStatus==-1){
            return 3;
        }
        lseek(fd, 0, SEEK_SET);
        ctrl=read(fd,&letto,count);
        /*
        if(ctrl!=count){
            printf("Something went wrong in read process...\n");
            return 4;
        }*/
        close(fd);
        printf("%d\n",count);
        printf("%d\n",ctrl);
        printf("string readed from file: %s",letto);
    }

    return 0;
}