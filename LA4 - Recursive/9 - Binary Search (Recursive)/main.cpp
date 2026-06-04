#include <iostream>
#include "hfile.hpp"
using namespace std;

int binarySearch(int arr[], int size, int x) {
    return helper(arr, 0, size-1, x);
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* arr = new int[size];
    cout << "Enter sorted unique numbers: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    int x;
    cout << "Enter the number to search for: ";
    cin >> x;

    int result = binarySearch(arr, size, x);
    if (result != -1) {
        cout << "Number found at index: " << result << std::endl;
    } else {
        cout << "Number not found!" << std::endl;
    }

    return 0;
}