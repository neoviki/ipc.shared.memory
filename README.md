## C/C++ IPC Shared Memory API 

Shared memory Library with internal read/write lock based on flock. 
This library is based on System V shared memory.

## Source 

   - src/shmem.c
   - src/shmem.h
   - src/ipc_flock.c
   - src/ipc_flock.h

## APIs

#####    Syntax:

		shmem_t *shmem_open(char *fname, size_t memory_size);

#####    Description:
	
		This function is used to create a shared memory segment or open an existing shared memory segment/
 
#####	Arguments:

	fname		: file name including full path, is used as a unique id to create shared memory. File will be created if 
				  the fille doesn't exist.

    memory_size : size of the shared memory.

	return		: success : memory address
				  failure : NULL

#####    Syntax:

	int shmem_close(shmem_t **shmem);

#####    Description:
	
		This function is used to close the shared memory segment.
	
#####	Arguments:

	shmem		: feed the address of shared memory variable returned from shmem_open()

	return		: success : 0
				  failure : -1


#####    Syntax:

	void *shmem_read(shmem_t **shmem, void *data, size_t size);

#####    Description:
	
		This function is used to read data from shared memory segment.
	
#####	Arguments:

	shmem		: feed the address of shared memory variable returned from shmem_open()

	data		: pointer to a buffer where the contents of shared memory is copied. 

	size 		: size of buffer ( size should be greater than or equal to shared memory size )


	return		: success : 0
				  failure : -1



#####    Syntax:

	int shmem_write(shmem_t **shmem, void *data, size_t size);

#####    Description:
	
		This function is used to write data to shared memory segment.
	
#####	Arguments:

	shmem		: feed the address of shared memory variable returned from shmem_open()

	data		: pointer to buffer. The contents of the buffer will be copied to shared memory

	size 		: size of buffer. ( The size should be less than or equal to shared memory size )

	return		: success : 0
				  failure : -1

#####    Syntax:

	int shmem_delete(shmem_t **shmem);	

#####    Description:

	Delete shared memory segment. No process can access shared memory after calling this function.


	shmem		: feed the shared memory variable returned from shmem_open()

	return		: success : 0
				  failure : <0




## Example Usage

	- example/client.c
	- example/server.c


