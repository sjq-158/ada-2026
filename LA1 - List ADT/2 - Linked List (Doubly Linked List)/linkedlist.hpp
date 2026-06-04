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
        
        if(pos > totalSize || pos < 0){
            throw logic_error("Invalid position");
        }
        
        node* curr = head;
        pos--;
        while(pos--){
            curr = curr->next;
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
                    node* nextNode = curr->next;
                    
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    
                    delete curr;
                    curr = nextNode;
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
        
        if(pos == 0){
            addFirst(num);
            return;
        }else if(pos == totalSize + 1){
            addLast(num);
            return;
        }else{
            node* n = new node;
            n->elem = num;
            
            node* curr = head;
            int i = 1;
            while(i < pos){
                curr = curr->next;
                i++;
            }
            
            n->next = curr;
            n->prev = curr->prev;
            curr->prev->next = n;
            curr->prev = n;
            
            // n->prev = curr;
            // n->next = curr->prev;
            // curr->next->prev = n;
            // curr->next = n;
            
            
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
        if(pos > totalSize + 1 || pos < 1){
            throw logic_error("Invalid position");
        }
        
        node* curr = head;
        if(pos == 1){
            return removeFirst();
        }else if(pos == totalSize){
            return removeLast();
        }else{
            
            while(pos--){
                curr = curr->next;
            }
            
            int res = curr->elem;
            curr->prev->next = curr->prev;
            curr->next->prev = curr->next;
            
            delete curr;
            totalSize--;
            
            return res;
        }
        
        return 0;
    }
    
    
    void addFirst(int num){
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
            node*curr = head;
        cout << "FROM HEAD: (none)" ;
        
        cout << endl; 
        cout << "FROM TAIL: (none)";
        cout << endl;
        }else{
            node*curr = head;
        cout << "FROM HEAD: " ;
        while(curr){
            
            if(curr == tail){
                cout << curr->elem << " ";
            }else{
                cout << curr->elem << " -> ";
            }
            
            curr = curr->next;
        }
        
        cout << endl; 
        
        curr = tail;
        cout << "FROM TAIL: ";
        while(curr){
            
            if(curr == head){
                cout << curr->elem << " ";
            }else{
                cout << curr->elem << " <- ";
            }
            curr = curr->prev;
        }
        
        cout << endl;
        }
    }
    
  
};