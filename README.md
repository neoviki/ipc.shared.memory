## C/C++ IPC Shared Memory API 

Simplified Shared memory Library. This library is a wrapper to System V shared memory.

## Source 

   - src/shmem.c
   - src/shmem.h


## APIs

#####    Syntax:

		shmem_t shmem_open(char *fname, size_t memory_size);

#####    Description:
	
		This function is used to create a shared memory segment or open an existing shared memory segment/
 
#####	Arguments:

	fname		: file name including full path, is used as a unique id to create shared memory. File will be created if 
				  the fille doesn't exist.

    memory_size : size of the shared memory.

	return		: success : a valid (shmem_t).id > 0 and (shmem_t).memory != NULL
				  failure : return (shmem_t).id < 0;

#####    Syntax:

	int shmem_close(shmem_t *shmem);

#####    Description:
	
		This function is used to close the shared memory segment.
	
#####	Arguments:

	shmem		: feed the shared memory variable returned from shmem_open()

	return		: success : 0
				  failure : -1


#####    Syntax:

	void *shmem_read(shmem_t *shmem);

#####    Description:
	
		This function is used to read data from shared memory segment.
	
#####	Arguments:

	shmem		: feed the shared memory variable returned from shmem_open()

	return		: success : Pointer to shared memory data
				  failure : NULL



#####    Syntax:

	int shmem_write(shmem_t *shmem, void *data, size_t size);

#####    Description:
	
		This function is used to write data to shared memory segment.
	
#####	Arguments:

	shmem		: feed the shared memory variable returned from shmem_open()

	data		: pointer to data to be writted into shared memory

	size 		: size of data

	return		: success : 0
				  failure : < 0

#####    Syntax:

	int shmem_delete(shmem_t *shmem);	

#####    Description:

	Delete shared memory segment. No process can access shared memory after calling this function.


	shmem		: feed the shared memory variable returned from shmem_open()

	return		: success : 0
				  failure : <0




## Example Usage

	- example/example_nolock
    - The example doesn't have any lock. It is the responsibility of the application programmer to use locks to synchronize shared resource.


