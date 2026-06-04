#include <iostream>

using namespace std;

long* res = new long[200];

long fibonacci(int n){
    
    if(n == 0){
        res[n - 1] = 0;
        return 0;
    }
    
    if(n == 1 || n == 2){
        res[n - 1] = 1;
        return 1;
    }
    
    if(res[n - 1] == 0){
        res[n - 1] = fibonacci(n - 1);
    }
    
    if(res[n - 2] == 0){
        res[n - 2] = fibonacci(n - 2);
    }
    
    return res[n - 1] + res[n - 2];
}