//
// Created by logos on 2019/6/2.
//
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include "../API/API.h"
#include "../BufferManager/BufferManager.h"
#include "BPTreeElement.h"
#include "BPTree.h"

using namespace std;

// States
const int BPTree::BPTREE_FAILED = -1;
const int BPTree::BPTREE_NORMAL = 0;
const int BPTree::BPTREE_ADD = 1;
const int BPTree::BPTREE_REMOVE = 2;
const int BPTree::BPTREE_CHANGE = 3;

// Create B+ Tree file
using namespace BM;
using namespace std;
void BPTree::createFile(string _fileName, int _length, int _order)
{
    // Calculate order if not provided
    if (_order < 0)
        _order = (PAGESIZE - 8) / (_length + 4) + 1;

    // Create file
    BufferManager &bm=API::getBM();
    auto toWrite = bm.createPage("data/" + _fileName + ".mdb");
    int header[] = {_order, _length, 0, -1, -1};
    toWrite->modify(reinterpret_cast<char*>(header),0,sizeof(header));
//    FILE* file = fopen(("data/" + _fileName + ".mdb").c_str(), "wb");
//
//    fwrite(header, 4, 5, file);
//    fclose(file);
}

// Constructor
BPTree::BPTree(string _fileName): fileName(_fileName)
{
    BufferManager &bm=API::getBM();
    std::cout << _fileName << std::endl;
    Page* page = bm.getPage(_fileName, 0);
//    cout<<"Page gotten"<<endl;
    unsigned char * data = &(page->data[0]);
    int * idata=(reinterpret_cast<int*>(data));
  //  cout<<idata[0]<<idata[1]<<idata[2]<<idata[3]<<idata[4]<<endl;
    // Get header information
    order = *(reinterpret_cast<int*>(data));
    length = *(reinterpret_cast<int*>(data + 4));
    nodeCount = *(reinterpret_cast<int*>(data + 8));
    root = *(reinterpret_cast<int*>(data + 12));
    firstEmpty = *(reinterpret_cast<int*>(data + 16));

    key = new unsigned char[length];
  //  cout<<order<<length<<nodeCount<<root<<firstEmpty<<endl;
}

// Destructor
BPTree::~BPTree()
{
    delete[] key;
}

// Find value of key
int BPTree::find(unsigned char* _key)
{
    memcpy(key, _key, length);
    return root < 0 ? BPTREE_FAILED : find(root);
}

// Add key-value pair. Return true if success
bool BPTree::add(unsigned char* _key, int _value)
{
    memcpy(key, _key, length);
    value = _value;
    cout<<root<<endl;
    int res = root < 0 ? BPTREE_ADD : add(root);
    cout<<"cccp"<<endl;
    if (res == BPTREE_ADD)
    {
        // Create new root
        int newRoot = getFirstEmpty();
        cout<<newRoot<<endl;
        cout<<"Before new"<<endl;
        BPTreeElement* node = new BPTreeElement(fileName, newRoot, length, root < 0, root < 0 ? -1 : root);
        cout<<"After new"<<endl;
        node->insert(0, key, value);
        cout<<"After insert"<<endl;
        delete node;
        cout<<"After delete"<<endl;
        root = newRoot;
    }
    updateHeader();
    cout<<"after updateHeader"<<endl;
    return res != BPTREE_FAILED;
}

// Remove key-value pair. Return true if success
bool BPTree::remove(unsigned char* _key)
{
    memcpy(key, _key, length);
    int res = root < 0 ? false : remove(root, 0, true, NULL);
    updateHeader();
    return res != BPTREE_FAILED;
}

#ifdef DEBUG
// Print tree structure
void BPTree::debugPrint()
{
    cerr << "DEBUG: [BPTree::debugPrint] Debug print start." << endl;
    cerr << "Node number = " << nodeCount << ", first empty = " << firstEmpty << endl;
    if (root >= 0)
    {
        cerr << "Root = " << root << endl;
        debugPrint(root);
    }
    else
        cerr << "Empty tree." << endl;
    cerr << "DEBUG: [BPTree::debugPrint] Debug print end." << endl;
}
#endif

// Recursive function for finding value
int BPTree::find(int id)
{
    BPTreeElement* node = new BPTreeElement(fileName, id, length);
    int pos = node->findPosition(key);

    int ret = BPTREE_FAILED;
    if (node->isLeaf())
    {
        // Check if key is found
        if (pos > 0)
        {
            unsigned char* k = node->getKey(pos);
            if (memcmp(key, k, length) == 0)
                ret = node->getPointer(pos);
        }
    }
    else
        ret = find(node->getPointer(pos));

    delete node;
    return ret;
}

// Recursive function for adding key-value pair
int BPTree::add(int id)
{
    BPTreeElement* node = new BPTreeElement(fileName, id, length);
    int pos = node->findPosition(key);

    int res = node->isLeaf() ? BPTREE_ADD : add(node->getPointer(pos));
    int ret = BPTREE_NORMAL;

    if (node->isLeaf() && pos > 0)
    {
        // Check for duplicate
        unsigned char* k = node->getKey(pos);
        if (memcmp(key, k, length) == 0)
            res = BPTREE_FAILED;
    }

    if (res == BPTREE_FAILED)
        // Duplicate key
        ret = BPTREE_FAILED;
    else if (res == BPTREE_ADD)
    {
        // Add new key-value
        node->insert(pos, key, value);

        if (node->getSize() >= order)
        {
            // Node full. Split
            int newId = getFirstEmpty();
            BPTreeElement* newNode = node->split(newId, key);
            value = newId;

            delete newNode;
            ret = BPTREE_ADD;
        }
    }

    delete node;
    return ret;
}

// Recursive function for deleting key-value pair
int BPTree::remove(int id, int sibId, bool leftSib, unsigned char* parentKey)
{
    BPTreeElement* node = new BPTreeElement(fileName, id, length);
    BPTreeElement* sib = nullptr;
    if (id != root)
        sib = new BPTreeElement(fileName, sibId, length);
    int pos = node->findPosition(key);

    int res;
    if (node->isLeaf())
        res = BPTREE_FAILED;
    else
    {
        int nxtId = node->getPointer(pos);
        int nxtSib = node->getPointer(pos > 0 ? pos - 1 : pos + 1);
        unsigned char* nxtParentKey = node->getKey(pos > 0 ? pos : pos + 1);
        res = remove(nxtId, nxtSib, pos > 0, nxtParentKey);
    }

    if (node->isLeaf())
    {
        // Check if key is found
        if (pos > 0)
        {
            unsigned char* k = node->getKey(pos);
            if (memcmp(key, k, length) == 0)
                res = BPTREE_REMOVE;
        }
    }

    int ret = BPTREE_NORMAL;
    if (res == BPTREE_FAILED)
        // Key not found
        ret = BPTREE_FAILED;
    else if (res == BPTREE_CHANGE)
        // Change key
        node->setKey(pos > 0 ? pos : pos + 1, key);
    else if (res == BPTREE_REMOVE)
    {
        // Delete key
        node->remove(pos > 0 ? pos : pos + 1);

        if (id == root)
        {
            if (node->getSize() == 0)
            {
                root = node->getPointer(0);
                removeBlock(id);
                node->setRemoved();
            }
        }
        else
        {
            int lim = (order+1)/2 - 1;
            if (node->getSize() < lim)
            {
                if (sib->getSize() > lim)
                {
                    // Borrow key from sibling
                    unsigned char* k = node->borrow(sib, leftSib, parentKey);
                    memcpy(key, k, length);
                    ret = BPTREE_CHANGE;
                }
                else
                {
                    // Merge sibling
                    if (leftSib)
                    {
                        sib->mergeRight(node, parentKey);
                        removeBlock(id);
                        node->setRemoved();
                    }
                    else
                    {
                        node->mergeRight(sib, parentKey);
                        removeBlock(sibId);
                        sib->setRemoved();
                    }
                    ret = BPTREE_REMOVE;
                }
            }
        }
    }

    delete node;
    if (sib != nullptr)
        delete sib;
    return ret;
}

// Get first empty block id
int BPTree::getFirstEmpty()
{
    BufferManager &bm=API::getBM();

    if (firstEmpty < 0)
        {
        bm.createPage(fileName);
        return ++nodeCount;
        }

    int ret = firstEmpty;
    Page* page = bm.getPage(fileName, firstEmpty);
    firstEmpty = *(reinterpret_cast<int*>(&(page->data[0])));
    return ret;
}

// Remove block in file
void BPTree::removeBlock(int id)
{
    BufferManager &bm=API::getBM();

    Page* page = bm.getPage(fileName, id);
    memcpy(&(page->data[0]), &firstEmpty, 4);
    firstEmpty = id;
}

// Update header information
void BPTree::updateHeader()
{
    BufferManager &bm=API::getBM();
    Page* page = bm.getPage(fileName, 0);
    unsigned char *data=&(page->data[0]);
    memcpy(data + 8, &nodeCount, 4);
    memcpy(data + 12, &root, 4);
    memcpy(data + 16, &firstEmpty, 4);

    page->setDirty();
}

#ifdef DEBUG
// Recursive function for tree structure printing
void BPTree::debugPrint(int id)
{
    BPTreeElement* node = new BPTreeElement(fileName.c_str(), id, length);

    cerr << "Block id = " << id << ", isLeaf = " << node->isLeaf() << endl;
    cerr << "Keys:";
    for (int i = 1; i <= node->getSize(); i++)
    {
        cerr << " ";
        unsigned char* k = node->getKey(i);
        for (int j = 0; j < length; j++)
        {
            cerr << (int)k[j];
            if (j < length-1)
                cerr << "~";
        }
    }
    cerr << endl;
    cerr << "Pointers: ";
    for (int i = 0; i <= node->getSize(); i++)
        cerr << " " << node->getPointer(i);
    cerr << endl;

    if (!node->isLeaf())
        for (int i = 0; i <= node->getSize(); i++)
            debugPrint(node->getPointer(i));

    delete node;
}
#endif

