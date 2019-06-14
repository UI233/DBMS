%option noyywrap nodefault yylineno case-insensitive
%{
#include "ParseHelp.h"
#include "interpreter.tab.h"

void yyerror(char *s, ...);

#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cctype>

%}

letter      [A-Za-z]
digit       [0-9]
%%

[ \t\n]     {}

-?{digit}+            { sscanf(yytext, "%d", &yylval.i);return Type_INT;} 

-?{digit}+"."{digit}* |
-?"."{digit}+ |
-?{digit}+E[-+]?{digit}+    |
-?{digit}+"."{digit}*E[-+]?{digit}+ |
-?"."{digit}*E[-+]?{digit}+ { sscanf(yytext, "%lf", &yylval.r); return Type_REAL;  }

\"([^\"\n]|(\"\"))*\"       { yylval.str = std::string(yytext + 1, yyleng - 2); return Type_DQSTRING; }
`([^\"\n]|(\"\"))*`         { yylval.str = std::string(yytext + 1, yyleng - 2); return Type_BSSTRING; }


{letter}({letter}|{digit}|_)*  {   yylval.str = std::string(yytext);
    std::string tok{yytext};
    int r = Type_STRING;
    if (tok == "select")r = Key_SELECT;
    if (tok == "create")r = Key_CREATE;
    if (tok == "insert")r = Key_INSERT;
    if (tok == "delete")r = Key_DELETE;
    if (tok == "drop")r = Key_DROP;

    if (tok == "table")r = Key_TABLE;
    if (tok == "index")r = Key_INDEX;

    if (tok == "from")r = Key_FROM;
    if (tok == "where")r = Key_WHERE;
    if (tok == "into")r = Key_INTO;
    if (tok == "and")r = Key_AND;
    if (tok == "values")r = Key_VALUES;
    if (tok == "unique")r = Key_UNIQUE;
    if (tok == "primary")r = Key_PRIMARY;
    if (tok == "key")r = Key_KEY;
    if (tok == "on")r = Key_ON;

    if (tok == "execfile")r = Key_EXECFILE;

    if (tok == "int")r = Key_INTEGER;
    if (tok == "char")r = Key_CHAR;
    if (tok == "float")r = Key_FLOAT;

    if (tok == "exit")r = Key_EXIT;

    return yylval.i = r;}

{letter}({letter}|{digit}|_|-)*(.sql){1} {  yylval.str = std::string(yytext); int r = Type_FILE; return yylval.i = r;}

"<"                  {return Type_LT;}
"<="                 {return Type_LE;}
">"                  {return Type_GT;}
">="                 {return Type_GE;}
"="                  {return Type_EQ;}
"!="                 {return Type_NE;}
"<>"                 {return Type_NE;}

[*/+\-=<>':;,.|&()]  {return yytext[0];}
.                    { std::cerr << "illegal character:" << yytext[0] << "\n"; }

%%