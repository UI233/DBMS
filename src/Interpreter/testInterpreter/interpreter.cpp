#include "interpreter.h"

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
       /* auto CM = Api::ApiHelper::getApiHelper()->getCatalogManager();
        auto bm = Api::ApiHelper::getApiHelper()->getBufferManager();
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
        execQuery();
    }
}

//semantic test
void execQuery()
{
	auto CM=new cm::catalogManager();
	bool isPassSemanticCheck=true;
    switch(query->getQueryType())
    {
        case QueryType::INSERT:
		{	auto insert_query = dynamic_cast<InsertQuery *>(query);
			if (insert_query)
			{
				isPassSemanticCheck=check_insert(insert_query->table_name, insert_query->value_list);
				if(isPassSemanticCheck)
				{
					auto insert_count = Api::insert(insert_query->table_name, insert_query->value_list);
				}
				delete insert_query;
				query = nullptr;
				return;
			}
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
					Api::delete_operation(delete_query->table_name, delete_query->condition_list);
				}
				delete delete_query;
				query = nullptr;
				return;
			}
			break;
		}
        case QueryType::SELECT:
		{
			auto select_query = dynamic_cast<SelectQuery *>(query);
			if (select_query)
			{
				isPassSemanticCheck=check_select(select_query->table_name,select_query->condition_list)
				if(isPassSemanticCheck)
				{
					auto r = Api::select(select_query->table_name,select_query->condition_list);
				}
				delete select_query;
				query = nullptr;
				return;
			}
			break;
		}
          
        case QueryType::CREATE_TABLE:
		{

			auto create_table_query = dynamic_cast<CreateTableQuery *>(query);
			if (create_table_query)
			{
				try
				{	
					//check
					Table tb = new Table();
					createQueryToTable(create_table_query,tb);
					CM.createTable(create_table_query->table_name, tb);
					//execute
					auto r = Api::create_table(create_table_query->table_name,
					create_table_query->attr_list,
					create_table_query->primary_key_name);

				}
				catch()
				
				delete create_table_query;
				query = nullptr;
				return;
			}
			break;
		}
        case QueryType::CREATE_INDEX:
		{
			auto create_index_query = dynamic_cast<CreateIndexQuery *>(query);
			if (create_index_query)
			{

				try
				{
					CM.createindex(create_index_query->table_name, create_index_query->attr_name, create_index_query->index_name);
					auto r = Api::create_index(create_index_query->table_name, create_index_query->attr_name, create_index_query->index_name);

	/*鬼知道这边要不要输出*/				std::cout<<"Successfully create index."<<std::endl;
				}
				catch(exception& e)
				{
					std::cerr<<e.what()<<std::endl;
				}
				delete create_index_query;
				query = nullptr;
				return;
			}
			break;
		}
          
        case QueryType::DROP_TABLE:
		{
			auto drop_table_query = dynamic_cast<DropTableQuery *>(query);
			if (drop_table_query)
			{
				try
				{
					CM.dropTable(drop_table_query->table_name);
					auto r = Api::drop_table(drop_table_query->table_name);

				}
				catch(exception& e)
				{
					std::cerr<<e.what()<<std::endl;
				}
				
				delete drop_table_query;
				query = nullptr;
				return;
			}
			break;
		}

        case QueryType::DROP_INDEX:
		{
			auto drop_index_query = dynamic_cast<DropIndexQuery *>(query);
			if (drop_index_query)
			{
				/*true if such index exist*/
				isPassSemanticCheck=CM.checkIndex(drop_index_query->index_name);
				if(isPassSemanticCheck)
				{
					auto r = Api::drop_index(drop_index_query->index_name);
				}
				else
				{
					std::cerr<<"There's no index with this name!"<<std::endl;
				}

				delete drop_index_query;
				query = nullptr;
				return;
			}
			break;
		}

        case QueryType::EXEC_FILE:
		{
			auto exec_file_query = dynamic_cast<ExecFileQuery *>(query);
			if (exec_file_query)
			{
				execFile(exec_file_query->file_name);
				delete exec_file_query;
				query = nullptr;
				return;
			}
		}

    }


/*！！r没处理啊*/

    return;
}

int main(int argc, char *argv[])
{
	Interpreter IM;
	IM.read_command_loop();
	return 0;
}

void createQueryToTable(const CreateTableQuery * query,Table &tb)
{
	tb.primary_key=query->primary_key_name;
	auto newattr=new common::attrtype();
	unsigned int order=0;
	for(auto &attr:attr_list)
	{
		newattr.type=(int)(attr.type);
		newattr.unique=attr.unique;
		newattr.size=attr.charSize;
		newattr.order=(order++);
		tb.attrs.insert(pair<std::string, common::attrtype>(attr.attrName, newattr));
	}
}