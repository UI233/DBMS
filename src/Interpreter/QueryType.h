#ifndef QUERY_TYPE_H
#define QUERY_TYPE_H
#include "../../include/common.h"

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

/*attr op val*/
struct Condition 
{
        std::string name;
        Operator op;
        SqlValue val;
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
    DROP_INDEX
};
/*int,float,string*/
enum class SqlValueType
{
	INT,
	FLOAT,
	STRING
}
/*value and type*/
struct SQLValue
{
	SQLValueType type;
    int i;
    float r;
    std::string str;
}
/*attr's value——sqlvalue,primary,unique and charsize*/
struct attrValue
{
	SQLValue value;
    bool primary = false;
    bool unique = false;
    size_t charSize; // charSize does not include the terminating zero of string!
}

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
    SelectQuery():isSelectAll(false)
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

/*create table table_name( attr_name type(table_schema_list),primary key(primary_key_attr)) */
class CreateTableQuery final : public QueryRequest
{
public:
    CreateTableQuery()
    {
        type = QueryType::CREATE_TABLE;
    }
    std::string table_name;
    /*attrname and attrvalue*/
    std::vector<std::pair<std::string, attrValue>> attr_list;
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
#endif