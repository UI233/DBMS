#ifndef PAGE_H
#define PAGE_H
#include <array>
#include <string>
#include <utility>
#include <memory>
#include "FileManager.h"

namespace BM{

    using PageInfo = std::pair<unsigned int, std::string>; // the type indicating the information of page, first is the path to the file, second is this index of the page int the file
    class Page
    {
        friend class BufferManager;
    private:
        //BufferManager *host;
        bool dirty; // indicate whether the page has been or will be modified
        bool pinned; // indicata whether the page will be used in the future, if a page is pinned it would not be flushed away during replacement
        bool is_open; // indicate whether the page is valid
        unsigned int page_index;
        imp::FileManager file;
        bool read();
        void init(const std::string &path, unsigned int idx);
        void close();
    public:
        std::array<unsigned char, PAGESIZE> data;

        // modify the data in [beg, end) of the data member
        // and set this page to be dirty
        // @params: the pointer to the date to be copied from, the begin and end position of the data to be modified in this page
        // @throw: std::invalid_argument("Out of range") if beg < 0 or end > PAGESIZE
        //         std::invalid_argument("Invalid page") if this page is invalid
        void modify(char * pdata, int beg, int end);

        // unpin this page to allow the BufferManager to replace it when the buffer is full
        inline void unpin() noexcept {pinned = false;}

        // mark the page as dirty to indicate it should be written back to the disk
        inline void setDirty() noexcept {dirty = true;}

        // force the page to be written back to disk without closing it
        // the dirty mark will be set of false after writing
        // @throw: std::runtime_error("Fail writting back") if it fails to writte back to disk
        //          std::invalid_argument("Invalid page") if the page is invalid
        void forceWrite();

        // get the information of this page
        // @return: a pair variable containing the index of page and the path to the file
        // @throw: std::invalid_argument("Invalid page") if this page is invalid
        PageInfo getInfo() const;

        // @return: a bool indicate whether the page is valid
        inline bool isValid() const noexcept { return is_open; }
        
        // @return: whether this page is the first page of the file i.e. page_index == 0
        inline bool isFirst() const{ return page_index == 0; }

        // @return: whether this page is the last page of the file i.e. page_index == page_num - 1
        inline bool isLast() const noexcept { return page_index == file.page_num - 1; }

        Page(): is_open(false), dirty(false), pinned(false) {}
        ~Page();
        Page(const Page &) = delete;
        Page& operator = (const Page &) = delete;
    };
}
#endif