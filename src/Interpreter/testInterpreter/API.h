#ifndef MINISQL_API_H
#define MINISQL_API_H
#include "QueryType.h"

namespace Api
{
	size_t insert(const std::string &table_name, std::vector<SQLValue> &value_list);

    bool delete_operation(const std::string &table_name, /*test const*/std::vector<Condition> &condition_list);

    bool select(const std::string &table_name, /*test const*/ std::vector<Condition> &condition_list);

    bool create_table(const std::string &table_name,
			/*test const*/ std::vector<attrValue> &schema_list,
                      const std::string &primary_key_name = ""
    );

    bool create_index(const std::string &table_name, const std::string &attribute_name, const std::string &index_name);

    bool drop_table(const std::string &table_name);

    bool drop_index(const std::string &index_name);

}

#endif