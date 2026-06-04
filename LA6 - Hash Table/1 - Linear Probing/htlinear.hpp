#include <cstdlib>
#include <iostream>
#include <functional>
#include "hashtable.hpp"
using namespace std;

template <typename K>
class HTLinear : public HashTable<K> {
    // IMPLEMENT ME
    
    K* table; // hash table (array)
    int N; // capacity of the hash table
    int count; // number of elements currently occupying the hash table
    
    
    public:
    HTLinear<K>(int N){
        this->N = N;
        count = 0;
        table = new K[N]; // table
    }
    
    int hash_code(K key){
        
        hash<K> hasher;
        return hasher(key); // hasher
        // return key;
    }
    
    int compress(int code){
        // MAD method
        return ((59 * code + 17) % 509) % N;
    }
    
    int insert(K key){
        
        // Step 1: check for full
        if(count == N){
            throw logic_error("Table already full");
        }
        
        int hash = this->hashfn(key);
        int collisions = 0, start = hash;
        
        
        do{
            if(table[hash] == key){
                throw logic_error("Already added key " + to_string(key));
            }
            
            if(table[hash] == 0 || table[hash] == -1){
                table[hash] = key;
                count++;
                return collisions;
            }
            
            hash = (hash + 1) % N;
            collisions++;
            
            if(start == hash){
                break;
            }
            
        }while(true);
        
        return collisions;
    }
    
    int search(K key){
        int hash = this->hashfn(key);
        int collisions = 0, start = hash;
        
        while(table[hash] != 0){
            if(table[hash] == key){
                return collisions;
            }
            
            hash = (hash + 1) % N;
            collisions++;
            
            if(start == hash){
                break;
            }
            
        }
        
        return -1;
    }
    
    int remove(K key){
        int hash = this->hashfn(key);
        int collisions = 0, start = hash;
        
        do{
            
            if(table[hash] == key){
                table[hash] = -1;
                count--;
                return collisions;
            }
            
            if(table[hash] == 0){
                return -1;
            }
            
            hash = (hash + 1) % N;
            collisions++;
            
            if(start ==  hash){
                break;
            }
            
        }while(start != hash);
        
        return -1; // not in the hash table
    }
    void print(){
        
        for(int i = 0; i < N; i++){
            cout << i << "\t";
        }
        
        cout << endl;
        
        for(int i = 0; i < N; i++){
            if(table[i] == 0 || table[i] == -1){
                cout << 0 << "\t";
            }else{
                cout << table[i] << "\t";
            }
        }
        
        cout << endl;
    }
    
};