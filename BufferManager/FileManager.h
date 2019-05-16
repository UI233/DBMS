#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <fstream>

namespace BM{
    // the size of a single page(in byte)
    static constexpr unsigned int PAGESIZE = 4096;
    // the capacity of pages 
    static constexpr unsigned int POOLSIZE = 40;

   namespace imp{
    class FileManager{
    private:
    public:
        std::fstream stream;
        std::string path;
        unsigned int page_num; // the number of pages in the file
        FileManager();
        ~FileManager();
    };
   } // namespace 
} // namespace BM

 #endif