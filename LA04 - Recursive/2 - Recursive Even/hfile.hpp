// TODO
#include <iostream>

using namespace std;

void evennums(int n){
    if(n < 2){
        return;
    }
    
    if(n %  2 == 0){
        cout << n << " ";
    }
    evennums(n - 1);
}