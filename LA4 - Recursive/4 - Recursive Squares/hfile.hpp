// TODO
#include <iostream>
#include <cmath>

using namespace std;

void recsquares(int n){
    
    if(n == 0){
        return;
    }
    
    recsquares(n - 1);
    cout << (n * n) << endl;
    
}