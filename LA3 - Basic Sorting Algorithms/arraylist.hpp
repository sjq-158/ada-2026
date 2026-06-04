#include "list.hpp"
#include <cstdlib>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
/**
 * Your ArrayList must have an initial capacity of 4.
 * If the array is full, allocate an additional capacity of 50% its current size.
 * Example, 4 becomes 6, then 6 becomes 9, so on.
 * Maintain a minimum capacity of 4.
 *
 * On the fields:
 * array - holds the pointer to the array itself
 * index - holds the current size, initially zero
 * capacity - holds the current capacity of the array - minimum of 4
 */
class ArrayList : public List {
    int* array;
    int index;
    int capacity;

    public:
        // CONSTRUCTOR
        ArrayList() {
            // changed
            index = 0;
            capacity = 4;
            array = (int*) malloc(capacity * sizeof(int));
        }

        int add(int num) {
        //   return 0;
        // changed
        
            // If the array is full, allocate an additional capacity of 50% its current size.
            if(index >= capacity){
                capacity = ceil(capacity * 1.5);
                array = (int*) realloc(array, capacity * sizeof(int));
            }
            
            // first element
            // if(index == 0){
            //     array[index++] = num;
            // }else{
            //     for(int i = index; i > 0; i--){
            //         array[i] = array[i - 1];
            //     }
                
            //     array[0] = num;
            //     index++;
            // }
            
            array[index++] = num;
            
            return index;
        }

        int get(int pos){
        //   return 0;
        // changed
            if(pos < 0 || pos >= index){
                return -1;
            }
        
            return array[pos];
        }

        int size(){
            return index;
        }

        void swap(int pos1, int pos2){
            // changed
            int temp = array[pos1];
            array[pos1] = array[pos2];
            array[pos2] = temp;
        }

        // WARNING! Do not modify the print method.
        // Doing so will nullify your score for this activity.
        void print() {
            cout << "[";
            for (int i = 0; i < capacity; i++) {
                if (i < index) {
                    cout << *(array + i);
                } else {
                    cout << "?";
                }

                if (i != capacity - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
        }
};