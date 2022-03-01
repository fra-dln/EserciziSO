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

int cons(void *shared_address, int semaphore){
    struct sembuf buf[1];

	buf[0].sem_num = 0;
	buf[0].sem_op = -1;
	buf[0].sem_flg = 0;

    if(semop(semaphore, buf, 1)==-1){
        printf("CAn't sync semaphore\n");
        return 0;
    }

    printf("Message from prod: %s\n", (char *) shared_address);

    buf[0].sem_num = 1;
	buf[0].sem_op = 1;
	buf[0].sem_flg = 0;
    
    if(semop(semaphore, buf, 1)==-1){
        printf("Can't sync semaphore \n");
        return 0;
    }
    return 1;
}

int main(int argc, char **argv){
    int ret, shm_ds,sem_ds;
    key_t shm_key, sem_key;
    void *shm_addr;

    shm_key=6969;
    sem_key=7878;
    
    shm_ds=shmget(shm_key, MEMSIZE,0);
    if(shm_ds==-1){
        printf("Can't get shared memory\n");
        return -1;
    }

    shm_addr=shmat(shm_ds, NULL, 0);
    if(shm_addr== (void *)-1){
        printf("Can't link shared memory\n");
        return -1;
    }

    sem_ds = semget(sem_key,2,0);
    if (sem_ds==-1){
        printf("Can't get semaphore \n%d",sem_ds);
        shmdt(shm_addr);
        return -1;
    }

    do{
        ret=cons(shm_addr,sem_ds);
    }while(ret);

    shmdt(shm_addr);
    return 0;
}