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
    char *data = NULL;
    shmem_t shmem;
    shmem = shmem_open("/tmp/test4.txt", 100);
    if(shmem.id<0) return -1;
    while(1){
    	data = shmem_read(&shmem);
	if(data){
	    printf("CLIENT READ ( %s )\n", data);
	    data = NULL;
	}
	sleep(1);
     }

    shmem_close(&shmem);
    return 0;
}
