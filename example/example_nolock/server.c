#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shmem.h"

int main()
{
    char data[64]; 
    int i = 0;
    shmem_t shmem;
    shmem = shmem_open("/tmp/test4.txt", 100);
    if(shmem.id<0) return 0;
    while(1){
        i= (i+1)%100;
        printf("SERVER WRITE ( %d )\n", i);
        snprintf(data, sizeof(data), "%d", i);
        shmem_write(&shmem, data, sizeof(data));
        sleep(1);
    }
    shmem_close(&shmem);
    shmem_delete(&shmem); 
    return 0;
}
