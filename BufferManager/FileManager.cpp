#include "FileManager.h"

using namespace BM;
static char data[PAGESIZE];
BM::imp::FileManager::FileManager(const std::string &path) :
    stream(path, std::ios::in | std::ios::out | std::ios::binary),
    path(path){
    if (stream.tellg() == -1) {
        std::ofstream creator(path);
        creator.write(data, PAGESIZE);
    }
    stream.open(path, std::ios::in | std::ios::out | std::ios::binary);
    stream.seekg(0, stream.end);
    page_num = stream.tellg() / PAGESIZE;
    stream.seekg(stream.beg);
}