#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const char *filename = "testfile.txt";

 void main(int argc, char **argv){
     int fd;
     size_t len;
     pid_t pid;

     fd = open(filename, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO);
     if(fd==-1){
         printf("Unable to create and open file %s\n", filename);
         exit(-1);
    }
    
    pid = fork();
    if(pid == -1){
        printf("Unable to fork a new process\n");
        exit(-1);
    }

    if(pid==0){
        char *text;

        printf("Child: Write a message i will pass it to the parent process: ");
        if(scanf("%m[^\n]", &text) == -1){
            printf("Child scanf error");
            exit(-1);
        }
        printf("after scan\n");
        len = strlen(text);
        printf("%s\n",text);
        if(write(fd, text, len)==-1){
            printf("Unable to write on file\n");
            exit(-1);
        }
      
        free(text); close(fd); exit(len);
    }else{
        int aux; int status;
        if(wait(&status)==-1){
            printf("Wait as parent has failed");
            exit(-1);
        }else if ((aux = WEXITSTATUS(status)) == -1) {
			printf("Child process terminated with error\n");
			exit(-1);
		}
        len = (size_t) aux;

        char text[len+1];

        lseek(fd, 0, SEEK_SET);

        if(read(fd,text,len)==-1){
            printf("Unable to read file \n");
            exit(-1);
        }
        text[len]='\0';

        close(fd); 

        printf("Here is the child's message: %s", text);
        exit(0);
    }
 }