//
// Created by logos on 2019/6/6.
//

#include <iostream>
#include <string>
#include "BPTree.h"
#include "IndexManager.h"
#include <exception>
#include "../CatalogManager/CatalogManager.h"
#include "../BufferManager/BufferManager.h"
#include "../API/API.h"
#include "../include/common.h"
using namespace CM;
using namespace std;
using namespace IM;
// Find key in index. Return record id
int IndexManager::find(string indexName, unsigned char* key)
{
    BPTree* tree = new BPTree("index/" + indexName);
    int ret = tree->find(key);
    delete tree;
    return ret;
}

// Insert key into index. Return true if success
bool IndexManager::insert(string indexName, unsigned char* key, int value)
{

    BPTree* tree = new BPTree("index/" + indexName);
    int preCheck=tree->find(key);
    if (preCheck!=-1){
        throw std::runtime_error("ERROR: [IndexManager::insert] Duplicate Key in index.");
    }
   // std::cout<<"Complete 1"<<std::endl;
    if (!tree->add(key, value))
    {
        throw std::runtime_error("ERROR: [IndexManager::insert] Duplicate key in index.");
        delete tree;
        return false;
    }
//    std::cout<<"Complete 2"<<std::endl;
    delete tree;
    return true;
}

// Delete key from index. Return true if success
bool IndexManager::remove(string indexName, unsigned char* key)
{
    BPTree* tree = new BPTree("index/" + indexName);
    if (!tree->remove(key))
    {
        throw std::runtime_error("ERROR: [IndexManager::remove] Cannot find key in index.");
        delete tree;
        return false;
    }
    delete tree;
    return true;
}
//Todo: complete and test the left functions
// Create index. Return true if success
bool IndexManager::createIndex(string indexName, string tableName, string attributeName)
{

    CatalogManager& manager = API::getCM();
    optional<IndexInfo> index = manager.getIndex(indexName);
    if (!index)
        return false;
    optional<Table> table = manager.getTableByName(tableName);
    if (!table)
        return false;
    cout<<"table"<<endl;
    common::attrtype type=table->attrs[attributeName];
    int keyLength=type.getSize();
    cout<<"create file"<<endl;
    BPTree::createFile("index/" + common::getIndexFile(indexName, tableName, attributeName)), keyLength);
    return true;
}

// Drop index. Return true if success,l,
bool IndexManager::dropIndex(string indexName)
{
    using namespace BM;
    BufferManager &bm=API::getBM();
    bm.deleteFile("index/" + indexName);
    return true;
}
