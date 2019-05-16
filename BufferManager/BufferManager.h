#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H
#include "Page.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <exception>
#include <stdexcept>

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
            inline bool push(const T &v) {
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
                return v;
            }

            inline T front() const{
                if(cap == 0)
                    return std::out_of_range("Empty queue");
                return data[head];
            }
            
            inline void rotate() noexcept{
                head = (head + 1) % MAXSIZE;
                tail = (tail + 1) % MAXSIZE;
            }
        };
    }

    class BufferManager{
    public:
        using Flag = decltype(std::ios::in);
        BufferManager(/* args */);
        ~BufferManager();

        // close the file according to the given path
        // all pages of this file in buffer will be flushed away
        // @param: the path to the file to be closed
        // @throw: std::invalid_argument("Unopened file") if the file is not open in the BufferManager
        void closeFile(std::string path);

        // delete the file according to the given path
        // @require: there is no page of this file in buffer
        // @param: the path of the file
        // @throw: std::run_time_error("Fail deleting file") if the funciton fails to delete the file
        void deleteFile(const std::string &path);
        
        // open the file according to given path and read the first page into memory
        // if the path does not exist, create an empty file
        // the openmode of file is (in | out | binary)
        // @param: the path of the file to be opened 
        // @throw: std::runtime_error("Fail opening file") if the file does not be opened successfully
        Page& openFile(const std::string &path);

        // read specified page of a file according to the path to the file and the index of the page
        // if the file has not been opened yet, open the file first
        // @oaram: the path to the file and the index of the page
        // @throw: std::out_of_range("Full Buffer") exception if the buffer is full and the replacement fails
        //         std::runtime_error("Fail opening file") if the file does not be opened properly
        // @return: The reference to the specifed page in buffer
        Page& getPage(const std::string &path, unsigned int index);

        // get the next page of file relative to current page
        // @param: a page representing the current position
        // @require: the argument passed to the function should be a valid page
        // @throw: std::out_of_range("Full Buffer") exception if the buffer is full and the replacement fails
        // @return: The reference to the specifed page in buffer
        Page& getNextPage(const Page &page);
        // get the previous page of file relative to current page
        Page& getPrevPage(const Page &page);
        // get the first page of file relative to current page
        Page& getFirstPage(const Page &page);
        // get the last page of file relative to current page
        Page& getLastPage(const Page &page);

        // create a new page appending to the tail of the file and read it into buffer
        // @param: path to the file 
        // @throw: std::out_of_range("Full Buffer") exception if the buffer is full and the replacement fails
        // @return: The reference to the specifed page in buffer
        Page& createPage(const std::string &path);
    private:
        std::unordered_map<PageInfo, unsigned int> pool;
        std::unordered_multimap<std::string, unsigned int> file2page;

        Page pages[POOLSIZE];
        imp::queue<unsigned int, POOLSIZE> ref_q;
        unsigned int ref_bits[POOLSIZE];
        Page& allocateNewPage();
        Page& replace();
    };
}

#endif