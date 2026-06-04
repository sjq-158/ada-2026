#include <algorithm>
#include <cmath>

using namespace std;

struct node {
    node* parent;
    node* right;
    node* left;
    int elem;
    
    // height() method, answer
    int height(){
        if(left == nullptr && right == nullptr){
            return 0; 
        }else if(right == nullptr){
            return left->height() + 1;
        }else if(left == nullptr){
            return right->height() + 1;
        }else{
            return max(left->height(), right->height()) + 1;
        }
    }
    
    
};  