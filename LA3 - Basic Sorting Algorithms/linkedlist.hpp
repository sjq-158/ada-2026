#include "list.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

// WARNING! Do not modify this struct!
// Doing so will nullify your score for this activity.
struct node {
    int element;
    node* next;
};

/**
 * This implementation is of a Singly-Linked List.
 * Feel free to add helper methods. You might want the create_node helper method.
 */
class LinkedList : public List {
    node* head;
    node* tail;
    int index;

    node* create_node(int num) {
    //   return NULL;
        node* n = new node;
        n->element = num;
        n->next = nullptr;
        index++;
        
        return n;
    }

    public:
        LinkedList() {
            // changed
            head = nullptr;
            tail = nullptr;
            index = 0;
        }

        int add(int num) {
        //   return 0;
        // changed
            node* n = new node;
            n->element = num;
            n->next = nullptr;
            
            if(tail == nullptr){
                head = n;
            }else{
                tail->next = n;
            }
            
            tail = n;
            index++;
            
            return index;
        }

        int get(int pos) {
        //   return 0;
        // changed
            
            if(pos < 0 || pos >= index){
                return -1;
            }
            
            node* curr = head;
            for(int i = 0; i < pos; i++){
                curr = curr->next;
            }
            
            return curr->element;
        }

        int size() {
            return index;
        }

        void swap(int pos1, int pos2) {
            
            if(pos1 == pos2){
                return;
            }
            
            if(pos1 < 0 || pos2 < 0 || pos1 >= index || pos2 >= index){
                return; // outofbounds
            }
            
            node* prev1 = nullptr;
            node* prev2 = nullptr;
            node* curr1 = head; // first pos
            node* curr2 = head; // second pos
            
            // search nodes
            for(int i = 0; i < pos1; i++){
                prev1 = curr1;
                curr1 = curr1->next;
            }
            
            for(int i = 0; i < pos2; i++){
                prev2 = curr2;
                curr2 = curr2->next;
            }
            
            if(curr1 == nullptr || curr2 == nullptr){
                return;
            }
            
            // swap
            if(prev1){
                prev1->next = curr2;
            }else{
                head = curr2;
            }
            
            if(prev2){
                prev2->next = curr1;
            }else{
                head = curr1;
            }
            
            node* temp = curr1->next;
            curr1->next = curr2->next;
            curr2->next = temp;
            
            if(curr1 == tail){
                tail = curr2;
            }else if(curr2 == tail){
                tail = curr1;
            }
            
        }

        // WARNING! Do not modify this method below!
        // Doing so will nullify your score for this activity.
        void print() {
            node* currnode = head;
            if (head == NULL && tail == NULL) {
                cout << "(empty)";
                return;
            }
            while (true) {
                cout << currnode->element;
                if (currnode == tail) {
                    cout << endl;
                    return;
                }
                cout << " -> ";
                currnode = currnode->next;
            }
        }
};