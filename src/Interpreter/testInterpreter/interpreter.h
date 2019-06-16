
#ifndef INTERPRETER_H
#define INTERPRETER_H
#define INPUT_LENGTH 40960

#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
#include <stdexcept>
#include <fstream>
#include "interpreter.tab.h"
#include "QueryType.h"
#include "lex.yy.h"
#include "API.h"

/*the parsed request */
extern QueryRequest* query;

class Interpreter{
public:
	/*read the input*/
	void read_command_loop();
};

/*parse the command-syntax examine*/
void doParse();

/*Call api to execute the query request-semantic examine*/
void execQuery();

/*run file to execute every command in it*/
void execFile(const std::string &file_name);


void createQueryToTable(const CreateTableQuery * query,Table &tb);
#endif 
