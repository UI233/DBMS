#include "Page.h"
#include <stdexcept>
using namespace BM;

Page::~Page() {
    if (is_open && dirty)
        forceWrite();
}

void Page::forceWrite() {
    dirty = false;
    if (!is_open)
        throw std::invalid_argument("Invalid page");
    if (file.use_count() == 0)
        throw std::invalid_argument("Invalid page");
    auto & write = file->stream;

    if(!write.good())
        throw std::invalid_argument("Invalid page");

    write.seekp(0, page_index * PAGESIZE);
    auto before = write.tellp;
    write.write((char *)&data[0], PAGESIZE);
    if (!write.good() || write.tellp() - before != PAGESIZE)
        throw std::runtime_error("Fail writting back");
}

void Page::close() {
    if (!is_open)
        throw std::invalid_argument("Invalid page");
    if (pinned)
        throw std::invalid_argument("Pinned page");

    forceWrite();
    file.reset();
    is_open = false;
    pinned = false;
    dirty = false;
}

PageInfo Page::getInfo() const {
    if (!is_open || file.use_count() == 0)
        throw std::invalid_argument("Invalid page");

    return std::make_pair(page_index, file->path);
}

bool Page::read() {
    if (file.use_count() == 0)
        return false;
    if (!file->stream.good())
        return false;

    auto &read = file->stream;
    read.seekg(0, page_index * PAGESIZE);
    auto before = read.tellg();
    read.read((char *)&data[0], PAGESIZE);
    if (read.bad() || read.tellg() - before)
        return false;

    return true;
}