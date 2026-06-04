#include <iostream>
using namespace std;

// Helper function required by the validation logic in main()
// added but not required
int find(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) return 1;
    }
    return 0;
}

// required.
int *findTwoNumbers(int arr[], int size, int target) {
    // TODO
    // return nullptr;
    
    int* result = new int[2];
    int left = 0, right = size - 1;
    
    while(left < right){
        int sum = arr[left] + arr[right];
        
        if(sum == target){
            
            result[0] = arr[left];
            result[1] = arr[right];
            
            return result;
        }else if(sum < target){
            left++;
        }else{
            right--;
        }
    }
    
    return nullptr;
}


// DO NOT MODIFY below
#include "hidden.hpp"

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* arr = new int[size];
    cout << "Enter the sorted list of numbers: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    int target;
    cout << "Enter the target value: ";
    cin >> target;

    int* result = findTwoNumbers(arr, size, target);
    if (result != nullptr) {
        if (find(arr, size, result[0]) + find(arr,size,result[1]) == 2 && result[0] + result[1] == target) {
            cout << "Two numbers found." << endl;
        } else {
            cout << "Either the numbers do not exist or " << result[0] << " and " << result[1] << " do not add to " << target << endl;
        }
        delete[] result;

    } else {
        cout << "No two numbers found that sum to the target." << endl;
    }

    delete[] arr;
    return 0;
}