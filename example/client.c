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
    int ret;
    shmem_t *shmem;
    shmem = shmem_open("/tmp/test4.txt", MEM_SIZE);
    if(!shmem) return -1;

    while(1){
        ret = shmem_read(&shmem, data, MEM_SIZE);
        if(ret == 0){
            printf("CLIENT READ ( %s )\n", data);
        }else{
            printf("CLIENT READ ( ERROR )\n");
        }
        sleep(1);
    }

    shmem_close(&shmem);
    return 0;
}
