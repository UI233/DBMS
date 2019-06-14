#include "API.h"



namespace Api
{
    size_t insert(const std::string &table_name, std::vector<SQLValue> &value_list)
    {
    	std::cout<<"Insert into table:"<<table_name<<std::endl;
    	for(std::vector<SQLValue>::iterator m = value_list.begin(); m != value_list.end(); m++ ) 
    	{
			std::cout << "valuetype:" << (int)m->type << " int:" << m->i << " float:" << m->r << " string:" << m->str << std::endl;
    	}
		std::cout << "Insert end;\n";
		return 1;
    }

    bool create_table(const std::string &table_name,
                      /*test const*/ std::vector<attrValue> &schema_list,
                      const std::string &primary_key_name
    )
    {
    	std::cout<<"Create table:"<<table_name<< std::endl;
    	for(std::vector<attrValue>::iterator m = schema_list.begin(); m != schema_list.end(); m++ ) 
    	{
    		std::cout<<"attrName:"<<m->attrName<<" attrType:"<<(int)m->type<<" charSize:"<< m->charSize<<" isUnique:"<<m->unique<<std::endl;
    	}
    	std::cout<<"primaryKey:"<<primary_key_name<<std::endl;
		std::cout << "create table end;";
		return 1;
    }

    bool create_index(const std::string &table_name, const std::string &attribute_name, const std::string &index_name )
    {

    	std::cout<<"Create index:"<<table_name<<"\nattributeName:"<<attribute_name<<" indexName:"<<index_name<<std::endl;

		return 1;
    }

    bool drop_table(const std::string &table_name)
    {
    	std::cout<<"Drop table:"<<table_name;

		return 1;
    }

    bool drop_index(const std::string &index_name)
    {
		std::cout << "Drop index" << index_name;

		return 1;
    }

    bool select(const std::string &table_name, /*test const*/  std::vector<Condition> &condition_list)
    {
		
    	std::cout<<"Select from:"<<table_name << std::endl;
    	for(std::vector<Condition>::iterator m = condition_list.begin(); m != condition_list.end(); m++ ) 
    	{
			std::cout << "Condition on:" << m->name << " op:" << (int)m->op << " valueType:" << (int)m->val.type << " int:" << m->val.i << " float:" << m->val.r << " string:" << m->val.str << std::endl;

    	}
		std::cout <<"Select end."<<std::endl;

		return 1;
    }

    bool delete_operation(const std::string &table_name, /*test const*/ std::vector<Condition> &condition_list)
    {
    	std::cout<<"Delete from:"<<table_name << std::endl;
		for (std::vector<Condition>::iterator m = condition_list.begin(); m != condition_list.end(); m++)
		{
			std::cout << "Condition on:" << m->name << " op:" << (int)m->op << " valueType:" << (int)m->val.type << " int:" << m->val.i << " float:" << m->val.r << " string:" << m->val.str << std::endl;

		}
		std::cout <<"Delete end."<<std::endl;

		return 1;
    }
}
