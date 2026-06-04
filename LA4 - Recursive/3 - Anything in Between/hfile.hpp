// TODO
#include <iostream>

using namespace std;

void between(int start, int end){
    
    if(start > end){
        return;
    }
    
    cout << start << " ";
    between(start + 1, end);
}