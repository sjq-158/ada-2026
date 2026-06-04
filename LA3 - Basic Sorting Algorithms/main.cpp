#include <iostream>

#include "linkedlist.hpp"
#include "arraylist.hpp"

void bubbleSort(List*);
void selectionSort(List*);
void insertionSort(List*);

/**
 * This activity is focused on using Arrays and Linked Lists as two different
 * implementations of List. It follows that you are only to use the methods of
 * List and not of the specific array or linkedlist.
 */
int main(void) {
    // WARNING! Do not modify this line up until line 56!
    // Doing so will nullify your score for this activity.
    // Also, do not create more instances of ArrayList or LinkedList
    // aside from those in lines 26 and 28.
    char li;
    cout << "Enter type of list: ";
    cin >> li;

    List* list;
    if (li == 'A') {
      list = new ArrayList();
    } else {
      list = new LinkedList();
    }

    int length;
    cout << "Enter number of elements: ";
    cin >> length;

    int input;
    for (int i = 0; i < length; i++) {
      cout << "Enter element " << i+1 << ": ";
      cin >> input;
      list->add(input);
    }

    char sym;
    cout << "Enter sorting method: ";
    cin >> sym;
    list->print();
    switch (sym) {
      case 'B':
        bubbleSort(list);
        break;
      case 'I':
        insertionSort(list);
        break;
      case 'S':
        selectionSort(list);
        break;
    }
    return 0;
};

void bubbleSort(List* list) {
    int size = list->size();
    
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(list->get(j) > list->get(j + 1)){
                list->swap(j, j + 1);
                list->print();
            }
        }
    }
    
    
};

void selectionSort(List* list) {
    int size = list->size();
    int minIndex;
    
    for(int i = 0; i < size - 1; i++){
        
        minIndex = i;
        
        for(int j = i + 1; j < size; j++){
            if(list->get(j) < list->get(minIndex)){
                minIndex = j;
            }
        }
        
        if(minIndex != i){
            list->swap(i, minIndex);
            list->print();
        }
    }
    
};

void insertionSort(List* list) {
    // to do
    
    int size = list->size();
    
    for(int i = 1; i < size; i++){
        
        for(int j = i; j >= 0 && list->get(j) < list->get(j - 1); ){
            list->swap(j, j - 1);
            list->print();
            j--;
        }
        
    }
    
};