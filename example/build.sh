gcc server.c ../src/ipc_shmem.c ../src/ipc_flock.c -I../src -o srv 
gcc client.c ../src/ipc_shmem.c ../src/ipc_flock.c -I../src -o cli 
