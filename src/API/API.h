#ifndef MINISQL_API_H
#define MINISQL_API_H
#include "../BufferManager/BufferManager.h"
#include "../CatalogManager/CatalogManager.h"
#include "../RecordManager/RecordManager.h"
#include "../IndexManager/IndexManager.h"
#include "../Interpreter/interpreter.h"

// #include "../IndexManager/BufferManager.h"


class API{
public:
    ~API() = default;
    static BM::BufferManager& getBM();
    static CM::CatalogManager& getCM();
    static IM::IndexManager& getIM();
    static RM::RecordManager& getRM();

    static void exec();
    static void init();
    static void destroy();
    static bool dropTable(const std::string &table_name);
    static bool dropIndex(const std::string &index_name);
    static bool createTable(const std::string& table_name,const std::string& primary_key_name, const std::string& primary_index_name);
    static bool createIndex(const std::string &index_name, const std::string &table_name, const std::string& attr_name);
    static bool deleteOperation(const std::string &table_name, const std::vector<Condition> &condition_list);
    static bool insertRecord(const std::string& table_name, const std::vector<SQLValue>value_list);
    static bool select(const std::string &table_name, const std::vector<Condition> &condition_list);
private:
    static API *api;
    static void removeIndices(const std::vector<int> &ids, std::string table_name);

    class GC {
    public:
        ~GC() {
            API::destroy();
        }
    };
    API() { static GC gc; }

    static bool displaySelect(const std::string& table_name, const std::vector<std::string>& raw_data);
    BM::BufferManager buffer_manager;
    CM::CatalogManager catalog_manager;
    IM::IndexManager  index_manager;
    RM::RecordManager record_manager;
    Interpreter interpreter;
    
};
#endif