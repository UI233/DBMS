//
// Created by logos on 2019/6/1.
//

#ifndef DBMS_BPTREEELEMENT_H
#define DBMS_BPTREEELEMENT_H
#include <string>
#include <vector>
using namespace std;
class BPTreeElement{
public:

    // Constructor
    BPTreeElement(string _fileName, int _id, int _length);
    BPTreeElement(string _fileName, int _id, int _length, bool _leaf, int firstPtr);

    // Destructor
    ~BPTreeElement();

    // Get node size
    int getSize() const;

    // Get key length
    int getKeyLength() const;

    // If node is leaf
    bool isLeaf() const;

    // Get key
    unsigned char* getKey(int pos) const;

    // Get pointer
    int getPointer(int pos) const;

    // Find key's position
    int findPosition(unsigned char* key) const;

    // Set key at position
    void setKey(int pos, unsigned char* key);

    // Set pointer at position
    void setPointer(int pos, int ptr);

    // Set the block as removed
    void setRemoved();

    // Insert key-pointer after position
    void insert(int pos, unsigned char* key, int ptr);

    // Remove key-pointer at position
    void remove(int pos);

    // Split into two nodes. Return new node
    BPTreeElement* split(int newId, unsigned char* newKey);

    // Borrow a key from sibling. Return new parent key
    unsigned char* borrow(BPTreeElement* sib, bool leftSib, unsigned char* parentKey);

    // Merge right sibling
    void mergeRight(BPTreeElement* sib, unsigned char* parentKey);

private:

    // Node file name
    string fileName;

    // Block id in file
    int id;

    // Node size
    int size;

    // Length of each key
    int length;

    // If node is leaf
    bool leaf;

    // If node has been modified
    bool dirty;

    // If block has been removed
    bool blockRemoved;

    // Node keys
    vector<unsigned char*> keys;

    // Node pointers
    vector<int> ptrs;

};
#endif //MYMINISQL_BPTREEELEMENT_H
