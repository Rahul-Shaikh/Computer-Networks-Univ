#include <iostream>
#include <cstdlib>
#include <cstring>

#include "shared_mem.hpp"

using namespace std;

int main(void) {
    
    // grab the shared memory block
    byte_t* block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        cout << "ERROR: couldn't get the shared memory block\n";
        return -1;
    }

    cout << "Reading: " << (char*)block << endl;
    detach_memory_block(block);
    return 0;
}