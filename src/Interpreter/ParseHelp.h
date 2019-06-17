
#ifndef PARSE_PUBLIC_H
#define PARSE_PUBLIC_H

#include <string>
#include <vector>
#include <cstring>

#include "QueryType.h"

#define INPUT_LENGTH 40960

extern char standard_input[INPUT_LENGTH];
extern size_t input_len;

extern std::string file_name;

extern bool isExit;

#ifdef YYSTYPE
#undef YYSTYPE
#endif

#ifdef YY_INPUT
#error YY_INPUT defined
#endif

int get_id(const std::string &s);

typedef struct yystype
{
    int i;
    double r;
    std::string str;
    bool b;
    void *dummy;   
    Operator op;
    SQLValue val;
    Condition cond;
    attrValue attr;
    std::vector<Condition> condition_list;
    std::vector<SQLValue> value_list;
    std::vector<attrValue> attr_list;
} YYSTYPE;


#endif 