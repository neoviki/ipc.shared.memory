/* Shared Memory Library	
 * 
 * 			
 * 			Author	: Viki (a) Vignesh Natarajan
 *			Contact	: vikiworks.io
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shmem.h"

shmem_t *shmem_open(char *fname, size_t memory_size)
{
		shmem_t *shmem = NULL;
		int key; /*unique key to create shared memory*/ 
		FILE *fp = NULL;


		if(!fname) return NULL;

		if( access( fname, F_OK ) != 0 ){
				/*file doesn't exist, create*/
				printf("notice: file doesn't exist, creating file (%s)\n", fname);

				fp  = fopen (fname, "w+");

				if(!fp){
						printf("error: creating file (%s)\n", fname);
						return NULL;
				}	

				fclose(fp);
		}

        shmem = (shmem_t*) calloc(1, sizeof(shmem_t));

        if(!shmem){
            printf("OOM\n");
            return NULL;
        }

		shmem->id = -1;   
        shmem->lockptr = ipc_flock_open(fname);
        if(shmem->lockptr == NULL){
            printf("error: ipc_flock_open(%s)\n", fname);
            free(shmem);
            return NULL;
        }

		key = ftok(fname, __APP_ID__);

		if (key == -1) {
				printf("error: ftok \n");
                free(shmem);
                return NULL;
        }

		shmem->memory_size = memory_size;

		/*Create Shared Memory*/
		shmem->id = shmget(key, shmem->memory_size, IPC_CREAT|IPC_EXCL|666);

		/*Shared Memory already created - Open Shared Memory*/
		if(shmem->id < 0) shmem->id = shmget(key, shmem->memory_size, 666);

		if(shmem->id < 0){
				printf("error: shared memory create failed\n");
                free(shmem);
				return NULL;
		}

		shmem->memory = shmat(shmem->id, NULL, 0);

		if(shmem->memory == (char *)-1){
				printf("error: process unable to attach to shared memory\n");
                free(shmem);
				return NULL;
		}

		return shmem;
}

int shmem_close(shmem_t **shmemp)
{
    if(!shmemp) return -1;

    shmem_t *shmem = *shmemp;

    if(!shmem) return -1;

    /*Detach Shared Memory*/
    shmdt((void *) shmem-> memory);

    if(shmem->lock_closed == 0){
        ipc_flock_close(shmem->lockptr);
        shmem->lock_closed = 1;
    }

    free(shmem);

    *shmemp = NULL;

    return 0;
}

int shmem_delete(shmem_t **shmemp)
{
    if(!shmemp) return -1;

    shmem_t *shmem = *shmemp;

    if(!shmem) return -1;
    /*Remove shared memory*/
    shmctl(shmem->id, IPC_RMID, NULL); 
    shmem->id = -1;

    if(shmem->lock_closed == 0){
        ipc_flock_close(shmem->lockptr);
        shmem->lock_closed = 1;
    }
    
    free(shmem);

    *shmemp = NULL;
    return 0;
}

int shmem_read(shmem_t **shmemp, void *data, size_t size)
{
    if(!shmemp) return -1;

    shmem_t *shmem = *shmemp;

    if(!shmem) return -1;
    if(!shmem->memory) return -1;
    if(!data) return -1;
    if(shmem->id < 0) return -1;
    if(size < shmem->memory_size) return -1;
    
    ipc_flock_lock(shmem->lockptr);
    memcpy(data, shmem->memory, shmem->memory_size);
    ipc_flock_unlock(shmem->lockptr);
    
    return 0;
}

int shmem_write(shmem_t **shmemp, void *data, size_t size)
{
    if(!shmemp) return -1;

    shmem_t *shmem = *shmemp;

    if(!shmem) return -1;
    if(!shmem->memory) return -1;
    if(!data) return -1;
    if(shmem->id < 0) return -1;
    if(size > shmem->memory_size) return -1;

    ipc_flock_lock(shmem->lockptr);
    memcpy(shmem->memory, data, size);
    ipc_flock_unlock(shmem->lockptr);

    return 0;
}

