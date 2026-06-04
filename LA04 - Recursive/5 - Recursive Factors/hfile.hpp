// TODO factor(int) here
#include <iostream>

using namespace std;

int factor(int n){
    static int i = 1;
    int count = 0;
    
    if(i > n){
        i = 1;
        return 0;
    }
    
    if(n % i == 0){
        cout << i << " ";
        count++;
    }
    
    i++;
    return count + factor(n);
}