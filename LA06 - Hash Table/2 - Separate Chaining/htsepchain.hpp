
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "hashtable.hpp"
#include "linkedlist.hpp"
using namespace std;

class HTSepChain : public HashTable {
    // IMPLEMENT ME
    
    // LinkedList* list or LinkedList** list ??? 
    LinkedList** table; // hash table (array of linked list)
    int N; // capacity of the hash table
    
    public:
    HTSepChain(int N){
        this->N = N;
        table = new LinkedList*[N];
        
        for(int i = 0; i < N; i++){
            table[i] = new LinkedList();
        }
        
    }
    
    int hash_code(string key){
        int code = 0, a = 5;
        
        for(int i = 0; i < key.length(); i++){
            code = code * a + key[i];
        }
        
        return (int)(code);
    }
    
    int compress(int code){
        return code % N; // ok
    }
    
    int insert(string key){
        int index = this->hashfn(key);
        
        node* curr = table[index]->getHead();
        while(curr){
            if(curr->elem == key){
                throw logic_error("Already added key " + key);
            }
            
            curr = curr->next;
        }
        
        table[index]->add(key);
        return table[index]->sizeLL();
    }
    
    int search(string key){
        int index = this->hashfn(key);
        // node* curr = table[index]->getHead();
        
        // while(curr){
        //     if(curr->elem == key){
        //         return table[index]->sizeLL();
        //     }
            
        //     curr = curr->next;
        // }
        
        // return -1;
        
        return table[index]->search(key);
    }
    
    int remove(string key){
        int index = this->hashfn(key);
        
        node* curr = table[index]->getHead();
        
        while(curr){
            if(curr->elem == key){
                table[index]->remove(key);
                return table[index]->sizeLL();
            }
            
            curr = curr->next;
        }
        
        return -1;
    }
    void print(){
        
        for(int i = 0; i < N; i++){
            cout << i << "\t";
            table[i]->print();
            
            cout << endl; 
        }
        
        cout << endl;
    }
    
    
};