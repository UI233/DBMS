#include "BufferManager.h"

int main() {
    char ch[BM::PAGESIZE];
    for (auto &v : ch)
        v = 'b';

    BM::BufferManager bm;
    BM::Page* lists[BM::POOLSIZE];
    for (int i = 0; i < 40; ++i) {
        std::string name = "file" + std::to_string(i);
        lists[i] = bm.createPage(name);
    }

    for (int i = 4; i < 40; i += 4)
        lists[i]->unpin();

    lists[0] = bm.getPage("file1", 1);
    lists[1] = bm.getPage("file1", 1);
}