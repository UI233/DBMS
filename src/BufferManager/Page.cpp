#include "Page.h"
#include <stdexcept>
#include <cstring>
using namespace BM;

Page::~Page() {
    if (is_open && dirty)
       forceWrite();
}

void Page::forceWrite() {
    dirty = false;
    if (!is_open)
        throw std::invalid_argument("Invalid page");
    auto & write = file.stream;

    if(!write.good())
        throw std::invalid_argument("Invalid page");

    write.seekp(page_index * PAGESIZE, write.beg);
    auto before = write.tellp();
    write.write((char *)&data[0], PAGESIZE);
    if (!write.good() || write.tellp() - before != PAGESIZE)
        throw std::runtime_error("Fail writting back");
}

void Page::close() {
    if (!is_open)
        throw std::invalid_argument("Invalid page");
    //if (pinned)
    //    throw std::invalid_argument("Pinned page");

    forceWrite();
    file.stream.close();
    is_open = false;
    pinned = false;
    dirty = false;
}

PageInfo Page::getInfo() const {
    if (!is_open)
        throw std::invalid_argument("Invalid page");

    return std::make_pair(page_index, file.path);
}

bool Page::read() {
    if (!file.stream.good())
        return false;

    auto &read = file.stream;
    read.seekg(page_index * PAGESIZE, read.beg);
    auto before = read.tellg();
    read.read((char *)&data[0], PAGESIZE);
    if (read.bad() || read.tellg() - before < PAGESIZE)
        return false;

    return true;
}

void Page::init(const std::string &path, unsigned int idx) {
    file.init(path);
    page_index = idx;
    is_open = read();
    dirty = false;
    pinned = true;
}

void Page::modify(char * pdata, int beg, int end) {
    if(beg < 0 || end > PAGESIZE)
        throw std::invalid_argument("Out of range");
    if (!is_open)
        throw std::invalid_argument("Invalid page");

    memcpy(&data[beg], pdata, end - beg);

    dirty = true;
}
