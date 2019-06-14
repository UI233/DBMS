

%{ 

#include <iostream>
#include <string>
#include <cstdlib>
#include "Interpreter.h"
#include "ParseHelp.h"
#include "interpreter.tab.h"

int yylex();
void yyerror(char *s, ...);

%}



%token

    Key_CREATE
    Key_DROP
    Key_SELECT
    Key_INSERT
    Key_DELETE
    Key_TABLE
    Key_INDEX

    Key_INTO
    Key_FROM
    Key_WHERE
    Key_AND
    Key_ON
    Key_VALUES
    Key_UNIQUE
    Key_PRIMARY
    Key_KEY

    Type_FILE
    Key_EXECFILE

    Key_INTEGER
    Key_FLOAT
    Key_CHAR

    Key_EXIT

    Type_LT
    Type_GT
    Type_GE
    Type_LE
    Type_EQ
    Type_NE

%token <i> Type_INT
%token <r> Type_REAL
%token <str> Type_STRING
%token <str> Type_DQSTRING
%token <str> Type_BSSTRING
%token <str> Type_FILE

%type <str> Type_ASTRING
%type <str> Type_BSTRING

%type <op> operator

%type <val> value

%type <cond> condition


%type <condition_list> condition_list;
%type <condition_list> op_where;

%type <value_list> value_list;

%type <b> op_unique;
%type <attr> attr_pair;
%type <attr_list> attr_definition;

%type <str> op_primary_key;

%type <attr> attr_type;

%type <dummy> top_stmt
    exit
    dml
    ddl
    exec_file

%type <dummy>
    insert
    query
    delete_operation
    create_table
    create_index
    drop_table
    drop_index
%%

top_sentence: top_stmt ';' { YYACCEPT; };

top_stmt: exit
    | dml
    | ddl
    | exec_file
    ;

dml: insert
    | query
    | delete_operation
    ;

ddl: create_table
    | create_index
    | drop_table
    | drop_index
    ;

/*execute file*/
exec_file: Key_EXECFILE Type_FILE
    {
        auto exec_file_query = new ExecFileQuery();
        exec_file_query->file_name = $2;

        query = exec_file_query;
    }
    ;
/*create table table_name(...)*/
create_table: Key_CREATE Key_TABLE Type_STRING '(' attr_definition op_primary_key ')'
    {
        auto create_table_query = new CreateTableQuery();
        create_table_query->table_name = $3;
        create_table_query->attr_list = $5;
        create_table_query->primary_key_name = $6;

        query = create_table_query;
    }
    ;
/*create index index_name on table_name(attr_name)*/
create_index: Key_CREATE Key_INDEX Type_STRING Key_ON Type_STRING '(' Type_STRING ')'
    {
        auto create_index_query = new CreateIndexQuery();
        create_index_query->index_name = $3;
        create_index_query->table_name = $5;
        create_index_query->attr_name = $7;

        query = create_index_query;
    }
    ;
/*drop table table_name*/
drop_table: Key_DROP Key_TABLE Type_STRING
    {
        auto drop_table_query = new DropTableQuery();
        drop_table_query->table_name = $3;

        query = drop_table_query;
    }
    ;

/*drop index index_name*/
drop_index: Key_DROP Key_INDEX Type_STRING
    {
        auto drop_index_query = new DropIndexQuery();
        drop_index_query->index_name = $3;

        query = drop_index_query;
    }
    ;

/*delete from table_name where ...*/
delete_operation: Key_DELETE Key_FROM Type_BSTRING op_where
    {
        auto delete_query = new DeleteQuery();
        delete_query->table_name = $3;
        delete_query->condition_list = $4;

        query = delete_query;
    }
    ;

/*select * from table_name where ...*/
query: Key_SELECT '*' Key_FROM Type_BSTRING op_where
    {
        auto select_query = new SelectQuery();
        select_query->table_name = $4;
        select_query->condition_list = $5;

        query = select_query;
    }
    ;

/*insert into table_name valuer(...)*/
insert: Key_INSERT Key_INTO Type_BSTRING Key_VALUES '(' value_list ')'
    {
        auto insert_query = new InsertQuery();
        insert_query->table_name = $3;
        insert_query->value_list = $6;

        query = insert_query;
    }
    ;
/*,primary key ( attr_name )*/
op_primary_key: ',' Key_PRIMARY Key_KEY '(' Type_BSTRING ')'
    {
        $$ = $5;
    }
    /*no definition*/
    | nothing
    {
        $$ = "";
    }

/*where condition and condition and ...*/
op_where: Key_WHERE condition_list
    {
        $$ = $2;
    }
    /*no condition*/
    | nothing
    {
        $$ = std::vector<Condition>();
    }
    ;

attr_definition: attr_definition ',' attr_pair
    {
        $$ = $1;
        $$.push_back($3);
    }
    | attr_pair
    {
        $$ = std::vector<attrValue>();
        $$.push_back($1);
    }
    ;

/*attr_name attr_type unique(or null)*/
attr_pair: Type_STRING attr_type op_unique
    {
        $$=$2;
        $$.attrName=$1;
        /*true or false*/
        $$.unique = $3;
    }
    ;
/*char(5)/int/float*/
attr_type: Key_INTEGER { $$.type = SQLValueType::INT; }
    | Key_FLOAT { $$.type = SQLValueType::FLOAT; }
    | Key_CHAR '(' Type_INT ')' { $$.type = SQLValueType::STRING; $$.charSize = $3; }
    ;

op_unique: Key_UNIQUE { $$ = true; }
    | nothing { $$ = false; }
    ;

condition_list: condition_list Key_AND condition
    {
        $1.push_back($3);
        $$ = $1;
    }
    /*final*/
    | condition
    {
        $$ = std::vector<Condition>();
        $$.push_back($1);
    }
    ;
/*attrname op value*/
condition: Type_BSTRING operator value
    {
        $$.name = $1;
        $$.op = $2;
        $$.val = $3;
    }
    ;

value_list: value_list ',' value
    {
        $1.push_back($3);
        $$ = $1;
    }
    | value
    {
        $$ = std::vector<SQLValue>();
        $$.push_back($1);
    }
    ;

value:
    Type_INT { $$.type = SQLValueType::INT; $$.i = $1; }
    | Type_REAL { $$.type = SQLValueType::FLOAT; $$.r = $1; }
    | Type_ASTRING { $$.type = SQLValueType::STRING; $$.str = $1; }
    ;

operator:
    Type_LT {   $$ = Operator::LESS_THAN; }
    | Type_LE { $$ = Operator::LESS_EQUAL; }
    | Type_GT { $$ = Operator::GREATER_THAN; }
    | Type_GE { $$ = Operator::GREAT_EQUAL; }
    | Type_EQ { $$ = Operator::EQUAL; }
    | Type_NE { $$ = Operator::NOT_EQUAL; }
    ;

Type_ASTRING: 
    Type_DQSTRING 
    | Type_STRING
    ;

Type_BSTRING:
    Type_BSSTRING 
    | Type_STRING
    ;

exit: 
    Key_EXIT { isExit = true; }
    ;

nothing:
    ;


%%
void yyerror(char *s, ...)
{
    std::cerr << "Error: ";
    std::cerr << s << std::endl;
}

