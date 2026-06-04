// TODO helper
#include <iostream>

using namespace std;

int helper(int* array, int start, int end, int target){
    
    if(start > end){
        return -1;
    }
    
    int mid = start + (end - start) / 2;
    
    if(array[mid] == target){
        return mid;
    }else if(array[mid] > target){
        return helper(array, start, mid - 1, target);
    }else{
        return helper(array, mid + 1, end, target);
    }
    
}