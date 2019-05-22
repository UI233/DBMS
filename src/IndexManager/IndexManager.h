#ifndef DBMS_INDEXMANAGER_H
#define DBMS_INDEXMANAGER_H
#include <BPTree.h>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <map>
namespace IM{
    include <string>
    enum SQL_Value_Type{

    };
    class IM {
    public:
        IM() = default;
        ~IM() = default;

        // add a file to a specific BPTree based on the type
        // @param: the name of file, element type of the BPTree
        // @throw: std::invalid_argument("Invalid Element Type") for invalid type input
        // @return: a bool whether the instruction is completed
        bool create(const string &filename, const SQL_Value_Type &type);

        // delete a file from the BPTree
        // @param: the name of file, element type of the BPTree
        // @throw: std::invalid_argument("Invalid Element Type") for invalid type input
        // @return: a bool whether the instruction is completed
        bool drop(const string &filename, const SQL_Value_Type &type);

        // search a element from a file
        // @param: the name of file, an element to search for
        // @throw: std::invalid_argument("Invalid Element Type") for invalid type input
        // @return: the offset of the element, 0 indicates not found, -1 indicate error
        int search(const string &filename, const Element &e);

        // search the node of the file in BPTree
        // @param: the name of file, an element type
        // @throw: std::invalid_argument("Invalid Element Type") for invalid type input
        // @return: the offset of the element, 0 indicates not found, -1 indicate error
        int searchHead(const string &filename, SQL_Value_Type type);

        // search the node next to the file in BPTree
        // @param: the name of file, an element type
        // @throw: std::invalid_argument("Invalid Element Type") for invalid type input
        // @return: the offset of the element, 0 indicates not found, -1 indicate error
        int searchNext(const string &filename, SQL_Value_Type type);

        // free the temporary attributes used in search
        // @param: the name of file, an element type
        // @throw: std::invalid_argument("Invalid Element Type") for invalid type input
        // @return: true for success, false for failure
        bool finishSearch(const string &filename, SQL_Value_Type type);

        // insert a element to a file at a certain offset
        // @param: the name of file, an element to insert, the offset
        // @throw: std::invalid_argument("Invalid Element Type") for invalid type input
        // @return: true for success, false for failure
        bool insert(const string &filename, const Element &e, int offset);

        // delete a element from a file
        // @param: the name of file, an element to insert
        // @throw: std::invalid_argument("Invalid Element Type") for invalid type input
        // @return: true for success, false for failure
        bool removeKey(const string &filename, const Element &e);

    private:
        typedef map<string, BPTree<int> *> intMap;
        typedef map<string, BPTree<float> *> floatMap;
        typedef map<string, BPTree<string> *> charMap;
        typedef map<string, NodeSearchParse<int>> intOMap;
        typedef map<string, NodeSearchParse<float>> floatOMap;
        typedef map<string, NodeSearchParse<string>> charOMap;

        intMap intIndexMap;
        floatMap floatIndexMap;
        charMap charIndexMap;
        intOMap intOffsetMap;
        floatOMap floatOffsetMap;
        charOMap charOffsetMap;

        BPTree<int> *intBPTree;
        BPTree<float> *floatBPTree;
        BPTree<string> *charBPTree;

        intMap::iterator intBPIterator;
        floatMap::iterator floatBPIterator;
        charMap::iterator charBPIterator;
    };

}


#endif //DBMS_INDEXMANAGER_H
