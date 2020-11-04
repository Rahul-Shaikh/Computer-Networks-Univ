#include <iostream>
#include <cstdlib>
#include <cstring>
#include <semaphore.h>
#include <sys/ipc.h>

#include "shared_mem.hpp"

using namespace std;

int main(void) {

    // unlink any semaphore with same name
    sem_unlink(SEM_SENDER_FNAME);
    sem_unlink(SEM_RECEIVER_FNAME);

    // create semaphore
    sem_t* sem_sender = sem_open(SEM_SENDER_FNAME, IPC_CREAT, 0660, 0);
    if (sem_sender == SEM_FAILED) {
        perror("sem_open/sender\n");
        exit(EXIT_FAILURE);
    }


    sem_t* sem_receiver = sem_open(SEM_RECEIVER_FNAME, IPC_CREAT, 0660, 1);
    if (sem_receiver == SEM_FAILED) {
        perror("sem_open/receiver\n");
        exit(EXIT_FAILURE);
    }

    
    // grab the shared memory block
    byte_t* block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        cout << "ERROR: couldn't get the shared memory block\n";
        return -1;
    }


    while (true) {
        sem_wait(sem_sender);
        if (strlen((char*)block)) {
            cout << "Reading: " << (char*)block << endl;
            bool done = (strcmp("quit", block) == 0);
            block[0] = 0;
            if (done) break;
        }
        sem_post(sem_receiver);
    }
    detach_memory_block(block);
    sem_close(sem_receiver);
    sem_close(sem_sender);
    return 0;
}