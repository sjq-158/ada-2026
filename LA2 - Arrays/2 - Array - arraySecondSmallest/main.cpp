#include <iostream>
using namespace std;

int arraySecondSmallest(int* array, int n){
    
    int first = array[0], second;
    
    for(int i = 1; i < n; i++){
        if(array[i] < first){
            second = first;
            first = array[i];
        }else if(array[i] < second){
            second = array[i];
        }
    }
    
    return second;
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
    
    cout << "The second smallest element is " << arraySecondSmallest(array, n) << endl;
    
    return 0;
}