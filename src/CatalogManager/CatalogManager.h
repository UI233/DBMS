#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H
#include <map>
#include <utility>
#include "Table.h"

namespace CM
{
    class CatalogManager
    {
    private:
        std::map<std::string, Table>  tables;
    public:
        CatalogManager(/* args */);
        ~CatalogManager();

        // force the catalogmanager to write the information of schemas to the disk
        void forceWrite();

        // get the information of table by its name
        // @param: the name of table
        // @return: if there exists the table with given name, return corresponding Table class
        //          or the value of optional variable is empty
        std::optional<Table> getTableByName(const std::string& table_name) const;

        // get the information of table by its index
        // @param: the index of table
        // @return: if there exists the table with given index, return corresponding Table class
        //          or the value of optional variable is empty
        std::optional<Table> getTableByIndex(const std::string& table_index) const;

        // check whether the table with given name exists
        // @param: the name of table need to be checked
        // @return: true if such table exists
        //          false otherwise
        bool checkTableByName(const std::string& table_name) const;

        // check whether the table with given index exists
        // @param: the index of table need to be checked
        // @return: true if such table exists
        //          false otherwise
        bool checkTableByIndex(const std::string& table_index) const;

        // create table by giving its name and schema
        // @param: the name of table and a Table variable containing its schema
        // @throw: std::invalid_argument("Table already exists") if there already exists the table with given name
        void createTable(const std::string& table_name, const Table& schema);

        // drop specified table from database by giving its name
        // @param: the name of table
        // @throw: std::invalid_argument("No such table") if there doesn't exist the table with given name
        void dropTable(const std::string& table_name);
    };
} // namespace CM

#endif