/* Shared Memory Library	
 * 
 * 			
 * 			Author	: Viki (a) Vignesh Natarajan
 *			Contact	: neoviki.com
 */

#ifndef SHMEM_H
#define SHMEM_H 
#include "ipc_flock.h"
#define  __APP_ID__  100 /*Can be any number greater than 0*/

typedef struct{
	int id;
	int memory_size;
	void *memory;
    ipc_flock_t *lockptr;
    int lock_closed;
}shmem_t;

shmem_t *shmem_open(char *fname, size_t memory_size);

/*shmem_delete() should not be called if shmem_close() is called*/
int shmem_close(shmem_t **shmem);

int shmem_read(shmem_t **shmemp, void *data, size_t size);
int shmem_write(shmem_t **shmem, void *data, size_t size);

/*Delete shared memory segment. No process can access shared memory*/
/*shmem_close() should not be called if shmem_delete() is called*/
int shmem_delete(shmem_t **shmem);

#endif
