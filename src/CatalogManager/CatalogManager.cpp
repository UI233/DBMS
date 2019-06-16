#include "CatalogManager.h"
#include <cstring>
#include <fstream>
#include <vector>
#include <memory>

using namespace CM;

CatalogManager::~CatalogManager() {
    if(modified)
        forceWrite();
}

CatalogManager::CatalogManager(/* args */): modified(false) {loadFromFile();}

std::optional<Table> CatalogManager::getTableByName(const std::string& table_name) const {
    if(!tables.count(table_name))
        return {};
    else return tables.find(table_name)->second;
}


std::optional<IndexInfo> CatalogManager::getIndex(const std::string& table_index) const {
    if(!indices.count(table_index))
        return {};
    else return indices.find(table_index)->second;
}

bool CatalogManager::checkTableByName(const std::string& table_name) const {
    return tables.count(table_name);
}

bool CatalogManager::checkIndex(const std::string& table_index) const{
    return indices.count(table_index);
}

void CatalogManager::createTable(const std::string& table_name, const Table& schema) {
    auto itr = tables.find(table_name);
    if(itr != tables.end())
        throw std::invalid_argument("Table already exists");

    // Check the constrain
    if (schema.attrs.size() > 32)     
        throw std::invalid_argument("Too many attributes in the table.");
    else {
        for (auto pair: schema.attrs)
            if (pair.second.type == common::attrtype::SQL_CHAR && pair.second.size >= 256)
                throw std::invalid_argument("The length of char exceeds 255.");
    }

    tables.insert(std::make_pair(table_name, schema));
    modified = true;
}

std::vector<std::string> CatalogManager::dropTable(const std::string& table_name) {
    std::vector<std::string> res;
    auto itr = tables.find(table_name);
    if(itr == tables.end())
        throw std::invalid_argument("No such table");

    auto pr = indices.equal_range(table_name);
    for (auto itr = pr.first; itr != pr.second; ++itr) {
        auto file_name = common::getIndexFile(itr->second.first, itr->first, itr->second.second);
        res.push_back(std::move(file_name));
        indices.erase(itr);
    }

    modified = true;
    tables.erase(itr);

    return std::move(res);
}

std::vector<std::string> CatalogManager::getAllIndices(const std::string& table_name) {
    auto itr = tables.find(table_name);
    if(itr == tables.end())
        throw std::invalid_argument("No such table");

    auto pr = indices.equal_range(table_name);
    std::vector<std::string> res;
    for (auto itr = pr.first; itr != pr.second; ++itr) {
        auto file_name = common::getIndexFile(itr->second.first, itr->first, itr->second.second);
        res.push_back(std::move(file_name));
    }
    return std::move(res);
}

std::string CatalogManager::getIndexName(const std::string& table_name, const std::string& attr_name) {
    auto pr = indices.equal_range(table_name);
    for (auto itr = pr.first; itr != pr.second; ++itr)
        if (itr->second.second == attr_name)
            return common::getIndexFile(itr->second.first, itr->first, itr->second.second);

    return "";
}

void CatalogManager::forceWrite() {
    // write the string with an ending '\0'
    static auto writeString = [](std::ostream &out, const std::string &str) {
        char zero = '\0';
        out.write(str.c_str(), str.length());
        out.write(&zero, 1);
    };
    // write the table definition back to disk
    static const std::string meta_file("tables.tb");
    std::ofstream meta(meta_file, std::ios::binary);
    for(auto &table: tables) {
        writeString(meta, table.first);
        writeString(meta, table.second.primary_key);
        unsigned char attr_sz = table.second.attrs.size();
        meta.write((char*)(&attr_sz), 1);
        // Attributes should be in order
        unsigned int unique_bytes = attr_sz % 8 == 0 ? attr_sz / 8 : attr_sz / 8 + 1;
        std::unique_ptr<char[]> uniques(new char[unique_bytes]);

        for (unsigned int i = 0; i < unique_bytes; i++)
            uniques[i] = 0u;

        for(auto &attr: table.second.attrs) {
            for(unsigned int i = 0; i < attr_sz; ++i) {
                unsigned int num = i / 8u;
                unsigned int bias = i % 8u;

                if(attr.second.unique)
                    uniques[num] |= 0x80u >> bias;
            }
        }
        meta.write(uniques.get(), unique_bytes);

        for(auto &attr: table.second.attrs) {
            writeString(meta, attr.first);
            meta.write((char*)&attr.second.order, 1);
            meta.write((char*)&attr.second.type, 1);
            if(attr.second.type == common::attrtype::SQL_CHAR)
                meta.write((char*)&attr.second.size, 1);
        }
    }

    // write the index information back to disk
    static const std::string meta_index("index.ix");
    meta.close();
    meta.open(meta_index, std::ios::binary);
    for(auto &index: indices) {
        writeString(meta, index.second.first);
        writeString(meta, index.first);
        writeString(meta, index.second.second);
    }
}

void CatalogManager::loadFromFile() {
    static const std::string meta_file("tables.tb");

    // read the table definition
    std::ifstream meta(meta_file, std::ios::binary);
    meta.seekg(0, meta.end);
    int size = meta.tellg();
    std::unique_ptr<char[]> raw_data(nullptr);
    if (size > 0) {
        meta.seekg(0, meta.beg);
        raw_data.reset(new char[size]);
        meta.read(raw_data.get(), size);
    }
    meta.close();

    std::vector<bool> uniques;
    for(int ptr = 0; ptr < size; ) {
        // the format of table file is in the document
        std::string table_name(raw_data.get() + ptr);
        Table table;
        ptr += table_name.length() + 1;

        std::string primary_key(raw_data.get() + ptr);
        ptr += primary_key.length() + 1;
        table.primary_key = primary_key;

        unsigned int attr_sz = (unsigned char)raw_data[ptr++];
        unsigned int unique_bits_map = (attr_sz % 8 == 0) ? attr_sz / 8 : (attr_sz / 8) + 1;

        for(unsigned int i = 0; i < attr_sz; ++i) {
            unsigned int num = i / 8u;
            unsigned int bias = i % 8u;

            auto t = static_cast<unsigned char>(raw_data[ptr + num]) << bias;
            bool unique = 0x80u & (static_cast<unsigned char>(raw_data[ptr + num]) << bias);
            uniques.push_back(unique);
        }

        ptr += unique_bits_map;

        for(int i = 0; i < attr_sz; ++i) {
            std::string attr_name(raw_data.get() + ptr);
            while(raw_data[ptr++]);
            unsigned char order(raw_data[ptr++]);

            common::attrtype::SQL_TYPE type = static_cast<common::attrtype::SQL_TYPE>(raw_data[ptr]);
            unsigned int size = 0;
            if(type == common::attrtype::SQL_CHAR) 
                size = static_cast<unsigned char>(raw_data[++ptr]);
            ++ptr;
            table.attrs.insert(std::make_pair(attr_name,  common::attrtype(type, uniques[i], order, size)));
        }

        tables.insert(std::make_pair(table_name, table));
        uniques.clear();
    }


    // read the index file
    static const std::string meta_index("index.ix");
    meta.open(meta_index, std::ios::binary);
    meta.seekg(0, meta.end);
    size = meta.tellg();
    if (size > 0) {
        meta.seekg(0, meta.beg);
        raw_data.reset(new char[size]);
        meta.read(raw_data.get(), size);
    }
    meta.close();

    for(int ptr = 0; ptr < size;) {
        std::string index_name(raw_data.get() + ptr);
        ptr += index_name.length() + 1;

        std::string table_name(raw_data.get() + ptr);
        ptr += table_name.length() + 1;

        std::string attr_name(raw_data.get() + ptr);
        ptr += attr_name.length() + 1;

        indices.insert(std::make_pair(table_name, IndexInfo(index_name, attr_name)));
    }
}

void CatalogManager::createindex(const std::string &table_name, const std::string &attr_name,const std::string &index_name) {
    auto pr = indices.equal_range(table_name);
    for (auto itr = pr.first; itr != pr.second; ++itr) {
        if (itr->second.second == attr_name)
            throw std::invalid_argument("existing index");
    }

    auto table_itr = tables.find(table_name);
    if(table_itr == tables.end())
        throw std::invalid_argument("No such table");

    auto attr_itr = table_itr->second.attrs.find(attr_name);
    if (attr_itr == table_itr->second.attrs.end() || !attr_itr->second.unique)
        throw std::invalid_argument("Invalid attribute");

    indices.insert(std::make_pair(table_name, IndexInfo(index_name, attr_name)));
    modified = true;
}
