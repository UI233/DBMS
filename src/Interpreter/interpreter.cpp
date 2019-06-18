#include "interpreter.h"
#include "../API/API.h"
#include <ctime>

QueryRequest *query = nullptr;

/*input of every line*/
char current_input[INPUT_LENGTH];
/*the final command*/
char standard_input[INPUT_LENGTH];
/*copy current_input from letter by letter;
 *if find ;,it will become a standard_input and memset itself to zero and start again
 *So it will process every command in the input and save the unterminated part of the input */
char temp_input[INPUT_LENGTH];
size_t input_len;
size_t temp_len;
char *temp_ptr;
bool isExit = false;
int file_executing = 0;

void flush() {
    API::getCM().forceWrite();
    API::getBM().flush();
}

void Interpreter::read_command_loop ()
{

	std::cout << "MiniSQL> ";
    temp_ptr = &temp_input[0];
    while (true)
    {
        /*For the sake of multi-line command,we need to read lines*/
        memset(current_input, 0, INPUT_LENGTH);
        std::cin.getline(current_input, INPUT_LENGTH);
        /*No \0*/
        temp_len = strlen(current_input);
        current_input[temp_len] = ' ';
        /*copy current_input to temp_input and terminate at ;*/
        for (int i = 0; i < temp_len; ++i)
        {
            *temp_ptr++ = current_input[i];
            if (temp_ptr[-1] == ';')
            {
                memset(standard_input, 0, INPUT_LENGTH);
                std::strncpy(standard_input, temp_input, temp_ptr - temp_input);
                temp_ptr = temp_input;
                memset(temp_input, 0, INPUT_LENGTH);
                /*test*/std::cout<<"Command:"<<standard_input<<std::endl;
                input_len = std::strlen(standard_input);
                /*if we find a standard command we just set it to lex then parse, examine and execute it*/
                yy_switch_to_buffer(yy_scan_string(standard_input));
                doParse();
				std::cout << std::endl;
            }
            /*if there are still some words after the final ;, it will be still in temp_input*/
        }
        /*formato*/
        if (current_input[temp_len - 1] !=';')
        {
            std::cout << "      -> ";
        }
        else
        {
            std::cout << "MiniSQL> ";
        }
    }
}

void execFile(const std::string &file_name)
{
    std::ifstream file(file_name);

    if (!file.is_open())
    {
        std::cerr << "File not found!" << std::endl;
        return;
    }
    std::cout << "Executing SQL file: " << file_name << std::endl;

    while (!file.eof())
    {
		/*For the sake of multi-line command,we need to read lines*/
		memset(current_input, 0, INPUT_LENGTH);
		file.getline(current_input, INPUT_LENGTH);
		/*No \0*/
		temp_len = strlen(current_input);
		current_input[temp_len] = ' ';
		/*copy current_input to temp_input and terminate at ;*/
		for (int i = 0; i < temp_len; ++i)
		{
			*temp_ptr++ = current_input[i];
			if (temp_ptr[-1] == ';')
			{
				memset(standard_input, 0, INPUT_LENGTH);
				std::strncpy(standard_input, temp_input, temp_ptr - temp_input);
				temp_ptr = temp_input;
				memset(temp_input, 0, INPUT_LENGTH);
				/*test*/std::cout << "Command:" << standard_input << std::endl;
				input_len = std::strlen(standard_input);
				/*if we find a standard command we just set it to lex then parse, examine and execute it*/
				yy_switch_to_buffer(yy_scan_string(standard_input));
				doParse();
				std::cout << std::endl;
			}
			/*if there are still some words after the final ;, it will be still in temp_input*/
		}
    }
}

void doParse()
{
    yyparse();
    /*if the command is quit, flush the buffer and catalog and exit*/
    if (isExit)
    {
        std::cout << "Byeヽ(￣▽￣)ﾉ\n";
		/*！！调用函数的名字可能还不对*/
       /* auto CM = API::APIHelper::getAPIHelper()->getcatalogManager();
        auto bm = API::APIHelper::getAPIHelper()->getBufferManager();
        CM->Flush();
        bm->flushAllBlocks();
        */
        exit(0);
    }
    if (query == nullptr)
    {
        return;
    } 
    else
    {
		auto st = clock();
		bool queryok = execQuery();
		auto ed = clock();
        if (queryok) {
			std::cout << "("<< (float)(ed - st) / (float)CLOCKS_PER_SEC << " sec)\n";	
			if (file_executing == 0)
				flush();
        }
    }
}

//semantic test
bool execQuery()
{
    auto& catalog_manager = API::getCM();

	bool isPassSemanticCheck=true;
    switch(query->getQueryType())
    {
        case QueryType::INSERT:
		{	auto insert_query = dynamic_cast<InsertQuery *>(query);
			bool r(false);
			if (insert_query)
			{
				isPassSemanticCheck=check_insert(insert_query->table_name, insert_query->value_list);
				if(isPassSemanticCheck)
				{
					auto insert_count = API::insertRecord(insert_query->table_name, insert_query->value_list);
				}
				delete insert_query;
				query = nullptr;
			}
			return isPassSemanticCheck;
			break;
		}
        case QueryType::DELETE:
		{
			auto delete_query = dynamic_cast<DeleteQuery *>(query);
			if (delete_query)
			{

				isPassSemanticCheck=check_delete(delete_query->table_name, delete_query->condition_list);
				if(isPassSemanticCheck)
				{
					API::deleteOperation(delete_query->table_name, delete_query->condition_list);
				}
				delete delete_query;
				query = nullptr;
				return isPassSemanticCheck;
			}
			break;
		}
        case QueryType::SELECT:
		{
			auto select_query = dynamic_cast<SelectQuery *>(query);
            bool r = false;
			if (select_query)
			{
				isPassSemanticCheck=check_select(select_query->table_name,select_query->condition_list);
				if(isPassSemanticCheck)
				{
					r = API::select(select_query->table_name,select_query->condition_list);
				}
				delete select_query;
				query = nullptr;
			}
            return r;
			break;
		}
          
        case QueryType::CREATE_TABLE:
		{
            bool r(false);
			auto create_table_query = dynamic_cast<CreateTableQuery *>(query);
			std::string primary_index_name;
			if (create_table_query)
			{
				try
				{	
					//check
			        if (!create_table_query->primary_key_name.empty())
			        {
			            bool pri_schema_found = false;
			            for (auto &it: create_table_query->attr_list)
			            {
			                if (it.attrName == create_table_query->primary_key_name)
			                {
			                    pri_schema_found = true;
       							primary_index_name = "pri_" + create_table_query->table_name + "_" + it.attrName;
			                }
			            }
			            if (!pri_schema_found)
			            {
			                 throw std::invalid_argument("Table already exists");
			            }
			        }
                    Table tb;
					createQueryToTable(create_table_query,tb);
					catalog_manager.createTable(create_table_query->table_name, tb);
                    // Modified by UI
					//catalogManager->createIndex(create_table_query->table_name,create_table_query->primary_key_name,primary_index_name);
                    if (create_table_query->primary_key_name != "")
                        catalog_manager.createIndex(primary_index_name, create_table_query->table_name, create_table_query->primary_key_name);
					//execute
					r = API::createTable(create_table_query->table_name,create_table_query->primary_key_name,primary_index_name);
				}
				catch(std::exception& e)
				{
					std::cerr<<e.what()<<std::endl;
				}
				
				delete create_table_query;
				query = nullptr;
			}
            return r;
			break;
		}
        case QueryType::CREATE_INDEX:
		{
			auto create_index_query = dynamic_cast<CreateIndexQuery *>(query);
            bool r(false);
			if (create_index_query)
			{
				try
				{
                    // modified by UI 13:03
					// catalogManager->createIndex(create_index_query->table_name, create_index_query->attr_name, create_index_query->index_name);
					r = API::createIndex(create_index_query->index_name, create_index_query->table_name, create_index_query->attr_name);
				}
				catch(std::exception& e)
				{
					std::cerr<<e.what()<<std::endl;
				}
				delete create_index_query;
				query = nullptr;
				return r;
			}
			break;
		}
          
        case QueryType::DROP_TABLE:
		{
			auto drop_table_query = dynamic_cast<DropTableQuery *>(query);
            bool r(false);
			if (drop_table_query)
			{
				try
				{
                    // modified by UI 13:03
					// catalogManager->dropTable(drop_table_query->table_name);
					r = API::dropTable(drop_table_query->table_name);
				}
				catch(std::exception& e)
				{
					std::cerr<<e.what()<<std::endl;
				}
				
				delete drop_table_query;
				query = nullptr;
			}
            return r;
			break;
		}

        case QueryType::DROP_INDEX:
		{
			auto drop_index_query = dynamic_cast<DropIndexQuery *>(query);
            bool r(false);
			if (drop_index_query)
			{
				std::string tableName = catalog_manager.getIndex(drop_index_query->index_name)->first;
				/*true if such index exist*/
				isPassSemanticCheck=catalog_manager.checkIndex(tableName,drop_index_query->index_name);
				if(isPassSemanticCheck)
				{
					r = API::dropIndex(drop_index_query->index_name);
				}
				else
				{
					std::cerr<<"There's no index with this name!"<<std::endl;
				}

				delete drop_index_query;
				query = nullptr;
				return r;
			}
			break;
		}

        case QueryType::EXEC_FILE:
		{
			auto exec_file_query = dynamic_cast<ExecFileQuery *>(query);
            if (exec_file_query)
            {
                file_executing++;
                execFile(exec_file_query->file_name);
                file_executing--;
                delete exec_file_query;
                query = nullptr;
            }
            return exec_file_query;
		}

    }
    return false;
}

void createQueryToTable(const CreateTableQuery * query,Table& tb)
{
	tb.primary_key=query->primary_key_name;
    common::attrtype newattr;
	unsigned int order=0;
	for(auto &attr:query->attr_list)
	{
		newattr.type=common::attrtype::SQL_TYPE((int)(attr.type));
        // UI: mark the primary key as unique
		newattr.unique=(attr.unique) || (attr.attrName == query->primary_key_name);
		newattr.size=attr.charSize;
		newattr.order=(order++);
        // modified by UI 13:07
		tb.attrs.insert(std::pair<std::string, common::attrtype>(attr.attrName, newattr));
	}
}