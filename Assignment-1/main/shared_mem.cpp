#include <iostream>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "shared_mem.hpp"

#define IPC_RESULT_ERROR (-1)

using namespace std;

static int get_shared_block(string filename, int size) {
    key_t key;
    
    // Request a key which is linked to the filename
    key = ftok(filename.c_str(), size);
    if (key == IPC_RESULT_ERROR) {
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0644 | IPC_CREAT);
}



byte_t* attach_memory_block(string filename, int size) {
    int shmid = get_shared_block(filename, size);

    if (shmid == IPC_RESULT_ERROR) return NULL;
    byte_t* result;

    result = (byte_t*) shmat(shmid, NULL, 0);
    if (result == NULL) return NULL;

    return result;
}



bool detach_memory_block(byte_t* block) {
    return (shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory_block(string filename) {
    int shmid = get_shared_block(filename, 0);
    
    if (shmid == IPC_RESULT_ERROR) return false;

    return shmctl(shmid, IPC_RMID, NULL) != IPC_RESULT_ERROR;
}


