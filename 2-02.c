#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFF 151

int main(int argc, char *argv[]){

    if(strlen(argv[1])>MAX_BUFF){
        printf("max length supported is %d characters. Max lenght exceeded\n", MAX_BUFF);
        return 0;
    }
    char buff[MAX_BUFF];
    strcpy(buff,argv[1]);
    printf("original string: %s\n", buff);

    char aux;
    int len=strlen(buff);
    for (int i = 0; i < len/2; i++)
    {
        aux=buff[len-i-1];
        buff[len-i-1]=buff[i];
        buff[i]=aux;
    }
       
    printf("Inverted string: %s\n",buff);

    return 0;
}