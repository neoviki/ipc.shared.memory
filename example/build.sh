gcc server.c ../src/shmem.c ../src/ipc_flock.c -I../src -o srv 
gcc client.c ../src/shmem.c ../src/ipc_flock.c -I../src -o cli 
