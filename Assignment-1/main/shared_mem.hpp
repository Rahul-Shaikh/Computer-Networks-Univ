#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include<iostream>
#include "constant.hpp"
using namespace std;

byte_t* attach_memory_block(string filename, int size);
bool detach_memory_block(byte_t* block);
bool destroy_memory_block(string filename);

#define FILENAME "sender.cpp"
#define BLOCK_SIZE 2048

#define SEM_SENDER_FNAME "/sem_sender"
#define SEM_RECEIVER_FNAME "/sem_receiver"

#endif