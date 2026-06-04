#include <iostream>

using namespace std;

int arraySum(int* array, int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += array[i];
    }
    
    return sum;
}

int main(){
    int n;
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    int array[n];
    
    for(int i = 0; i < n; i++){
        cout << "Enter element " << i + 1 << ": ";
        cin >> array[i];
    }
    
    cout << "Sum is " << arraySum(array, n);
    
    return 0;
}