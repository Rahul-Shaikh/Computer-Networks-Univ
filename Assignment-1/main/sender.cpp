#include <iostream>
#include <cstdlib>
#include <cstring>
#include <semaphore.h>
#include <sys/ipc.h>

#include "shared_mem.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "USAGE: " << argv[0] << " \"Stuff you want to write\"" << endl;
        return -1;
    }

    sem_t* sem_sender = sem_open(SEM_SENDER_FNAME, 0);
    if (sem_sender == SEM_FAILED) {
        perror("sem_open/sender\n");
        exit(EXIT_FAILURE);
    }

    sem_t* sem_receiver = sem_open(SEM_RECEIVER_FNAME, 0);
    if (sem_receiver == SEM_FAILED) {
        perror("sem_open/receiver");
        exit(EXIT_FAILURE);
    }

    // grab the shared memory block
    byte_t* block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        cout << "ERROR: couldn't get the shared memory block\n";
        return -1;
    }

    for (int i = 0; i < 5; i++) {
        sem_wait(sem_receiver);
        cout << "Writing " << argv[1] << endl;
        memcpy(block, argv[1], BLOCK_SIZE);
        if (strcmp(block, "quit") == 0) break;
        sem_post(sem_sender);
    }
    // strncpy(block, argv[1], BLOCK_SIZE);

    detach_memory_block(block);
    sem_close(sem_receiver);
    sem_close(sem_sender);

    return 0;
}