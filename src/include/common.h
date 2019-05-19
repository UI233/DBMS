#ifndef COMMON_H
#define COMMON_H
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
        attrtype() {}
        ~attrtype() {}
        SQL_TYPE type;
        bool primary;
        bool unique;
        unsigned int size; 
    };
} // namespace common

#endif