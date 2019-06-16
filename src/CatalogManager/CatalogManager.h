#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H
#include <map>
#include <utility>
#include <optional>
#include "Table.h"

namespace CM
{
    // table_name and attribute name

    using TableName = std::string;
    using AttributeName = std::string;
    using IndexInfo = std::pair<TableName, AttributeName>;

    class CatalogManager
    {
    private:
        std::map<std::string, Table>  tables;
        std::map<std::string, IndexInfo> indices;
        bool modified;
        void loadFromFile();
    public:
        CatalogManager(const CatalogManager &) = delete;
        CatalogManager(/* args */);
        ~CatalogManager();

        // force the catalogmanager to write the information of schemas to the disk
        void forceWrite();

        // get the information of table by its name
        // @param: the name of table
        // @return: if there exists the table with given name, return corresponding Table class
        //          or the value of optional variable is empty
        std::optional<Table> getTableByName(const std::string& table_name) const;

        // get the information of  index
        // @param: the index of table
        // @return: if there exists the table with given index, return corresponding index information
        //          or the value of optional variable is empty
        std::optional<IndexInfo> getIndex(const std::string& table_index) const;

        // check whether the table with given name exists
        // @param: the name of table need to be checked
        // @return: true if such table exists
        //          false otherwise
        bool checkTableByName(const std::string& table_name) const;

        // check whether the index exists
        // @param: the index of table need to be checked
        // @return: true if such index exists
        //          false otherwise
        bool checkIndex(const std::string& table_index) const;

        // create table by giving its name and schema
        // @param: the name of table and a Table variable containing its schema
        // @throw: std::invalid_argument("Table already exists") if there already exists the table with given name
        //         std::invalid_argument(ErrorInfo) if the definition of schema violate some constrain such that the length of char variable exceeds 255
        void createTable(const std::string& table_name, const Table& schema);

        // drop specified table from database by giving its name
        // @param: the name of table
        // @throw: std::invalid_argument("No such table") if there doesn't exist the table with given name
        void dropTable(const std::string& table_name);

        // create the index named "index_name" on the column "attr_name" of table "table_name" in Catalog
        // @param: the name of table, the name of attributes to be indexed and the name of index
        // @throw: std::invalid_argument("No such table") if the table name is not valid
        //         std::invalid_argument("Invalid attribute") if the attribute is not available on the table
        //         std::invalid_argument("Existing index") if the index with given name already exists
        void createindex(const std::string &table_name, const std::string &attr_name,const std::string &index_name);
    };
} // namespace CM

#endif