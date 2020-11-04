#include <iostream>
#include <cstdlib>
#include <cstring>

#include "shared_mem.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "USAGE: " << argv[0] << " \"Stuff you want to write\"" << endl;
        return -1;
    }

    // grab the shared memory block
    byte_t* block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        cout << "ERROR: couldn't get the shared memory block\n";
        return -1;
    }

    cout << "Writing " << argv[1] << endl;
    memcpy(block, argv[1], BLOCK_SIZE);
    // strncpy(block, argv[1], BLOCK_SIZE);

    detach_memory_block(block);

    return 0;
}