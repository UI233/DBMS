#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "../BufferManager/BufferManager.h"
#include "../CatalogManager/CatalogManager.h"
#include "../API/API.h"

namespace RM{

    enum Condition {EQ, NE, LT, GT, LE, GE};

    static constexpr unsigned int MAX_VALUE_LENGTH  = 256;

    inline std::string tableFile(const std::string &tableName) { return tableName + ".tb"; }

    class RecordManager
    {
    public:
        RecordManager(): {}
        ~RecordManager() {}

        int getRecordLength(const std::string &tableName);

        // Select record from table. Return number of records selected
        int selectRecord(
            const std::string &tableName, const std::vector<std::string> &colName,
            const std::vector<Condition> &cond, const std::vector<std::string> &operand,
            std::vector<char*> &records, std::vector<int> &ids
        );

        // Insert record into table. Return new index id
        int insertRecord(const std::string &tableName, const std::string &data);

        // Delete id-th record from table. Return true if success
        bool removeRecord(const std::string tableName, const int id);
        bool removeRecord(const std::string tableName, const std::vector<int> &ids);

        // Create table. Return true if success
        bool createTable(const std::string &tableName);

        // Drop table. Return true if success
        bool dropTable(const std::string &tableName);

        // Check if record satisfy all conditions
        bool RecordManager::checkRecord(
            const std::string &record, const std::string &tableName,
            const std::vector<std::string> &colName, const std::vector<Condition> &cond,
            const std::vector<std::string> &operand
        ); 

    private:

        BM::Page *page;

        // Table name
        std::string tableName;

        // Length of a record
        int recordLength;

        // Total number of records(include invalid ones)
        int recordCount;

        // Number of records in a block
        int recordBlockCount;

        // First empty record
        int firstEmpty;

        // Record pointer
        int ptr;
        
        // Pointer bias in the block
        int bias;

        void loadTable(const std::string &tableName);

        // Update file header
        void updateHeader();

        // Load id-th record to block
        void loadRecord(int id);

        // Read next record. Return id of the record
        int getNextRecord(char* data);

        // Compare string
        bool charCmp(const char* a, const char* b, Condition op);

        // Compare int
        bool intCmp(const char* a, const char* b, Condition op);

        // Compare float
        bool floatCmp(const char* a, const char* b, Condition op);
    };
}

#endif