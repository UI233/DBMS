#ifndef MINISQL_API_H
#define MINISQL_API_H
#include "../BufferManager/BufferManager.h"
// #include "../CatalogManager/BufferManager.h"
// #include "../IndexManager/BufferManager.h"

class API{
public:
    ~API() = default;
    static BM::BufferManager& getBM();
    static void init();
private:
    static API *api;
    BM::BufferManager buffer_manager;
    API() = default;
};
#endif