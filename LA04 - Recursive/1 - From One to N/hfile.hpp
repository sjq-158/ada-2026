// TODO
#include <iostream>

using namespace std;

void allnums(int n){
    
    if(n == 0){
        return;
    }
    
    allnums(n - 1);
    cout << n << " ";
}