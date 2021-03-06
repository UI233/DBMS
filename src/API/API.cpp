#include "API.h"
#include <memory>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iomanip>

API* API::api(nullptr);

void API::exec() {
    init();
    api->interpreter.read_command_loop();
}

BM::BufferManager& API::getBM() {
    if (!api)
        init();
    return api->buffer_manager;
}

CM::CatalogManager& API::getCM() {
    if (!api)
        init();
    return api->catalog_manager;
}

IM::IndexManager& API::getIM() {
    if (!api)
        init();
    return api->index_manager;
}

RM::RecordManager& API::getRM() {
    if (!api)
        init();
    return api->record_manager;
}

void API::init() {
    if (!api)
        api = new API();
}

void API::destroy() {
    delete api;
}

bool API::dropTable(const std::string &table_name) {
    using namespace std;
    auto& cm = API::getCM();
    auto& im = API::getIM();
    auto& rm = API::getRM();

    try {
        rm.dropTable(table_name);
        vector<string> dropIndex = cm.dropTable(table_name);
        for(auto &it:dropIndex){
            im.dropIndex(it);
        }
    }
    catch (const exception& err) {
        cout << err.what() << endl;
        return false;
    }
    return true;
}

bool API::dropIndex(const std::string& index_name) {
    using namespace std;
    auto& cm = API::getCM();
    auto& im = API::getIM();

    try{
        auto info = cm.getIndex(index_name);
        if (!info) {
            std::cerr << "No such index\n";
            return false;
        }
        cm.dropIndex(index_name);
        im.dropIndex(common::getIndexFile(index_name, info->first, info->second));
    }
    catch(const std::exception &e) {
        cout << e.what() << endl;
        return false;
    }
    return true;
}

// Todo
bool API::createTable(const std::string& table_name,const std::string& primary_key_name, const std::string& primary_index_name) {
    auto& rm = API::getRM();
    auto& im = API::getIM();
    if (primary_index_name != "")
        im.createIndex (primary_index_name,table_name, primary_key_name);
    std::cout << "Create table success." << std::endl;
    auto rval = rm.createTable(table_name);
    if (rval)
        std::cout << "Query OK 0 row affected ";
    return rval;
}

bool API::createIndex(const std::string & index_name, const std::string &table_name, const std::string& attr_name){
    auto& index_manager = API::getIM();
    auto& record_manager = API::getRM();
    auto& catalog_manager = API::getCM();
    auto table = catalog_manager.getTableByName(table_name);
    if (!table)
        return false;
    try
    {
        // insert it into CM /**/
        catalog_manager.createIndex(index_name, table_name, attr_name);
        // insert every existing records into index manager if any
        index_manager.createIndex(index_name, table_name, attr_name);
        // index_manager.createIndex(table_name);
        auto size = record_manager.getTotalRecordNumber(table_name);
        auto attr_type = table->attrs[attr_name];
        for (int i = 0; i < size; ++i)
            if(record_manager.isValid(table_name, i)){
                auto offset = table->getOffset(attr_name);
                auto length = attr_type.getSize();
                auto raw_data = record_manager.getRawData(table_name, i);
                auto key = raw_data.c_str() + offset;
                index_manager.insert(common::getIndexFile(index_name,table_name,attr_name), (unsigned char*)key, i); }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    std::cout << "Query OK ";
    return true;
}

bool API::displaySelect(const std::string& table_name, const std::vector<std::string>& raw_data) {
    auto& cm = API::getCM();
    auto& rm = API::getRM();
    try {
        auto table = cm.getTableByName(table_name);
        using cmp_t = std::pair<std::string, int>;
        std::vector<cmp_t> attr_temp;
        if (!table) {
            std::cerr << "No such table\n" << std::endl;
            return false;
        }
        for (auto itr : table->attrs)
            attr_temp.push_back(std::make_pair(itr.first, itr.second.order));

        std::sort(attr_temp.begin(), attr_temp.end(), [](const cmp_t &lhs, const cmp_t &rhs) { return lhs.second < rhs.second; });

        if (!table) {
            std::cerr << "Table not exist\n";
        }
        // Todo
        auto attr_num = table->getAttrNum();

        std::vector<int> attrLen;
        int totalLen = 0;
        for (const auto &attr : attr_temp) {
            auto attr_type = table->attrs[attr.first];
            if (attr_type.type == common::attrtype::SQL_INT)
                attrLen.push_back(12);
            if (attr_type.type == common::attrtype::SQL_CHAR)
                attrLen.push_back(12);
            if (attr_type.type == common::attrtype::SQL_FLOAT)
                attrLen.push_back(12);
        }

        for (const auto &data : raw_data) {
            int num = 0;
            for (const auto &attr : attr_temp) {
                int offset = table->getOffset(attr.first);
                auto attr_type = table->attrs[attr.first];
                if (attr_type.type == common::attrtype::SQL_CHAR) {
                    char *p = new char[attr_type.size + 1];
                    memcpy(p, (void*)(data.c_str() + offset), attr_type.getSize());
                    p[attr_type.getSize()] = '\0';
                    if (strlen(p) + 2 > attrLen[num])
                        attrLen[num] = strlen(p) + 2;
                    delete[] p;
                }
                num++;
            }
        }

        for (const auto &len : attrLen) {
            totalLen += len;
        }

        printf("┌");
        for (int i = 0; i < totalLen; i++) {
            printf("─");
        }
        printf("┐\n");
        printf("│");
        int num = 0;
        for (const auto &attr : attr_temp) {
            std::cout << std::setw(attrLen[num]) << attr.first.c_str();
            num++;
        }

        printf("│\n");
        printf("┝");
        for (int i = 0; i < totalLen; i++) {
            printf("━");
        }
        printf("┥\n");

        for (const auto &data : raw_data) {
            printf("│");
            int num = 0;
            for (const auto &attr : attr_temp) {
                int offset = table->getOffset(attr.first);
                auto attr_type = table->attrs[attr.first];
                if (attr_type.type == common::attrtype::SQL_INT)
                    std::cout << std::setw(attrLen[num]) << *(int*)&data[offset];
                if (attr_type.type == common::attrtype::SQL_CHAR) {
                    char *p = new char[attr_type.size + 1];
                    memcpy(p, (void*)(data.c_str() + offset), attr_type.getSize());
                    p[attr_type.getSize()] = '\0';
                    std::cout << std::setw(attrLen[num]) << p;
                    delete[] p;
                }
                if (attr_type.type == common::attrtype::SQL_FLOAT)
                    std::cout << std::setw(attrLen[num]) << *(float*)&data[offset];
                num++;
            }
            printf("│\n");
        }

        printf("└");
        for (int i = 0; i < totalLen; i++) {
            printf("─");
        }
        printf("┘\n");
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}

/*const std::string& data
insert_query->value_list*/
bool API::insertRecord(const std::string& table_name, const std::vector<SQLValue> value_list)
{
    //1. check uniqueness
    auto& rm=API::getRM();
    auto& cm = API::getCM();
    auto& im = API::getIM();
    std::optional<Table> table=cm.getTableByName(table_name);
    //value_list to data
    //first order the value_list to zidianxu, then join them into a string, the length is the attrType's size
    std::string data;
    std::string str;
    size_t total_sz = 0;
    for (auto &attr : table->attrs)
        total_sz += attr.second.getSize();
    data.resize(total_sz, 0);
    total_sz = 0;
    for(auto &attr: table->attrs)
    {
        switch (table->attrs[attr.first].type)
        {
            case common::attrtype::SQL_INT:
                memcpy((void*)(data.c_str() + total_sz), (char *)&(value_list[attr.second.order].i), sizeof(int));
                break;
            case common::attrtype::SQL_FLOAT:
                memcpy((void*)(data.c_str() + total_sz), (char *)&(value_list[attr.second.order].r), sizeof(float));
                break;
            case common::attrtype::SQL_CHAR:
                memcpy((void*)(data.c_str() + total_sz), value_list[attr.second.order].str.c_str(), table->attrs[attr.first].getSize());
                {
                    for (size_t i = data.length(); i < attr.second.getSize();++i)
                        data[i] = 0;
                }
                break;
        }
        total_sz += attr.second.getSize();
    }

    if (!table)
        return false;
    for (auto itr: table->attrs){
        auto offset = table->getOffset(itr.first);
        auto length = itr.second.getSize();
        auto key = data.c_str() + offset;
        std::string raw_data;
        raw_data.resize(length, 0);
        data.copy((char*)raw_data.c_str(), length, offset);

        if (itr.second.unique){
            auto index_name = cm.getIndexName(table_name, itr.first);
            if (index_name != ""){
                if (im.find(index_name,(unsigned char*)raw_data.c_str()) != -1){
                    std::cerr<<"API::insertRecord duplicate record insert\n";
                    return false;
                }
            }
            else{
                std::vector<std::string> rec;
                std::vector<int> ids;

                if (rm.selectRecord(table_name, {itr.first},{RM::EQ},{raw_data}, rec, ids) != 0) {
                    std::cerr<<"API::insertRecord duplicate record insert\n";
                    return false;
                }
            }
        }
    }

    auto id = rm.insertRecord(table_name,data);

    //2. insert it via record manager and get the id back
    for (auto itr: table->attrs){
        auto offset = table->getOffset(itr.first);
        auto length = itr.second.getSize();
        auto key = data.c_str() + offset;

        if (itr.second.unique){
            auto index_name = cm.getIndexName(table_name, itr.first);
            if (index_name != ""){
                im.insert(index_name,(unsigned char*)key,id);
            }
        }
    }

    //3. if there is/are index/indices defined on it, insert it into B+ tree via index manager
    //So the uniqueness should be checked in advance(via index manager maybe)
    std::cout << "Query OK 1 row affected ";
    return true;
}

bool API::select(const std::string &table_name, const std::vector<Condition> &condition_list) {
    auto& catalog_manager = API::getCM();
    auto& index_manager = API::getIM();
    auto& record_manager = API::getRM();

    std::vector<std::string> colName;
    std::vector<RM::Condition> cond;
    std::vector<std::string> operand;
    std::string str;
    std::vector<std::string> records;
    std::vector<int> ids;
    std::string record;

    bool isOptimalChance=true;
    bool isExecEqual=false;
    int equalID;
    bool r;
    auto indices =catalog_manager.getAllIndices(table_name);

    if (indices.size() == 0 || condition_list.size() == 0) {
        isOptimalChance=false;
    }

    for (const auto &it: condition_list)
    {
        colName.push_back(it.name);
        cond.push_back(RM::Condition((int)it.op));
        switch(it.val.type)
        {
            case common::attrtype::SQL_INT:
                str.resize(sizeof(int), 0);
                memcpy(&str[0],(char *)&it.val.i,sizeof(int));
                break;
            case common::attrtype::SQL_FLOAT:
                str.resize(sizeof(float), 0);
                memcpy(&str[0],(char *)&(it.val.r),sizeof(float));
                break;
            case common::attrtype::SQL_CHAR:
                str.resize(it.val.str.size(), 0);
                memcpy(&str[0],it.val.str.c_str(),it.val.str.size());
                break;
        }
        if(isOptimalChance&&!isExecEqual&&it.op==Operator::EQUAL&&catalog_manager.checkIndex(table_name,it.name))
        {
            isExecEqual=true;
            equalID=index_manager.find(catalog_manager.getIndexName(table_name,it.name),(unsigned char *)str.c_str());
        }
        operand.push_back(str);
    }

    if(isExecEqual)
    {
        if (equalID != -1) {
            record=record_manager.getRawData(table_name,equalID);
            r=record_manager.checkRecord(record.c_str(),table_name,colName,cond,operand);
            if(r) {
                // todo
                records.push_back(record);
            }
        }
        else r = false;
    }
    else
    {
        r= record_manager.selectRecord(table_name,colName,cond,operand,records,ids);
    }
    /*打印records*/
    if (!r)
        return false;
    displaySelect(table_name, records);
    std::cout << records.size() << " rows in set ";
    return r;
}

void API::removeIndices(const std::vector<int> &ids, std::string table_name) {

    auto& catalog_manager = API::getCM();
    auto& index_manager = API::getIM();
    auto& record_manager = API::getRM();

    Table table = catalog_manager.getTableByName(table_name).value();
    for (auto attr: table.attrs) {
        auto index = catalog_manager.getIndexName(table_name, attr.first);
        if (index != ""){
            size_t offset = table.getOffset(attr.first);
            for (auto id : ids) {
                auto raw_data = record_manager.getRawData(table_name, id);
                index_manager.remove(index, (unsigned char*)(raw_data.c_str() + offset));
            }
        }
    }
}

bool API::deleteOperation(const std::string &table_name, const std::vector<Condition> &condition_list) {
    auto& catalog_manager = API::getCM();
    auto& index_manager = API::getIM();
    auto& record_manager = API::getRM();

    std::vector<std::string> colName;
    std::vector<RM::Condition> cond;
    std::vector<std::string> operand;
    std::string str;
    std::vector<std::string> indices;
    std::vector<std::string> records;
    std::vector<int> ids;
    std::string record;

    bool isOptimalChance=true;
    bool isExecEqual=false;
    int equalID;
    bool r;
    indices =catalog_manager.getAllIndices(table_name);
    int deleteNum=0;

    if (indices.size() == 0 || condition_list.size() == 0)
    {
        isOptimalChance=false;
    }
   
    for (const auto &it: condition_list)
    {
        colName.push_back(it.name);
        cond.push_back(RM::Condition((int)it.op));
        switch(it.val.type)
        {
            case common::attrtype::SQL_INT:
                str.resize(sizeof(int), 0);
                memcpy(&str[0],(char *)&it.val.i,sizeof(int));
                break;
            case common::attrtype::SQL_FLOAT:
                str.resize(sizeof(float), 0);
                memcpy(&str[0],(char *)&(it.val.r),sizeof(float));
                break;
            case common::attrtype::SQL_CHAR:
                str.resize(it.val.str.size(), 0);
                memcpy(&str[0],it.val.str.c_str(),it.val.str.size());
                break;
        }
        if(isOptimalChance&&!isExecEqual&&it.op==Operator::EQUAL&&catalog_manager.checkIndex(table_name,it.name))
        {
            isExecEqual=true;
            equalID=index_manager.find(catalog_manager.getIndexName(table_name,it.name),(unsigned char *)str.c_str());
        }
        operand.push_back(str);
    }

    if(isExecEqual==true)
    {
        r = false;
        if (equalID != -1) {
            record=record_manager.getRawData(table_name,equalID);
            r=record_manager.checkRecord(record.c_str(),table_name,colName,cond,operand);
        }
        if(r==true)
        {
            API::removeIndices({ equalID }, table_name);
            r=record_manager.removeRecord(table_name,equalID);
            deleteNum=1;
        }
        else
        {
            deleteNum=0;
            r=true;
        }
    }
    else
    {
        r= record_manager.selectRecord(table_name,colName,cond,operand,records,ids);
        API::removeIndices(ids, table_name);
        r= record_manager.removeRecord(table_name,ids);
        deleteNum=ids.size();
    }

    // remove the index
    std::cout<<"Query Ok "<<records.size()<<" rows affected ";
    return r;
}
