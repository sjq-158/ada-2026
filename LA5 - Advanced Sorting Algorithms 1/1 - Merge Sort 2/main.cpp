#include <iostream>
#include "linkedlist.h"
#include <bits/stdc++.h>

LinkedList* mergeSort(LinkedList*);

// WARNING! Do not modify this main function!
// Doing so will nullify your score for this activity.
int main(void) {
    LinkedList* list = new LinkedList();

    int length;
    cout << "Input length: ";
    cin >> length;

    int input;
    for (int i = 0; i < length; i++) {
        cout << "Enter element " << i + 1 << ": ";
      cin >> input;
      list->add(input);
    }
    list->print();

    list = mergeSort(list);
    return 0;
};

LinkedList* mergeSort(LinkedList* list) {
    // BASE CASE: When the list only contains one element.
    if (list->size() <= 1) {
        return list;
    }
    
    int half = ceil(list->size() / 2.0);
    
    // Step 1 - DIVIDE
    LinkedList* firsthalf = new LinkedList();
    LinkedList* secondhalf = new LinkedList();
    // TODO: ...
    
    // firsthalf
    firsthalf->head = list->head;
    firsthalf->tail = list->head;
    int mysize = 1;
    
    for(int i = 1; i < half; i++){
        firsthalf->tail = firsthalf->tail->next;
        mysize++;
    }
    
    firsthalf->index = mysize;
    
    // secondhalf
    secondhalf->head = firsthalf->tail->next;
    firsthalf->tail->next = nullptr;
    secondhalf->tail = list->tail;
    secondhalf->index = list->size() - mysize;
    
    // Given: Step 2 - RECURSIVE CALL
    cout << "My first list: ";
    firsthalf->print();
    firsthalf = mergeSort(firsthalf);

    cout << "My second list: ";
    secondhalf->print();
    secondhalf = mergeSort(secondhalf);

    // Step 3 - COMBINE
    LinkedList* sorted = new LinkedList();
    // TODO: ...
    node* newcurr = nullptr;
    node* firstcurr = firsthalf->head;
    node* secondcurr = secondhalf->head;
    
    while(firstcurr || secondcurr){
        if(firstcurr == nullptr){
            newcurr->next = secondcurr;
            secondcurr = secondcurr->next;
        }
        
        else if(secondcurr == nullptr){
            newcurr->next = firstcurr;
            firstcurr = firstcurr->next;
        }else if(firstcurr->element < secondcurr->element){
            if(sorted->head == nullptr){
                sorted->head = firstcurr;
                newcurr = sorted->head;
            }else{
                newcurr->next = firstcurr;
                newcurr = newcurr->next;
            }
            
            firstcurr = firstcurr->next;
        }else{
           if(sorted->head == nullptr){
               sorted->head = secondcurr;
               newcurr = sorted->head;
           }else{
               newcurr->next = secondcurr;
               newcurr = newcurr->next;
           }
           
           secondcurr = secondcurr->next;
        }
        
        
    }
    
    sorted->tail = newcurr;
    sorted->index = list->index;
    
    
    // print and return the sorted list
    cout << "SORTED: ";
    sorted->print();
    return sorted;
}