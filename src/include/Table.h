#ifndef TABLE_H
#define TABLE_H
#include "common.h"
#include <map>
class Table
{
public:
    // the map from attributes' name to its information
    std::map<std::string, common::attrtype> attrs;
    std::string primary_key;
    inline unsigned intgetAttrNum() {
        return attrs.size();
    }
    Table(/* args */) = default;
    ~Table() = default;
};
#endif