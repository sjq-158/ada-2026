// TODO entire implementation and add more header file/s as needed
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "list.hpp"
#include "node.hpp"

using namespace std;

class LinkedList : public List{
  node* head;
  node* tail;
  int totalSize;
  
public:
    LinkedList(){
        head = nullptr;
        tail = nullptr;
        totalSize = 0;
    }
    
    void insert(int num){
        // addLast
        addLast(num);
    }
    
    int get(int pos){
        // Fix: Changed pos < 0 to pos < 1 to match 1-based indexing
        if(pos > totalSize || pos < 1){
            throw logic_error("Invalid position");
        }
        
        node* curr;
        // Efficiency Fix: Determine if we should start from head or tail
        if (pos <= totalSize / 2) {
            curr = head;
            for (int i = 1; i < pos; i++) curr = curr->next;
        } else {
            // Efficiency Fix: Traverse backwards from tail if closer
            curr = tail;
            for (int i = totalSize; i > pos; i--) curr = curr->prev;
        }
        
        return curr->elem;
    }
    
    int remove(int num){
        node* curr = head;
        int pos = 0;
        while(curr){
            pos++;
            if(curr->elem == num){
                if(curr == head){
                    removeFirst();
                }else if(curr == tail){
                    removeLast();
                }else{
                    // Fix: Correctly link the neighbors together
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    
                    // Fix: Deallocate node to prevent memory leak
                    delete curr;
                    totalSize--;
                }
                return pos;
            }else{
                curr = curr->next;
            }
        }
        
        return 0;
    }
    
    void addAt(int num, int pos){
        if(pos > totalSize + 1 || pos < 1){
            throw logic_error("Invalid position");
        }
        
        // Logic: Use existing helper methods for boundaries
        if(pos == 1){
            addFirst(num);
        }else if(pos == totalSize + 1){
            addLast(num);
        }else{
            node* n = new node;
            n->elem = num;
            
            node* curr;
            // Efficiency Fix: Optimal traversal path
            if (pos <= totalSize / 2) {
                curr = head;
                for (int i = 1; i < pos; i++) curr = curr->next;
            } else {
                curr = tail;
                for (int i = totalSize; i > pos; i--) curr = curr->prev;
            }
            
            // Logic: Insert new node 'n' before 'curr'
            n->next = curr;
            n->prev = curr->prev;
            curr->prev->next = n;
            curr->prev = n;
            totalSize++;
        }
    }
    
    int size(){
        return totalSize;
    }
    
    bool isEmpty(){
        return totalSize == 0;
    }

    int removeAt(int pos){
        // Fix: Correct boundary check (pos > totalSize instead of totalSize + 1)
        if(pos > totalSize || pos < 1){
            throw logic_error("Invalid position");
        }
        
        if(pos == 1){
            return removeFirst();
        }else if(pos == totalSize){
            return removeLast();
        }else{
            node* curr;
            // Efficiency Fix: Optimal traversal path
            if (pos <= totalSize / 2) {
                curr = head;
                for (int i = 1; i < pos; i++) curr = curr->next;
            } else {
                curr = tail;
                for (int i = totalSize; i > pos; i--) curr = curr->prev;
            }
            
            int res = curr->elem;
            // Fix: Point neighbors to each other (fixed from previous logic error)
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            
            // Fix: Deallocate to prevent memory leak
            delete curr;
            totalSize--;
            
            return res;
        }
    }
    
    
    void addFirst(int num){
        // Logic: Standard DLL prepend
        node* n = new node;
        n->elem = num;
        
        n->next = head;
        n->prev = nullptr;
        
        if(head){
            head->prev = n;
        }else{
            tail = n;
        }
        
        head = n;
        totalSize++;
    }
    
    void addLast(int num){
        // Logic: Standard DLL append
        node* n = new node;
        n->elem = num;
        
        n->next = nullptr;
        n->prev = tail;
        
        if(tail){
            tail->next = n;
        }else{
            head = n;
        }
        
        tail = n;
        totalSize++;
    }
    
    int removeFirst(){
        node* temp = head;
        int res = head->elem;
        head = head->next;
        
        if(head){
            head->prev = nullptr;
        }else{
            tail = nullptr;
        }
        
        delete temp;
        totalSize--;
        return res;
    }
    
    int removeLast(){
        node* temp = tail;
        int res = tail->elem;
        tail = tail->prev;
        
        if(tail){
            tail->next = nullptr;
        }else{
            head = nullptr;
        }
        
        delete temp;
        totalSize--;
        return res;
    }
    
    void print(){
        if(totalSize == 0){
            // Format Fix: Strictly match output "(none)"
            cout << "FROM HEAD: (none)" << endl; 
            cout << "FROM TAIL: (none)" << endl;
        }else{
            node*curr = head;
            cout << "FROM HEAD: " ;
            while(curr){
                cout << curr->elem;
                // Logic: Only print arrows between elements, not at the end
                if(curr->next){
                    cout << " -> ";
                }
                curr = curr->next;
            }
            cout << endl; 
            
            curr = tail;
            cout << "FROM TAIL: ";
            while(curr){
                cout << curr->elem;
                // Logic: Backward arrow formatting
                if(curr->prev){
                    cout << " <- ";
                }
                curr = curr->prev;
            }
            cout << endl;
        }
    }
};