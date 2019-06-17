#ifndef SEMANTICCHECK_H
#define SEMANTICCHECK_H
#include <string>
#include <iostream>
#include <vector>
#include "../Interpreter/QueryType.h"
/*insert:
check the table_name
check the type of attribute (length of string is enough),
check if the attribute is unique
*/
bool check_insert(const std::string &table_name, std::vector<SQLValue> &value_list);

/*delete:
check the table_name,
check whether the condition has correct type and attribute,
*/
bool check_delete(const std::string &table_name, /*test const*/std::vector<Condition> &condition_list);

/*select: 
check the table_name,
check whether the condition has correct type and attribute
*/
bool check_select(const std::string &table_name, /*test const*/ std::vector<Condition> &condition_list);

#endif