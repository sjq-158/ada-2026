#include <cmath>
#include <algorithm>

using namespace std;

struct node {
    node* parent;
    node* right;
    node* left;
    int elem;

    // TODO paste your height method here
    int height() {
        if(left == nullptr && right == nullptr){
            return 1; 
        }else if(right == nullptr){
            return left->height() + 1;
        }else if(left == nullptr){
            return right->height() + 1;
        }else{
            return max(left->height(), right->height()) + 1;
        }
    }
    
    
    
};