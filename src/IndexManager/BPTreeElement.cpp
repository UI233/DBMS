//
// Created by logos on 2019/6/1.
//
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <exception>
#include "BPTreeElement.h"
#include "../BufferManager/BufferManager.h"
#include "../API/API.h"
using namespace std;
using namespace BM;
// Constructor from file
BPTreeElement::BPTreeElement(string _fileName, int _id, int _length):
 fileName(_fileName), id(_id), length(_length) {
    BufferManager &bm=API::getBM();
    Page *page = bm.getPage(_fileName+ ".mdb", id);
    unsigned char * data = &(page->data[0]);
    size = *(reinterpret_cast<int*>(data));
    keys.push_back(nullptr);
    ptrs.push_back(*(reinterpret_cast<int*>(data + 4)));
    leaf = ptrs[0] < 0;
    blockRemoved = false;

   // cout<<endl<<"ppp"<<size<<leaf<<blockRemoved<<endl;
    int bias = 8;
    for (int i = 1; i <= size; i++)
    {
        unsigned char* k = new unsigned char[length];
        memcpy(k, data + bias, length);
        keys.push_back(k);
        ptrs.push_back(*reinterpret_cast<int*>(data + bias + length));
        bias += length + 4;
    }
}

// Constructor for an empty node
BPTreeElement::BPTreeElement(string _fileName, int _id, int _length, bool _leaf, int firstPtr)
        : fileName(_fileName), id(_id), length(_length), leaf(_leaf) {
    size = 0;
    keys.push_back(nullptr);
    ptrs.push_back(firstPtr);
    dirty = true;
    blockRemoved = false;
}

// Destructor
BPTreeElement::~BPTreeElement()
{
    // Write modification to block
    if (dirty && !blockRemoved)
    {
      //  cout<<"Into ~"<<endl;
        BufferManager &bm=API::getBM();
        Page* page = bm.getPage(fileName+ ".mdb", id);
      //  cout<<"After get page"<<endl;
        unsigned char * data = &(page->data[0]);

     //   cout<<"Before memcpy"<<endl;
        // Update size
        memcpy(data, &size, 4);

        // Update first pointer
        memcpy(data + 4, &ptrs[0], 4);
      //  cout<<"Finish memcpy"<<endl;
        // Update key-pointer
        int bias = 8;
        for (int i = 1; i <= size; i++)
        {
            memcpy(data + bias, keys[i], length);
            memcpy(data + bias + length, &ptrs[i], 4);
            bias += length + 4;
        }
        page->setDirty();
    }

    // Clean up keys
    for (auto k : keys)
        if (k != nullptr)
            delete[] k;
}
// Get node size
int BPTreeElement::getSize() const
{
    return size;
}

// Get key length
int BPTreeElement::getKeyLength()const
{
    return length;
}

// If node is leaf
bool BPTreeElement::isLeaf() const
{
    return leaf;
}

// Get key
unsigned char* BPTreeElement::getKey(int pos) const
{
    if (pos > size || pos <= 0)
    {
        throw std::runtime_error("ERROR: [BPTreeElement::getKey] Position out of range!");
        return nullptr;
    }

    return keys[pos];
}

// Get pointer
int BPTreeElement::getPointer(int pos) const
{
    if (pos > size || pos < 0)
    {
        throw  std::runtime_error("ERROR: [BPTreeElement::getKey] Position out of range!");
        return -1;
    }
    return ptrs[pos];
}

// Find key's position
int BPTreeElement::findPosition(unsigned char *key) const {
    return upper_bound(
            keys.begin() + 1, keys.end(), key,
            [&](unsigned char *a, unsigned char *b) {
                return memcmp(a, b, length) < 0;
            }
    ) - (keys.begin() + 1);
}

// Set key at position
void BPTreeElement::setKey(int pos, unsigned char* key)
{
    if (pos > size || pos <= 0)
    {
        throw std::runtime_error("ERROR: [BPTreeElement::setKey] Position out of range!");
        return;
    }

    dirty = true;
    memcpy(keys[pos], key, length);
}

// Set pointer at position
void BPTreeElement::setPointer(int pos, int ptr)
{
    if (pos > size || pos < 0)
    {
        throw std::runtime_error("ERROR: [BPTreeElement::setPointer] Position out of range!");
        return;
    }

    dirty = true;
    ptrs[pos] = ptr;
}

// Set block as removed
void BPTreeElement::setRemoved()
{
    blockRemoved = true;
}

// Insert key-pointer after position
void BPTreeElement::insert(int pos, unsigned char* key, int ptr)
{
    if (pos > size || pos < 0)
    {
        throw std::runtime_error("ERROR: [BPTreeElement::insert] Position out of range!");
        return;
    }

    dirty = true;
    unsigned char* k = new unsigned char[length];
    memcpy(k, key, length);
    if (pos == size)
    {
        keys.push_back(k);
        ptrs.push_back(ptr);
    }
    else
    {
        keys.insert(keys.begin() + pos + 1, k);
        ptrs.insert(ptrs.begin() + pos + 1, ptr);
    }
    size++;
}

// Rmove key-pointer at position
void BPTreeElement::remove(int pos)
{
    if (pos > size || pos <= 0)
    {
        throw std::runtime_error("ERROR: [BPTreeElement::insert] Position out of range!");
        return;
    }

    dirty = true;
    if (pos == size)
    {
        keys.pop_back();
        ptrs.pop_back();
    }
    else
    {
        keys.erase(keys.begin() + pos);
        ptrs.erase(ptrs.begin() + pos);
    }
    size--;
}

// Split into two nodes. Return new node
BPTreeElement* BPTreeElement::split(int newId, unsigned char* newKey)
{
    dirty = true;

    int pos = size/2 + (leaf ? 0 : 1);
    memcpy(newKey, keys[size/2 + 1], length);
    BPTreeElement* ret = new BPTreeElement(fileName, newId, length, leaf, leaf ? -1 : ptrs[pos]);

    // Copy former half of keys-pointers to new node
    for (pos++; pos <= size; pos++)
        ret->insert(ret->getSize(), keys[pos], ptrs[pos]);

    size /= 2;
    keys.resize(size + 1);
    ptrs.resize(size + 1);

    return ret;
}

// Borrow a key from sibling. Return new parent key
unsigned char* BPTreeElement::borrow(BPTreeElement* sib, bool leftSib, unsigned char* parentKey)
{
    dirty = true;

    if (leftSib)
    {
        // Borrow from left sibling
        int sibSize = sib->getSize();
        unsigned char* sibKey = sib->getKey(sibSize);
        int sibPtr = sib->getPointer(sibSize);
        sib->remove(sibSize);

        if (leaf)
            insert(0, sibKey, sibPtr);
        else
        {
            int ptr = ptrs[0];
            ptrs[0] = sibPtr;
            insert(0, parentKey, ptr);
        }

        return sibKey;
    }
    else
    {
        // Borrow from right sibling
        unsigned char* sibKey = sib->getKey(1);
        int sibPtr0 = sib->getPointer(0);
        int sibPtr1 = sib->getPointer(1);
        sib->remove(1);

        if (leaf)
        {
            insert(size, sibKey, sibPtr1);
            return sib->getKey(1);
        }
        else
        {
            sib->setPointer(0, sibPtr1);
            insert(size, parentKey, sibPtr0);
            return sibKey;
        }
    }
}

// Merge right sibling
void BPTreeElement::mergeRight(BPTreeElement* sib, unsigned char* parentKey)
{
    dirty = true;

    int sibSize = sib->getSize();
    if (!leaf)
        insert(size, parentKey, sib->getPointer(0));
    for (int i = 1; i <= sibSize; i++)
        insert(size, sib->getKey(i), sib->getPointer(i));
}
