#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "ipc_shmem.h"

#define MEM_SIZE 100

int exit_app = 0;

void signal_handler(int signal)
{
    printf("\n\nctrl + c : pressed\n");
    exit_app = 1;
    exit(0);
}

int main()
{
    char data[MEM_SIZE];
    int ret;
    signal(SIGINT, signal_handler);
    shmem_t *shmem;
    shmem = shmem_open("/tmp/test4.txt", MEM_SIZE);
    if(!shmem) return -1;

    while(1){
        if(exit_app) break;
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
