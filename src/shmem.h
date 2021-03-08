/* Shared Memory Library	
 * 
 * 			
 * 			Author	: Viki (a) Vignesh Natarajan
 *			Contact	: vikiworks.io
 */

#ifndef SHMEM_H
#define SHMEM_H 
#define  __PROJ_ID__  100 /*Any non zero number. Can be any number*/

typedef struct{
	int id;
	int memory_size;
	void *memory;
}shmem_t;

shmem_t shmem_open(char *fname, size_t memory_size);

int shmem_close(shmem_t *shmem);

void *shmem_read(shmem_t *shmem);
int shmem_write(shmem_t *shmem, void *data, size_t size);

/*Delete shared memory segment. No process can access shared memory*/
int shmem_delete(shmem_t *shmem);

#endif
