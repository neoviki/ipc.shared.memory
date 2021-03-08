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

shmem_t shmem_open(char *fname, size_t memory_size)
{
		shmem_t shmem;
		size_t total_memory_size;
		int key; /*unique key to create shared memory*/ 
		FILE *fp = NULL;

		shmem.id = -1;   

		if(!fname) goto SAFE_EXIT;

		if( access( fname, F_OK ) != 0 ){
				/*file doesn't exist, create*/
				printf("notice: file doesn't exist, create file (%s)\n", fname);

				fp  = fopen (fname, "w+");

				if(!fp){
						printf("error: creating file (%s)\n", fname);
						goto SAFE_EXIT;
				}	

				fclose(fp);
		}

		key = ftok(fname, __PROJ_ID__);
		if (key == -1) {
				printf("error: ftok \n");
				shmem.id = -2;   
				goto SAFE_EXIT;
		}

		shmem.memory_size = memory_size;
		total_memory_size = memory_size + sizeof(shmem_t);
		/*Create Shared Memory*/
		shmem.id = shmget(key, total_memory_size, IPC_CREAT|IPC_EXCL|666);

		/*Shared Memory already created - Open Shared Memory*/
		if(shmem.id < 0) shmem.id = shmget(key, total_memory_size, 666);

		if(shmem.id < 0){
				printf("error: shared memory create failed\n");
				shmem.id = -3;
				goto SAFE_EXIT;
		}

		shmem.memory = shmat(shmem.id, NULL, 0);

		if(shmem.memory == (char *)-1){
				printf("error: process unable to attach to shared memory\n");
				shmem.id = -4;
				goto SAFE_EXIT;
		}

SAFE_EXIT:
		return shmem;
}

int shmem_close(shmem_t *shmem)
{
		if(!shmem) return -1;
		/*Detach Shared Memory*/
		shmdt((void *) shmem-> memory);
		return 0;
}

int shmem_delete(shmem_t *shmem)
{
		if(!shmem) return -1;
		/*Remove shared memory*/
		shmctl(shmem->id, IPC_RMID, NULL); 
		shmem->id = -1;
		return 0;
}

void *shmem_read(shmem_t *shmem)
{
		void *data;
		if(!shmem) return NULL;
		if(!shmem->memory) return NULL;
		return shmem->memory;
}

int shmem_write(shmem_t *shmem, void *data, size_t size)
{
		if(!shmem) return -1;
		if(!shmem->memory) return -1;
		if(!data) return -1;
		if(shmem->id < 0) return -1;

		if(size > shmem->memory_size) return -1;
		
		memcpy(shmem->memory, data, size);
		return 0;
}

