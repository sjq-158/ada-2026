// TODO entire implementation
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

#include "list.hpp"

using namespace std;

class ArrayList : public List{
    int* arr;
    int totalSize, capacity;
    
public:
    ArrayList(){
        capacity = 5;
        totalSize = 0;
        arr = (int*) calloc(capacity, sizeof(int));
    }
    
    void insert(int num){
        // addLast
        addLast(num);
    }
    
    int get(int pos){
        if(pos > totalSize || pos < 1){
            throw logic_error("Invalid position"); 
        }
        
        return arr[pos - 1];
    }
    
    int remove(int num){
        // return -1; // TODO
        int index = 0;
        
        for(int i = 0; i < totalSize; i++){
            if(arr[i] == num){
                index = i + 1;
                // for(int j = i; j < totalSize - 1; j++){
                //     arr[j] = arr[j + 1];
                // }
                
                // totalSize--;
                // dynamic_deduce();
                removeAt(i + 1);
                break;
            }
        }
        
        return index;
    }
    
    void addAt(int num, int pos){
        if(pos - 1 > totalSize || pos < 1){
            throw logic_error("Invalid position"); 
        }
        
        pos--;
        dynamic_add(); 
        for(int i = totalSize; i > pos; i--){
            arr[i] = arr[i - 1];
        }
        
        arr[pos] = num;
        totalSize++;
    }
    
    int removeAt(int pos){
        // TODO
        // return -1;
        if(pos > totalSize || pos < 1){
            throw logic_error("Invalid position"); 
        }
        pos--;
        
        int result = arr[pos];
        
        for(int i = pos; i < totalSize; i++){
            arr[i] = arr[i + 1];
            // arr[i + 1] = arr[i];
        }
        
        totalSize--;
        dynamic_deduce();
        return result;
    }
    
    bool isEmpty(){
        return totalSize == 0;
    }
    
    int size(){
        return totalSize;
    }
    
    void print(){
        
        for(int i = 0; i < capacity; i++){
            if(i < totalSize){
                cout << arr[i] << " ";
            }else{
                cout << "? ";
            }
        }
        
        cout << endl;
    }
    
    
    // other methods
    void addFirst(int num){
        // check
        dynamic_add();
        
        for(int i = totalSize - 1; i > 0; i--){
            arr[i] = arr[i - 1];
        }
        
        arr[0] = num;
        totalSize++;
    }
    
    void addLast(int num){
        // DONE
        dynamic_add();
        arr[totalSize++] = num;
    }
    
    // addAt 
    
    int removeFirst(){
        // TODO
        // return -1;
        int res = arr[0];
        
        for(int i = 0; i < totalSize - 1; i++){
            arr[i] = arr[i + 1];
        }
        
        return res;
    }
    
    int removeLast(){
        
        return arr[--totalSize];
    }
    
    // removeAt
    
    
    // helper methods
    void dynamic_add(){
        if(totalSize >= capacity){
            capacity += ceil(capacity * 0.5);
            arr = (int*) realloc(arr, capacity * sizeof(int));
        }
    }
    
    void dynamic_deduce(){
        if(totalSize <=  (capacity * 2) / 3.00){
            int newCap = ceil(capacity * 0.75);
            
            if(newCap < 5){
                newCap = 5;
            }
            
            capacity = newCap;
            arr = (int*) realloc(arr, capacity * sizeof(int));
        }
    }
    
};