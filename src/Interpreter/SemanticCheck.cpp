#include "../API/API.h"
#include "SemanticCheck.h"

/*insert:
check the table_name
check the type of attribute (length of string is enough),
check if the attribute is unique
*/
bool check_insert(const std::string &table_name, std::vector<SQLValue> &value_list)
{
    auto& cm = API::getCM();
    //check name
    if (!cm.checkTableByName(table_name))
    {
        std::cerr << "Table not found!" << std::endl;
        return false;
    }

    auto tb = cm.getTableByName(table_name);

    //check the number of values
    if (tb->getAttrNum() != value_list.size())
    {
        std::cerr << "Number of values not fit!" << std::endl;
        return false;
    }

    //check the sqlvalue's type
    for(auto &attr: tb->attrs) 
    {
        //the order 
        if ((int)value_list[attr.second.order].type!=attr.second.type)
        {
            if (value_list[attr.second.order].type == common::attrtype::SQL_FLOAT && attr.second.type == common::attrtype::SQL_FLOAT)
            {
                value_list[attr.second.order].type = common::attrtype::SQL_FLOAT;
                value_list[attr.second.order].r = value_list[attr.second.order].i;
            } 
            else
            {
                std::cerr << "Type mismatch!" << std::endl;
                return false;
            }
        }
        //the charSize
        if (value_list[attr.second.order].type == common::attrtype::SQL_CHAR)
        {
            if (value_list[attr.second.order].str.length() > attr.second.getSize())
            {
                std::cout << "Over pass the size of char(..)." << std::endl;
                return false;
            }
        }
    }
    return true;
}

/*delete:
check the table_name,
check whether the condition has correct type and attribute,
*/
bool check_delete(const std::string &table_name, /*test const*/std::vector<Condition> &condition_list)
{
    auto& cm = API::getCM();
    //check table 
    if (!cm.checkTableByName(table_name))
    {
        std::cerr << "Table not found!" << std::endl;
        return false;
    }

    auto tb = cm.getTableByName(table_name);
    //check conditions
    for (const auto &cond: condition_list)
    {
        auto it = tb->attrs.find(cond.name);
        if (it == tb->attrs.end())
        {
            std::cerr << "Attribute in conditions mismatch!" << std::endl;
            return false;
        }
        auto type = tb->attrs[cond.name].type;
        if (type!= common::attrtype::SQL_TYPE((int)(cond.val.type)))
        {
            std::cerr << "Type in conditions mismatch!" << std::endl;
            return false;
        }
    }
    return true;
}

/*select: 
check the table_name,
check whether the condition has correct type and attribute
*/
bool check_select(const std::string &table_name, /*test const*/ std::vector<Condition> &condition_list)
{
        auto& cm = API::getCM();
        //check name
        if (!cm.checkTableByName(table_name))
        {
            std::cerr << "Table not found!" << std::endl;
            return false;
        }

        auto tb = cm.getTableByName(table_name);
        //check conditions
        for (const auto &cond: condition_list)
        {
            auto it = tb->attrs.find(cond.name);
            if (it == tb->attrs.end())
            {
                std::cerr << "Attribute in conditions mismatch!" << std::endl;
                return false;
            }
            auto type = tb->attrs[cond.name].type;
            if (type!= common::attrtype::SQL_TYPE((int)(cond.val.type)))
            {
                std::cerr << "Type in conditions mismatch!" << std::endl;
                return false;
            }
        }
    return true;
}


