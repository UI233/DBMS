#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H
#include "Page.h"
#include <memory>
#include <map>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <bitset>
#include <vector>

namespace BM{

    namespace imp{
        template<typename T, unsigned int MAXSIZE>
        class queue{
        private:
            unsigned int cap;
            unsigned int head;
            unsigned int tail;
            T data[MAXSIZE];
        public:
            queue(): cap(0), head(0), tail(0) {}
            inline bool isfull() noexcept {return cap == MAXSIZE;}
            inline void push(const T &v) {
                if(cap == MAXSIZE)
                    throw std::out_of_range("Full queue");
                cap++; 
                data[tail++] = v; 
                tail %= MAXSIZE;
            }

            inline T pop() {
                if(cap == 0)
                    throw std::out_of_range("Empty queue");
                T v = data[head];
                head = (head + 1) % MAXSIZE;
                cap--;
                return v;
            }

            inline T front() const{
                if(cap == 0)
                    throw std::out_of_range("Empty queue");
                return data[head];
            }
            
            inline void rotate() noexcept{
                head = (head + 1) % MAXSIZE;
                tail = (tail + 1) % MAXSIZE;
            }

            inline unsigned int getCap() noexcept {
                return cap;
            }
        };
    }

    class BufferManager{
        //friend class Page;
    public:
        using Flag = decltype(std::ios::in);
        BufferManager(/* args */);
        ~BufferManager();

        inline bool isFull() noexcept { return file2page.size() < POOLSIZE; }

        // close the file according to the given path
        // all pages of this file in buffer will be flushed away
        // @param: the path to the file to be closed
        // @throw: std::invalid_argument("Invalid file") if the file is not open in the BufferManager
        void closeFile(const std::string &path);

        // delete the file according to the given path
        // @require: there is no page of this file in buffer
        // @param: the path of the file
        // @throw: std::run_time_error("Fail deleting file") if the funciton fails to delete the file
        void deleteFile(const std::string &path);
        
        // read specified page of a file according to the path to the file and the index of the page
        // if the file has not been open yet, open the file first
        // if the path does not exist, create an empty file
        // the openmode of file is (in | out | binary)
        // @param: the path to the file and the index of the page
        // @throw: std::out_of_range("Full buffer") exception if the buffer is full and the replacement fails
        //         std::out_of_range("Out of range") if index excess the number of pages of the file
        //         std::runtime_error("Fail opening file") if the file does not be opened properly
        // @return: The pointer to the specifed page in buffer
        Page* getPage(const std::string &path, unsigned int index);

        // get the next page of file relative to current page
        // @param: a page representing the current position
        // @require: the argument passed to the function should be a valid page
        // @throw: std::out_of_range("Full Buffer") exception if the buffer is full and the replacement fails
        // @return: The pointer to the specifed page in buffer
        Page* getNextPage(Page * page);
        // get the previous page of file relative to current page
        Page* getPrevPage(Page *page);
        // get the first page of file relative to current page
        Page* getFirstPage(Page * page);
        // get the last page of file relative to current page
        Page* getLastPage(Page *page);

        // create a new page appending to the tail of the file
        // @param: path to the file 
        // @throw: std::out_of_range("Full Buffer") exception if the buffer is full and the replacement fails
        //         std::runtime_error("Fail opening file") if the file does not be opened properly
        // @return: a pointer to the newly constructed page
        Page* createPage(const std::string &path);

        // close the certain page, throw it out from buffer
        // if the page is dirty write this page back to disk
        // @throw: std::invalid_argument("Invalid page") if the page is invalid
        // @param: a pointer to a specified page
        void close(Page* page);

        BufferManager(const BufferManager &) = delete;
        BufferManager& operator = (const BufferManager &) = delete;
    private:
        std::map<std::pair<unsigned int, std::string>, unsigned int> file2page;
        std::vector<unsigned int> active_list;
        Page pages[POOLSIZE];
        imp::queue<unsigned int, POOLSIZE> ref_q;
        std::bitset<POOLSIZE> ref_bits;
        unsigned int allocateNewPage();
        unsigned int replace();
    };
}

#endif