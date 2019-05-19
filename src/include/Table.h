#ifndef TABLE_H
#define TABLE_H
#include "common.h"
#include <vector>
class Table
{
public:
    std::vector<std::string> attr_name;
    std::vector<common::attrtype> attr_types;
    inline unsigned intgetAttrNum() {
        return attr_name.size();
    }
    Table(/* args */) {}
    ~Table() {}
};
#endif