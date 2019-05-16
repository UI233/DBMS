#include "BufferManager.h"
#include <cstring>
using namespace BM;

BufferManager::BufferManager(){
    memset(ref_bits, 0, sizeof(ref_bits));
}

BufferManager::~BufferManager(){
}
