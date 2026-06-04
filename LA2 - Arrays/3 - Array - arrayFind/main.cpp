#include <iostream>

using namespace std;

int arrayFind(int* array, int num, int n){
    for(int i = 0; i < n; i++){
        if(array[i] == num){
            return i + 1;
        }
    }
    
    return -1;
}

int main(){
    int n, num;
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    int array[n];
    
    for(int i = 0; i < n; i++){
        cout << "Enter element " << i  + 1 << ": ";
        cin >> array[i];
    }
    
    cout << "Number to find: ";
    cin >> num;
    
    if(arrayFind(array, num, n) == - 1){
        cout << num << " is not there" << endl;
    }else{
        cout << num << " is at position " << arrayFind(array, num, n) << endl;
    }
    
    return 0;
}