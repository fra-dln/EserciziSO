/*
Scrivere due programmi in C (produttore &
consumatore) che una volta agganciati alla stessa
memoria condivisa, operano su di essa in maniera
esclusiva tramite l’utilizzo di semafori (System V).
Più precisamente il consumatore dovrà attendere il
completamento della scrittura sulla memoria da parte del
produttore, che a sua volta attenderà il consumatore
affinchè abbia effettivamente completato la lettura.
Il produttore prende il dato da stdin, mentre il
consumatore stampa il dato a stdout.
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>

#define MEMSIZE 4096

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int production(void *shared_address, int semaphore){
    struct sembuf buf[1];

    buf[0].sem_num=1;
    buf[0].sem_op=-1;
    buf[0].sem_flg=0;

    if(semop(semaphore, buf, 1) == -1){
        printf("Can't sync semaphore\n");
        return 0;
    }

    printf("Message for the consumer: ");
    if(scanf("%[^\n]", (char *) shared_address)==0){
        *((char *)shared_address) = '\0';
    }
    getc(stdin);
 
    buf[0].sem_num=0;
    buf[0].sem_op=1;
    buf[0].sem_flg=0;
   
    if(semop(semaphore,buf,1)==-1){
        printf("Can't sync semaphore \n");
        return 0;
    }

    return 1;

    
}

int main(int argc, char **argv){
    
    key_t shm_key, sem_key;
    int shm_ds, sem_ds;
    void *shm_addr;

    union semun sem_arg;

    shm_key=6969;
    sem_key=7878;

    shm_ds=shmget(shm_key, MEMSIZE, IPC_CREAT|0666);
    if(shm_ds==-1){
        printf("Unable to allocate shared memory, exiting.\n");
        return -1;
    }

    shm_addr=shmat(shm_ds,NULL,0);
    if(shm_addr==(void *)-1){
        printf("Unable to link the shared memory\n");
        shmctl(shm_ds, IPC_RMID, NULL);
        return -1;
    }

    sem_ds=semget(sem_key,2,IPC_CREAT|0666);
    if(sem_ds==-1){
        printf("Unable to get semaphore, exiting\n");
        shmctl(shm_ds, IPC_RMID, NULL);
        shmdt(shm_addr);
        return -1;
    }

    sem_arg.val=0;
    if(semctl(sem_ds, 0, SETVAL, sem_arg)==-1){
        printf("Unable to init semaphore\n");
        semctl(sem_ds,-1,IPC_RMID,sem_arg);
        shmctl(shm_ds, IPC_RMID, NULL);
        shmdt(shm_addr);
        return -1;
    }

    sem_arg.val = 1;
    if((semctl(sem_ds, 1, SETVAL, sem_arg))==-1){
        printf("Unable to init semaphore\n");
        semctl(sem_ds,-1,IPC_RMID,sem_arg);
        shmctl(shm_ds, IPC_RMID, NULL);
        shmdt(shm_addr);
        return -1;
    }
    int ret;

    do{
        ret=production(shm_addr,sem_ds);
    }while(ret);
    
    semctl(sem_ds , -1 , IPC_RMID , sem_arg);
    shmctl(shm_ds, IPC_RMID, NULL);
    shmdt(shm_addr);
    return 0;
}