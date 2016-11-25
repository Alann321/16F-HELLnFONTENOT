#ifndef HASHTABLE
#define HASHTABLE

#include "DSString.h"

template <class K, class V>
class hashnode{
private:
    //key value pair
    K key;
    V value;
public:

    //base constructor
    hashnode(K key, V value) {
        this->key = key;
        this->value = value;
    }

    //getter
    K getKey() {
        return key;
    }

    void setValue(V inValue){
        this->value = inValue;
    }

    V getValue() {
        return value;
    }
};


template <class K, class V>
class hashtable {
private:

    hashnode<K,V> **table;

    int size;

public:

    int hashFcn(K key);
    
    hashtable() {
        size = 128;
        table = new hashnode<K,V>*[size];
        for (int i = 0; i < size; i++){
            table[i] = nullptr;
        }
    }

    hashtable(hashtable<K,V>& intable){
        size = intable.size;
        table = new hashnode<K,V>*[size];
        for (int i = 0; i < size; i++){
            if(intable.table[i] == nullptr){
                table[i] = nullptr;
            }
            else{
                table[i] = new hashnode<K,V>(intable.table[i]->getKey(),
                                        intable.table[i]->getValue());
            }
        }
    }

    V get(K key) {

        int hash = (hashFcn(key) % size);

        while (table[hash] != nullptr && table[hash]->getKey() != key){
            hash = (hash + 1) % size;
        }

        if (table[hash] == nullptr){
            return -1;
        }

        else{
            return table[hash]->getValue();
        }
    }

    void put(K key, V value) {

        int hash = (hashFcn(key) % size);

        int count = 0;
        while (table[hash] != nullptr && table[hash]->getKey() != key){
            count++;

            if(count >= size){
                std::cout << "RESIZE NEEDED" <<std::endl;
                resize();
                hash = (hashFcn(key) % size);
                count = 0;
            }

            else{
                hash = (hash + 1) % size;
            }

        }

        if (table[hash] != nullptr){
            delete table[hash];
        }

        table[hash] = new hashnode<K, V>(key, value);
    }

    ~hashtable() {
        for (int i = 0; i < size; i++){
              if (table[i] != nullptr){
                    //delete value at entry
                    delete table[i];
              }
        }
        delete[] table;
    }

    void resize(){
        hashnode<K,V> ** tmpTable = new hashnode<K,V>*[size*2];

        for(int i = 0; i < size*2; i++){
            tmpTable[i] = nullptr;
        }

        for(int i = 0; i < size; i++ ){
            K tmpKey = table[i]->getKey();
            int tmpHash = hashFcn(tmpKey) % (size*2);

            //assign item in hash table to location in new table
            tmpTable[tmpHash] = table[i];
        }

        delete[] table;
        table = tmpTable;
        size = size*2;
    }
};


template<class K, class V>
int hashtable<K, V>::hashFcn(K key){
    return (int)std::hash<K>()(key);
}

//overloading function makes hashing much more reliable
template<>
int hashtable<DSString, DSString>::hashFcn(DSString key){
    int prox = 10;
    if(key.size() != 1){
        prox += key.strVal[0];
    }

    if(key.size() > 4){
        prox += key.strVal[4];
    }

    return (int)std::hash<int>()(prox);
}

#endif // HASHTABLE
