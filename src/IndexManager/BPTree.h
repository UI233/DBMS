//
// Created by logos on 2019/5/12.
//

#ifndef DBMS_BPTREE_H
#define DBMS_BPTREE_H


#include <vector>
#include <string>
#include "BPTreeElement.h"

using namespace std;

class BPTree

{
public:

    // Create B+ tree file
    static void createFile(string _fileName, int _keyLength, int _order = -1);

    // Constructor
    BPTree(string _fileName);

    // Destructor
    ~BPTree();

    // Find value of key
    int find(unsigned char* _key);

    // Add key-value pair. Return true if success
    bool add(unsigned char* _key, int _value);

    // Remove key-value pair. Return true if success
    bool remove(unsigned char* _key);

#ifdef DEBUG
    // Print tree structure
    void debugPrint();
#endif

private:

    // States
    static const int BPTREE_FAILED;
    static const int BPTREE_NORMAL;
    static const int BPTREE_ADD;
    static const int BPTREE_REMOVE;
    static const int BPTREE_CHANGE;

    // Order of BPTree
    int order;

    // Length of each key
    int length;

    // Total number of nodes
    int nodeCount;

    // Block id of root
    int root;

    // First empty block in file
    int firstEmpty;

    // Binary file name
    string fileName;

    // Key-value to maintain
    unsigned char* key;
    int value;

    // Recursive function for finding value
    int find(int id);

    // Recursive function for adding key-value pair
    int add(int id);

    // Recursive function for deleting key-value pair
    int remove(int id, int sibId, bool leftSib, unsigned char* parentKey);

    // Get first empty block id
    int getFirstEmpty();

    // Remove block in file
    void removeBlock(int id);

    // Update header information
    void updateHeader();

#ifdef DEBUG
    // Recursive function for tree structure printing
    void debugPrint(int id);
#endif
};

#endif //DBMS_BPTREE_H
