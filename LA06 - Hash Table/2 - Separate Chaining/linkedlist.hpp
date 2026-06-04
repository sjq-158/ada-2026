#include "node.hpp" // string and cstring found
#include <iostream>

using namespace std;
class LinkedList {
	// IMPLEMENT ME
	node* head;
	node* tail;
	int size;
	
	public:
	LinkedList(){
	    head = nullptr;
	    tail = nullptr;
	    size = 0;
	}
	
	void add(string key){
	    
	    node* n = new node(key);

	    if(tail == nullptr){
	        head = n;
	    }else{
	        tail->next = n;
	    }
	    
	    tail = n;
	    size++;
	}
	
	int remove(string key){
	    
	    node* curr = head;
	    node* prev = nullptr;
	    int index = 0;
	    
	    while(curr){
	        
	        if(curr->elem == key){
	            
	            // check if head
	            if(curr == head){
	                head = head->next;
	                
	                if(head == nullptr){
	                    tail = nullptr; 
	                }
	                
	            }else{
	                
	                prev->next = curr->next;
	                
	                if(curr == tail){
	                    tail = prev;
	                }
	                
	            }
	            
	            delete curr;
	            size--;
	            
	            return index;
	        }
	        
	        prev = curr;
	        curr = curr->next;
	        index++;
	    }
	    
	    return -1; //  not found
	}
	
	int sizeLL(){
	    return size;
	}
	
    int search(string key){
        node* curr = head;
        int index = 0;
        
        while(curr){
            if(curr->elem == key){
                return index;
            }
            
            index++;
            curr = curr->next;
        }
        
        return -1;
    }
	
	node* getHead(){
	    return head;
	}
	
	void print(){
	    node* curr = head;
	    
	    while(curr){
	        cout << curr->elem << "\t";
	        curr = curr->next;
	    }
	}
	
	
	
	
	
	
	// miscellaneous stuff
	
	// remove
	// while(curr){
	        
	   //     if(curr->elem == key){
	            
	   //         // check if head
	   //         if(curr == head){
	   //             head = head->next;
	                
	   //             if(head == nullptr){
	   //                 tail = nullptr; 
	   //             }
	                
	   //             size--;
	                
	   //             return index;
	   //         }else{
	                
	   //             prev->next = curr->next;
	                
	   //             if(curr == tail){
	   //                 tail = prev;
	   //             }
	                
	   //             size--;
	   //             return index;
	   //         }
	            
	   //     }
	        
	   //     prev = curr;
	   //     curr = curr->next;
	   //     index++;
	   // }
	
};