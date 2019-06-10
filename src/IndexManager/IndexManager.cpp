//
// Created by logos on 2019/6/6.
//

#include <iostream>
#include <string>
#include "BPTree.h"
#include "IndexManager.h"
#include <exception>

using namespace std;
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
/*// Create index. Return true if success
bool IndexManager::createIndex(string indexName)
{
    CatalogManager* manager = MiniSQL::getCatalogManager();
    Index* index = manager->getIndex(indexName);
    if (index == NULL)
        return false;
    Table* table = manager->getTable(index->getTableName());
    if (table == NULL)
        return false;
    int keyLength = Utils::getTypeSize(table->getType(index->getColName()));

    BPTree::createFile("index/" + indexName, keyLength);
    return true;
}

// Drop index. Return true if success
bool IndexManager::dropIndex(string indexName)
{
    Utils::deleteFile("index/" + indexName);
    return true;
}*/
