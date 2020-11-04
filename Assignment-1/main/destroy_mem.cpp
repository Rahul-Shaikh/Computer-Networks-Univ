#include <iostream>

#include "shared_mem.hpp"
using namespace std;

int main(void) {
    if (destroy_memory_block(FILENAME)) {
        cout << "Memory destroyed\n";
    } else {
        cout << "Couldn't destroy shared memory\n";
    }
    return 0;
}