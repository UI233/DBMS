#ifndef MINISQL_API_H
#define MINISQL_API_H
#include "../BufferManager/BufferManager.h"
#include "../CatalogManager/CatalogManager.h"
#include "../IndexManager/IndexManager.h"
// #include "../IndexManager/BufferManager.h"

class API{
public:
    ~API() = default;
    static BM::BufferManager& getBM();
    static CM::CatalogManager& getCM();
    static void init();
    static bool dropTable(const std::string &table_name);
    static bool dropIndex(const std::string &table_name);

private:
    static API *api;
    BM::BufferManager buffer_manager;
    CM::CatalogManager catalog_manager;
    API() = default;
};
#endif