#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shmem.h"

#define MEM_SIZE 100
int main()
{
    char data[MEM_SIZE]; 
    int i = 0;
    shmem_t *shmem;
    shmem = shmem_open("/tmp/test4.txt", MEM_SIZE);

    if(!shmem) return -1;

    while(1){
        i= (i+1)%100;
        printf("SERVER WRITE ( %d )\n", i);
        snprintf(data, sizeof(data), "%d", i);
        shmem_write(&shmem, data, sizeof(data));
        sleep(1);
    }
    shmem_delete(&shmem);
    return 0;
}
