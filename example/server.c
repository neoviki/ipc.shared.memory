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
    printf("\n\nctrl+c pressed\n\n");
    exit_app = 1;
}

int main()
{
    shmem_t *shmem;
    signal(SIGINT, signal_handler);
    char data[MEM_SIZE]; 
    int i = 0;
    shmem = shmem_open("/tmp/test4.txt", MEM_SIZE);

    if(!shmem) return -1;

    while(1){
        if(exit_app) break;
        i= (i+1)%100;
        printf("SERVER WRITE ( %d )\n", i);
        snprintf(data, sizeof(data), "%d", i);
        shmem_write(&shmem, data, sizeof(data));
        sleep(1);
    }
    shmem_delete(&shmem);
    return 0;
}
