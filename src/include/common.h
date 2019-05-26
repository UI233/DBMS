#ifndef COMMON_H
#define COMMON_H
#include <set>
namespace common
{
    class attrtype
    {
    public:
        enum SQL_TYPE{
            SQL_INT,
            SQL_CHAR,
            SQL_FLOAT
        };
        attrtype(SQL_TYPE t_type, bool t_unique, unsigned int t_size = 0): type(t_type), unique(t_unique), size(t_size) {}
        attrtype() {}
        ~attrtype() {}
        SQL_TYPE type;
        bool unique;
        // if type == SQL_CHAR it has such attribute to indicate its maximal length
        unsigned int size; 
    };
} // namespace common

#endif