#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    
    char *buffer; 

    printf("Please type a string: ");

    scanf("%m[^\n]", &buffer);
    printf("String is in the Heap: %s \n",buffer);

    printf("Copying string in the Stack\n");
    int len = strlen(buffer);
    char stack_buff[len];
    strcpy(stack_buff,buffer);

    printf("...\n\n");

    free(buffer);

    printf("String deleted from Heap.\nString copied in the stack: %s\n", stack_buff);
}