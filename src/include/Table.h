#ifndef TABLE_H
#define TABLE_H
#include "common.h"
#include <map>
#include <string>

class Table
{
public:
    // the map from attributes' name to its information
    std::map<std::string, common::attrtype> attrs;
    std::string primary_key;
    inline size_t getAttrNum() {
        return attrs.size();
    }
    
    inline size_t getOffset(const std::string& attr_name) {
        int sz[32];
        int count = 0;
        int idx;
        for (auto& attr: attrs) {
            if (attr.first == attr_name)
                idx = count;
            sz[count++] = attr.second.getSize();
        }

        size_t offset = 0;
        for (int i = 0; i <= idx - 1; ++i)
            offset += sz[i];
        return offset;
    } 
    Table(/* args */) = default;
    ~Table() = default;
};
#endif