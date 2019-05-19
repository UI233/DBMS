#include "BufferManager.h"
#include <cstring>
using namespace BM;

bool fileExist(const std::string &path) {
    std::ifstream checker(path);
    return checker.good();
}

BufferManager::BufferManager(){
    active_list.reserve(POOLSIZE);
    ref_bits.reset();
    for(int i = 0; i < POOLSIZE; ++i)
        active_list.push_back(i);
    //for (auto &page : pages)
    //    page.host = this;
}

BufferManager::~BufferManager(){
}

void BufferManager::closeFile(const std::string &path) {
    for(auto& v: file2page)
        if (v.first.second == path) {
            auto idx = v.second;
            pages[idx].close();
        }
}

void BufferManager::deleteFile(const std::string &path) {
    int idx = remove(path.c_str());
    if (idx == 0)
        return;
    throw std::runtime_error("Fail deleting file");
}

//Page* BufferManager::getPage(const std::string &path, unsigned int index) {
//    auto eq = file2page.equal_range(path);
//    unsigned int idx;
//    std::shared_ptr<imp::FileManager> temp;
//    // the file does not exist
//    if (eq.first == file2page.end()) {
//       temp = std::make_shared<imp::FileManager>(path);
//        if (temp->page_num <= index)
//            throw std::out_of_range("Out of range");
//        idx = allocateNewPage();
//
//        if (idx > POOLSIZE)
//            throw std::out_of_range("Full buffer");
//    }
//
//    else {
//        // the file is in the buffer already
//        for (auto itr = eq.first; itr != eq.second; ++itr)
//         if (pages[itr->second].page_index == index)
//             return pages + itr->second;
//
//        // the file is in buffer while the corresponding page is not.
//        temp = pages[eq.first->second].file;
//        if (temp->page_num <= index)
//            throw std::out_of_range("Out of range");
//        idx = allocateNewPage();
//
//        if (idx > POOLSIZE)
//            throw std::out_of_range("Full buffer");
//    }
//    pages[idx].init(temp, index);
//    file2page.insert(std::make_pair(path, idx));
//    return pages + idx;
//}

Page* BufferManager::getNextPage(Page * page) {
    if (page->isLast()) {
        page->pinned = true;
        return const_cast<Page*>(page);
    }
    return getPage(page->file.path, page->page_index + 1);
}

Page* BufferManager::getPrevPage(Page *page) {
    if (page->isFirst()) {
        page->pinned = true;
        return const_cast<Page*>(page);
    }
    return getPage(page->file.path, page->page_index - 1);
}

Page* BufferManager::getFirstPage(Page *page) {
    return getPage(page->file.path, 0);
}

Page* BufferManager::getLastPage(Page *page) {
    std::fstream stream(page->file.path, std::ios::in | std::ios::out | std::ios::binary);
    stream.seekg(0, stream.end);
    unsigned int page_num = stream.tellg() / PAGESIZE;
    stream.close();
    return getPage(page->file.path, page_num - 1);
}

Page* BufferManager::createPage(const std::string &path) {
    unsigned int index;
    
    unsigned int idx = allocateNewPage();
    if (idx > POOLSIZE)
        throw std::out_of_range("Full buffer");

    bool exist = fileExist(path);
    pages[idx].init(path, 0);
    auto& fs = pages[idx].file.stream;
    auto& pn = pages[idx].file.page_num;
    if (!fs.good())
        throw std::runtime_error("Fail opening file");
    if (exist) {
        fs.seekp(0, fs.end);
        fs.write((char*)&(pages[0].data[0]), PAGESIZE);
        ++pn;
    }
    pages[idx].page_index = pn - 1;
    file2page.insert(std::make_pair(PageInfo(pn - 1, path), idx));
    return pages + idx;
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
    unsigned int count = 0; // the number of pinned valid pages in the queue
    for (idx = ref_q.front(); ref_q.getCap() && (!pages[idx].isValid() || pages[idx].pinned || ref_bits[idx]) && count < POOLSIZE;) {
        // closed page in the queue
        if (!pages[idx].isValid()) {
            ref_q.pop();
            active_list.push_back(idx);
        }
        else {
            if (pages[idx].pinned)
                ++count;
            // if a valid page is unpinned and refered
            else ref_bits[idx] = 0;
        }

        ref_q.rotate();
        idx = ref_q.front();
    }

    if (count == POOLSIZE)
        return POOLSIZE + 1u;

    if (ref_q.getCap()) {
        file2page.erase(pages[idx].getInfo());
        pages[idx].close();
        active_list.push_back(idx);
        ref_q.pop();
    }

    idx = active_list[active_list.size() - 1];
    ref_q.push(idx);
    ref_bits[idx] = 1;
    active_list.pop_back();

    return idx;
}

Page* BufferManager::getPage(const std::string &path, unsigned int index) {
    auto itr = file2page.find(std::make_pair(index, path));
    if (itr != file2page.end()) {
        pages[itr->second].pinned = true;
        return pages + itr->second;
    }
    // the file is in buffer while the corresponding page is not.
    unsigned int idx = allocateNewPage();

    if (idx > POOLSIZE)
        throw std::out_of_range("Full buffer");

    pages[idx].init(path, index);
    auto& fs = pages[idx].file.stream;
    auto& pn = pages[idx].file.page_num;
    if (fs.bad())
        throw std::runtime_error("Fail opening file");
    if (index >= pn)
        throw std::out_of_range("Out of range");
    file2page.insert(std::make_pair(PageInfo(index, path), idx));
    return pages + idx;
}

void BufferManager::close(Page* page) {
    auto info = page->getInfo();
    file2page.erase(info);
    page->close();
}