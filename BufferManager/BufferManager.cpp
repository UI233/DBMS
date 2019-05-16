#include "BufferManager.h"

using namespace BM;

BufferManager::BufferManager(){

}

BufferManager::~BufferManager(){
    for(auto &page: pool){
        unsigned int idx = page.second;
        pages[idx].close();
    }

}