#include "FileManager.h"

using namespace BM;
static char data[PAGESIZE];

void imp::FileManager::init(const std::string &path) {
    this->path = path;
    stream.close();
    stream.open(path, std::ios::in | std::ios::out | std::ios::binary);
    stream.seekg(0, stream.end);
    if (stream.tellg() < PAGESIZE) {
        stream.close();
        std::ofstream creator(path, std::ios::out | std::ios::binary);
        creator.write(data, PAGESIZE);
        creator.close();
        stream.open(path, std::ios::in | std::ios::out | std::ios::binary);
        page_num = 1;
    }
    else {
        page_num = stream.tellg() / PAGESIZE;
    }
}

imp::FileManager::FileManager(const std::string &path) {
    init(path);
}