#ifndef DBMS_INDEXMANAGER_H
#define DBMS_INDEXMANAGER_H
#include <string>
namespace IM {
    class IndexManager {
    public:
        using string = std::string;

        // Find key in index. Return record id
        int find(string indexName, unsigned char *key);

        // Insert key into index. Return true if success
        bool insert(string indexName, unsigned char *key, int value);


        // Delete key from index. Return true if success
        bool remove(string indexName, unsigned char *key);

        // Create index. Return true if success
        bool createIndex(string indexName);

        // Drop index. Return true if success
        bool dropIndex(string indexName);
    };
}


#endif //DBMS_INDEXMANAGER_H
