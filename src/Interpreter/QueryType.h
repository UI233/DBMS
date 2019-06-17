#ifndef QUERY_TYPE_H
#define QUERY_TYPE_H

#include <string>
#include <vector>
#include <iostream>
#include "common.h"

/*>=,<=,>,<,<>,=*/
enum class Operator
{
    GREATER_THAN,
    GREAT_EQUAL,
    LESS_THAN,
    LESS_EQUAL,
    EQUAL,
    NOT_EQUAL
};

/*Query,Delete,Select,Insert,CreateTable,CreateIndex,DropTable,Dropindex*/
enum class QueryType
{
    INSERT,
    DELETE,
    SELECT,
    CREATE_TABLE,
    CREATE_INDEX,
    DROP_TABLE,
    DROP_INDEX,
    EXEC_FILE
};
/*int,float,string*/
enum class SQLValueType
{
    INT,
    FLOAT,
    STRING
};
/*value and type*/
struct SQLValue
{
    common::attrtype::SQL_TYPE type;
    int i;
    float r;
    std::string str;
};
/*attr's value——sqlvalue,primary,unique and charsize*/
struct attrValue
{
    std::string attrName;
    common::attrtype::SQL_TYPE type;
    bool unique = false;
    size_t charSize; // charSize does not include the terminating zero of string!
};

/*attr op val*/
struct Condition 
{
        std::string name;
        Operator op;
        SQLValue val;
};


class QueryRequest
{
protected:
    QueryType type;

public:
    QueryType getQueryType() const
    {
        return this->type;
    }

    virtual ~QueryRequest() = 0;
};
/*select * from table_name where condition_list*/
class SelectQuery final : public QueryRequest
{
public:
    SelectQuery()
    {
        type = QueryType::SELECT;
    }
    ~SelectQuery() override
    {}
    std::string table_name;
    std::vector<Condition> condition_list;
};

/*insert into table_name values(value_list)*/
class InsertQuery final : public QueryRequest
{
public:
    InsertQuery()
    {
        type = QueryType::INSERT;
    }
    ~InsertQuery() override
    {}
    std::string table_name;
    std::vector<SQLValue> value_list;
};

/*delete from table_name where condition_list*/
class DeleteQuery final : public QueryRequest
{
public:
    DeleteQuery()
    {
        type = QueryType::DELETE;
    }
    std::string table_name;
    std::vector<Condition> condition_list;
};

/*create table table_name( attr_name type(attr_list),primary key(primary_key_attr)) */
class CreateTableQuery final : public QueryRequest
{
public:
    CreateTableQuery()
    {
        type = QueryType::CREATE_TABLE;
    }
    std::string table_name;
    /*attrname and attrvalue*/
    std::vector<attrValue> attr_list;
    std::string primary_key_name;
};
/*create index index_name on table_name(attr_name)*/
class CreateIndexQuery final : public QueryRequest
{
public:
    CreateIndexQuery()
    {
        type = QueryType::CREATE_INDEX;
    }
    std::string table_name;
    std::string attr_name;
    std::string index_name;
};
/*drop table table_name*/
class DropTableQuery final : public QueryRequest
{
public:
    DropTableQuery()
    {
        type = QueryType::DROP_TABLE;
    }
    std::string table_name;
};
/*drop index index_name*/
class DropIndexQuery final : public QueryRequest
{
public:
    DropIndexQuery()
    {
        type = QueryType::DROP_INDEX;
    }
    std::string index_name;
};

class ExecFileQuery final : public QueryRequest
{
public:
    ExecFileQuery()
    {
        type = QueryType::EXEC_FILE;
    }
    std::string file_name;
};
#endif