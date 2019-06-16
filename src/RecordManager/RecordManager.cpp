#include "RecordManager.h"
#include <cstring>
using namespace RM;

int RecordManager::getRecordLength(const std::string &tableName) {
    std::optional<Table> table = API::getCM().getTableByName(tableName);
    int len = 0;
    if (table) {
        for (const auto &attr: table->attrs) {
            if (attr.second.type == common::attrtype::SQL_INT)
                len += sizeof(int);
            if (attr.second.type == common::attrtype::SQL_CHAR)
                len += sizeof(char) * attr.second.size;
            if (attr.second.type == common::attrtype::SQL_FLOAT)
                len += sizeof(float);
        }
    }
    return len;
}

int RecordManager::selectRecord(
            const std::string &tableName, const std::vector<std::string> &colName,
            const std::vector<Condition> &cond, const std::vector<std::string> &operand,
            std::vector<char*> &records, std::vector<int> &ids
) {
    loadTable(tableName);
    ptr = -1;
    // Iterate through record file
    int id, hitCount = 0;
    char* dataIn = new char[recordLength];

    while ((id = getNextRecord(dataIn)) >= 0)
        // Check all conditions
        if (checkRecord(dataIn, tableName, colName, cond, operand))
        {
            char* hit = new char[recordLength];
            memcpy(hit, dataIn, recordLength);

            records.push_back(hit);
            ids.push_back(id);
            hitCount++;
        }

    delete[] dataIn;
    return hitCount;
}

int RecordManager::insertRecord(const std::string &tableName, const std::string &data) {
    loadTable(tableName);
    loadRecord(firstEmpty >= 0 ? firstEmpty : recordCount);

    if (firstEmpty >= 0)
        // Update first empty record
        firstEmpty = *(reinterpret_cast<int*>(&page->data[bias]));
    else 
        // Update total number of records
        recordCount++;

    page->modify((char*)data.c_str(), bias, bias + recordLength - 1);
    char zero = 0;
    page->modify(&zero, bias + recordLength - 1, bias + recordLength);
    updateHeader();
    page->unpin();

    return true;
}

bool RecordManager::removeRecord(const std::string tableName, const int id) {
    loadTable(tableName);

    if (id >= recordCount) {
        std::cerr << "ERROR: [HeapFile::deleteRecord] Index out of range!" << std::endl;
        return false;
    }

    // Check record validity
    loadRecord(id);
    bool invalid = *(reinterpret_cast<char*>(&page->data[bias + recordLength - 1]));
    if (invalid) {
        std::cerr << "ERROR: [HeapFile::deleteRecord] Record already deleted!" << std::endl;
        return false;
    }

    // Update data
    page->modify((char*)&firstEmpty, bias, bias + 4);
    char one = 1;
    page->modify(&one, bias + recordLength - 1, bias + recordLength);

    firstEmpty = ptr;
    updateHeader();
    return true;
}

bool RecordManager::removeRecord(const std::string tableName, const std::vector<int> &ids) {
    loadTable(tableName);
    for (int i = 0; i < (int)ids.size(); i++)
        removeRecord(tableName, ids.at(i));
    return true;
}

bool RecordManager::createTable(const std::string &tableName) {
    std::string tableFileStr = tableFile(tableName);
    page = API::getBM().createPage(tableFileStr);

    // Add an extra invalidity-bit
    recordLength = getRecordLength(tableName) + 1;
    page->modify((char*)&recordLength, 0, sizeof(int));
    recordCount = 0;
    firstEmpty = -1;
    this->tableName = tableName;
    updateHeader();
    page->unpin();

    return true;
}

bool RecordManager::dropTable(const std::string &tableName) {
    std::string tableFileStr = tableFile(tableName);
    API::getBM().deleteFile(tableFileStr);
    return true;
}

bool RecordManager::checkRecord(
    const std::string &record, const std::string &tableName,
    const std::vector<std::string> &colName, const std::vector<Condition> &cond,
    const std::vector<std::string> &operand
) {
    using namespace std;
    std::optional<Table> table = API::getCM().getTableByName(tableName);
    if (!table)
        return false;

    std::map<std::string, int> attrPos;
    int offset = 0;
    for (const auto &attr: table->attrs) {
        attrPos.insert(make_pair(attr.first, offset));
        if (attr.second.type == common::attrtype::SQL_INT)
            offset += sizeof(int);
        if (attr.second.type == common::attrtype::SQL_CHAR)
            offset += sizeof(char) * attr.second.size;
        if (attr.second.type == common::attrtype::SQL_FLOAT)
            offset += sizeof(float);
    }

    int condCount = colName.size();

    for (int i = 0; i < condCount; i++)
    {
        char dataOut[MAX_VALUE_LENGTH];
        common::attrtype::SQL_TYPE type = table->attrs.find(colName[i])->second.type;

        if (type == common::attrtype::SQL_CHAR)
        {
            // Char type
            memcpy(dataOut, record.c_str() + attrPos.find(colName[i])->second, sizeof(char) * table->attrs.find(colName[i])->second.size);
            if (!charCmp(dataOut, operand.at(i).c_str(), cond.at(i)))
                return false;
        }
        else if (type == common::attrtype::SQL_INT)
        {
            // Int type
            memcpy(dataOut, record.c_str() + attrPos.find(colName[i])->second, sizeof(int));
            if (!intCmp(dataOut, operand.at(i).c_str(), cond.at(i)))
                return false;
        }
        else if (type == common::attrtype::SQL_FLOAT)
        {
            // Float type
            memcpy(dataOut, record.c_str() + attrPos.find(colName[i])->second, sizeof(float));
            if (!floatCmp(dataOut, operand.at(i).c_str(), cond.at(i)))
                return false;
        }
    }

    return true;
}

void RecordManager::loadTable(const std::string &tableName) {
    std::string tableFileStr = tableFile(tableName);
    this->tableName = tableName;

    page = API::getBM().getPage(tableFileStr, 0);
    recordLength = *(reinterpret_cast<int*>(&page->data[0]));
    recordCount = *(reinterpret_cast<int*>(&page->data[4]));
    recordBlockCount = BM::PAGESIZE / recordLength;
    firstEmpty = *(reinterpret_cast<int*>(&page->data[8]));
    page->unpin();
}

void RecordManager::updateHeader() {
    std::string tableFileStr = tableFile(tableName);
    BM::Page *page = API::getBM().getPage(tableFileStr, 0);
    page->modify((char*)&recordCount, 4, 4 + sizeof(int));
    page->modify((char*)&firstEmpty, 8, 8 + sizeof(int));
    page->unpin();
}

void RecordManager::loadRecord(int id) {
    std::string tableFileStr = tableFile(tableName);
    ptr = id;
    int pageIndex = ptr / recordBlockCount + 1;
    int pageNum = API::getBM().fileSize(tableFileStr);
    if (pageIndex < pageNum)
        page = API::getBM().getPage(tableFileStr, pageIndex);
    else 
        page = API::getBM().createPage(tableFileStr);
    page->unpin();
    bias = ptr % recordBlockCount * recordLength;
}

int RecordManager::getNextRecord(char* data) {
    bool invalid = true;

    // Read next valid record
    do
    {
        if (ptr + 1 >= recordCount)
        {
            // End of file
            memset(data, 0, sizeof(char) * (recordLength - 1));
            return -1;
        }
        
        loadRecord(ptr + 1);
        invalid = *(reinterpret_cast<char*>(&page->data[bias + recordLength - 1]));
    }
    while (invalid);

    memcpy(data, &page->data[bias], recordLength - 1);
    return ptr;
}

bool RecordManager::charCmp(const char* a, const char* b, Condition op) {
    if (op == EQ)
        return strcmp(a, b) == 0;
    else if (op == NE)
        return strcmp(a, b) != 0;
    else if (op == LT)
        return strcmp(a, b) < 0;
    else if (op == GT)
        return strcmp(a, b) > 0;
    else if (op == LE)
        return strcmp(a, b) <= 0;
    else if (op == GE)
        return strcmp(a, b) >= 0;
    else
        return false;
}

bool RecordManager::intCmp(const char* a, const char* b, Condition op) {
    const int left = *(reinterpret_cast<const int*>(a));
    const int right = *(reinterpret_cast<const int*>(b));

    if (op == EQ)
        return left == right;
    else if (op == NE)
        return left != right;
    else if (op == LT)
        return left < right;
    else if (op == GT)
        return left > right;
    else if (op == LE)
        return left <= right;
    else if (op == GE)
        return left >= right;
    else
        return false;
}

bool RecordManager::floatCmp(const char* a, const char* b, Condition op) {
    const float left = *(reinterpret_cast<const float*>(a));
    const float right = *(reinterpret_cast<const float*>(b));

    if (op == EQ)
        return left == right;
    else if (op == NE)
        return left != right;
    else if (op == LT)
        return left < right;
    else if (op == GT)
        return left > right;
    else if (op == LE)
        return left <= right;
    else if (op == GE)
        return left >= right;
    else
        return false;
}