#include "node.hpp"
#include <iostream>
#include <climits>
#include <cstdlib>

using namespace std;
class Heap {
    
    node** arr;
    int capacity;
    int heapsize;
    
    void swap_node(node*& a, node*& b){
        node* temp = a;
        a = b;
        b = temp;
    }
    
    void heapifyUp(int i){
        
        while(i > 0){
            int parent = (i - 1) / 2;
            
            if(arr[i]->weight < arr[parent]->weight){
                swap_node(arr[i], arr[parent]);
                i = parent;
            }else{
                break;
            }
            
        }
        
    }
    
    void heapifyDown(int i){
        
        while(true){
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            
            if(left < heapsize && arr[left]->weight < arr[smallest]->weight){
                smallest = left;
            }
            
            if(right < heapsize && arr[right]->weight < arr[smallest]->weight){
                smallest = right;
            }
            
            
            // both children equal and smaller, choose LEFT
            if(left < heapsize && right < heapsize){
                if(arr[left]->weight == arr[right]->weight && arr[left]->weight < arr[i]->weight){
                    smallest = left;
                }
            }
            
            
            if(smallest != i){
                swap_node(arr[i], arr[smallest]);
                i = smallest;
            }else{
                break;
            }
        }
        
    }
    
	public:
	Heap(){
	    capacity = 100;
	    heapsize = 0;
	    
	    arr = (node**) calloc(capacity, sizeof(node*));
	}
	
    // TODO insert
	void insert(node* n) {
        
        if(heapsize >= capacity){
            return;
        }
        
        arr[heapsize] = n;
        heapifyUp(heapsize);
        heapsize++;
	}

    // TODO removeMin
	node* removeMin() {
// 		return nullptr;

        if(heapsize == 0){
            return nullptr;
        }
        
        node* minNode = arr[0]; // minHeap 
        arr[0] = arr[heapsize - 1];
        heapsize--;
        
        if(heapsize > 0){
            heapifyDown(0);
        }
        
        return minNode;
	}

    // TODO size
	int size() {
// 		return 0;
        return heapsize;
	}
};