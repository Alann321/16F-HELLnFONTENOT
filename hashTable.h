//Using Secure Hash Algorithm

#include "Vector.h"
#include "LinkedList.h"
#include "DSString"
#include <sha1.h>

const TABLE_SIZE = 127;

template<typename Key, typename Value>
class HashTable
{
private:
        class HashNode
        {
            friend class HashTable;
            Key k;
            Value v;
        public:
            HashNode();
            HashNode(const Key&, const Value&);
            ~HashNode();
        };

        int bucketNum;
//        int tableSize;
        Vector<LinkedList<HashNode*>*>* table;

        int hash(const Key&)const;
        int rehash();

    public:
        HashTable();
        HashTable(const int);
        HashTable(const HashTable &);
        ~HashTable();

//        int HashTableGetSize();
        int HashTableGetBucketNumber();

        int HashTableInsert(const Key&, const Value&);
        bool IsInHashTable(const Key&, const Value&) const;
        bool IsEmptyBucket(const  int) const;
};
