#include "BufferManager.h"
#include <cstring>
using namespace BM;

BufferManager::BufferManager(){
    active_list.reserve(POOLSIZE);
    ref_bits.reset();
    for(int i = 0; i < POOLSIZE; ++i)
        active_list.push_back(i);
}

BufferManager::~BufferManager(){
}

void BufferManager::closeFile(const std::string &path) {
    auto eq = file2page.equal_range(path);
    if (eq.first == file2page.end())
        throw std::invalid_argument("Invalid file");
    for (auto itr = eq.first; itr != eq.second; ++itr)
        pages[itr->second].close();
}

void BufferManager::deleteFile(const std::string &path) {
    int idx = remove(path.c_str());
    if (idx == 0)
        return;
    throw std::runtime_error("Fail deleting file");
}

Page& BufferManager::getPage(const std::string &path, unsigned int index) {
    auto eq = file2page.equal_range(path);
    // the file does not exist
    if (eq.first == file2page.end()) {
        std::shared_ptr<imp::FileManager> temp(new imp::FileManager(path));
        if (temp->page_num <= index)
            throw std::out_of_range("Out of range");
        unsigned int idx = allocateNewPage();

        if (idx > POOLSIZE)
            throw std::out_of_range("Full buffer");

        pages[idx].init(temp, index);
        return pages[idx];
    }

    // the file is in the buffer already
    for (auto itr = eq.first; itr != eq.second; ++itr)
     if (pages[itr->second].page_index == index)
         return pages[itr->second];

    // the file is in buffer while the corresponding page is not.
    std::shared_ptr<imp::FileManager> temp(pages[eq.first->second].file);
    if (temp->page_num <= index)
        throw std::out_of_range("Out of range");
    unsigned int idx = allocateNewPage();

    if (idx > POOLSIZE)
        throw std::out_of_range("Full buffer");

    pages[idx].init(temp, index);
    return pages[idx];
}

Page& BufferManager::getNextPage(const Page &page) {
    if (page.isLast())
        return const_cast<Page&>(page);
    return getPageRelative(page.page_index + 1, page.file);
}

Page& BufferManager::getPrevPage(const Page &page) {
    if (page.isFirst())
        return const_cast<Page&>(page);
    return getPageRelative(page.page_index - 1, page.file);
}

Page& BufferManager::getFirstPage(const Page &page) {
    return getPageRelative(0, page.file);
}

Page& BufferManager::getLastPage(const Page &page) {
    return getPageRelative(page.file->page_num - 1, page.file);
}

Page& BufferManager::createPage(const std::string &path) {
    auto itr = file2page.find(path);
    unsigned int index;
    std::shared_ptr<imp::FileManager> temp;
    if (itr != file2page.end()) {
        temp = std::make_shared<imp::FileManager>(path);
        index = temp->page_num;
        temp->page_num++;
    }
    else {
        temp= pages[itr->second].file;
        index = temp->page_num;
        temp->page_num++;
    }
    unsigned int idx = allocateNewPage();
    if (idx > POOLSIZE)
        throw std::out_of_range("Full buffer");
    if (!temp->stream.good())
        throw std::runtime_error("Fail opening file");

    auto &fs = temp->stream;
    fs.seekp(0, fs.end);
    fs.write((char*)&(pages[0].data[0]), PAGESIZE);
    pages[idx].init(temp, index);
    return pages[idx];
}

unsigned int BufferManager::allocateNewPage() {
    if (active_list.size() != 0) {
        unsigned int idx = active_list[active_list.size() - 1];
        ref_q.push(idx);
        ref_bits[idx] = 1;
        active_list.pop_back();
        return idx;
    }
    else {
        return replace();
    }
}

// Use LRU approximation to replace the buffer
unsigned int BufferManager::replace() {
    unsigned int idx;
    unsigned int count = 0;
    for (idx = ref_q.front(); ref_q.getCap() && (!pages[idx].isValid() || pages[idx].pinned || ref_bits[idx]) && count < 2 * POOLSIZE; ref_q.rotate(), ++count)
        if (!pages[idx].isValid()) {
            ref_q.pop();
            active_list.push_back(idx);
        }
        else {
            if (!pages[idx].pinned)
                ref_bits[idx] = 0;
        }

    if (active_list.size() == 0)
        return POOLSIZE + 1u;

    if (ref_q.getCap()) {
        pages[idx].close();
        ref_q.pop();
    }

    idx = active_list[active_list.size() - 1];
    ref_q.push(idx);
    ref_bits[idx] = 1;
    active_list.pop_back();

    return idx;
}

Page& BufferManager::getPageRelative(unsigned int index, const std::shared_ptr<imp::FileManager> &fp) {
    auto eq = file2page.equal_range(fp->path);
    // the file is in the buffer already
    for (auto itr = eq.first; itr != eq.second; ++itr)
        if (pages[itr->second].page_index == index)
            return pages[itr->second];

    // the file is in buffer while the corresponding page is not.
    std::shared_ptr<imp::FileManager> temp(pages[eq.first->second].file);
    if (temp->page_num <= index)
        throw std::out_of_range("Out of range");
    unsigned int idx = allocateNewPage();

    if (idx > POOLSIZE)
        throw std::out_of_range("Full buffer");

    pages[idx].init(temp, index);
    return pages[idx];
}