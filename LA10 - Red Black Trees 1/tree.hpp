#include "node.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;
class BSTree {
    node* root;
    int size;

    public:
    BSTree() {
        root = NULL;
        size = 0;
    }
    
    // okay
    node* create_node(int num, node* parent){
        
        node* n = (node*) malloc(sizeof(node));
        n->element = num;
        
        n->left = nullptr;
        n->right = nullptr;
        n->parent = parent;
        n->is_red = true;
        
        return n;
    }
    
    node* search_node(int num, node* curr){
        
        if(curr->element == num){
            return curr;
        }
        
        if(num < curr->element){
            // return curr->left ? search_node(num, curr->left) : curr;
            if(curr->left){
                return search_node(num, curr->left);
            }
            return curr;
        }
        
        // return curr->right ? search_node(num, curr->right) : curr;
       if(curr->right){
            return search_node(num, curr->right);
        }
        return curr; 
    }
    
    
    void zigright(node* x){
        
        
        // node* parent = curr->parent;
        // node* grandparent = parent->parent;
        // node* t2 = curr->right;
        
        // // if(parent == nullptr){
        // //     return; // error 
        // // }
        
        // if(grandparent){
        //     if(grandparent->left == parent){
        //         grandparent->left = curr;
        //     }else{
        //         grandparent->right = curr;
        //     }
            
        //     curr->right = grandparent;
            
        // }
        
        
        // // clp, prt, ... if(t2) t2p = c  
        // curr->right = parent; 
        // parent->parent = curr; // check this 
        // parent->left = t2;
        
        // if(t2){
        //     t2->parent = curr;
        // }
        
        // // check if grandparent is nullptr
        // if(grandparent == nullptr){
        //     root = curr;
        //     curr->parent = nullptr; 
        // }
        
        node* t2 = x->right;
        node* y = x->parent;
        node* z = y->parent;
        
        if(z){
            if(z->left == y){
                z->left = x;
            }else{
                z->right = x;
            }
        }else{
            root = x;
        }
        
        x->parent = z;
        x->right = y;
        y->parent = x;
        y->left = t2;
        
        if(t2){
            t2->parent = y;
        }
        
    }
    
    void zigleft(node* x){
        
        // node* parent = curr->parent;
        // node* grandparent = parent->parent;
        // node* t2 = curr->left;
        
        // // if(parent == nullptr){
        // //     return; // error 
        // // }
        
        // if(grandparent){
        //     if(grandparent->right == parent){
        //         grandparent->right = curr;
        //     }else{
        //         grandparent->left = curr;
        //     }
            
        //     curr->left = grandparent;
            
        // }
        
        
        // // clp, prt, ... if(t2) t2p = c  
        // curr->left = parent;
        // parent->parent = curr; // check this 
        // parent->right = t2;
        
        // if(t2){
        //     t2->parent = curr;
        // }
        
        // // check if grandparent is nullptr
        // if(grandparent == nullptr){
        //     root = curr;
        //     curr->parent = nullptr; 
        // }
        
        
        // node* parent = curr->parent;
        // node* grandparent = parent->parent;
        // node* t2 = curr->right;
        
        // // if(parent == nullptr){
        // //     return; // error 
        // // }
        
        // if(grandparent){
        //     if(grandparent->left == parent){
        //         grandparent->left = curr;
        //     }else{
        //         grandparent->right = curr;
        //     }
            
        //     curr->right = grandparent;
            
        // }
        
        
        // // clp, prt, ... if(t2) t2p = c  
        // curr->right = parent; 
        // parent->parent = curr; // check this 
        // parent->left = t2;
        
        // if(t2){
        //     t2->parent = curr;
        // }
        
        // // check if grandparent is nullptr
        // if(grandparent == nullptr){
        //     root = curr;
        //     curr->parent = nullptr; 
        // }
        
        node* t2 = x->left;
        node* y = x->parent;
        node* z = y->parent;
        
        if(z){
            if(z->left == y){
                z->left = x;
            }else{
                z->right = x;
            }
        }else{
            root = x;
        }
        
        x->parent = z;
        x->left = y;
        y->parent = x;
        y->right = t2;
        
        if(t2){
            t2->parent = y;
        }
    }
    
    node* restructure(node* child){
        
        // parent 
        node* parent = child->parent;
        // if(parent == nullptr){
        //     return nullptr; // nothing
        // }
        bool ptoc = false;
        if(parent->right == child){
            ptoc = true;
        }
        
        // grandparent
        node* grandparent = parent->parent;
        bool gtop = false;
        if(grandparent->right == parent){
            gtop = true;
        }
        
        
        // restructure
        // if(grandparent && gtop && ptoc){
        //     // zigleft
        //     cout << "ZIGLEFT" << endl;
        //     zigleft(parent);
        //     return parent;
        // }else if(grandparent && gtop){
        //     // zigzagleft
        //     cout << "ZIGZAGLEFT" << endl;
        //     zigright(child);
        //     zigleft(child);
        //     return child;
        // }else if(grandparent && !ptoc){
        //     // zigright
        //     cout << "ZIGRIGHT" << endl;
        //     zigright(parent);
        //     return parent;
        // }else if(grandparent){
        //     cout << "ZIGZAGRIGHT" << endl;
        //     zigleft(child);
        //     zigright(child);
        //     return child;
        // }else if(ptoc){
        //     // zigleft
        //     cout << "ZIGLEFT" << endl;
        //     zigleft(child);
        //     return child;
        // }else{
        //     // zigright
        //     cout << "ZIGRIGHT" << endl;
        //     zigright(child);
        //     return child;
        // }
        
        if(gtop && ptoc){
            // zigleft
            cout << "ZIGLEFT" << endl;
            zigleft(parent);
            return parent;
        }else if(!ptoc && gtop){
            // zigzagleft
            cout << "ZIGZAGLEFT" << endl;
            zigright(child);
            zigleft(child);
            return child;
        }else if(!gtop && !ptoc){
            // zigright
            cout << "ZIGRIGHT" << endl;
            zigright(parent);
            return parent;
        }else if(!gtop && ptoc){
            cout << "ZIGZAGRIGHT" << endl;
            zigleft(child);
            zigright(child);
            return child;
        }
        
    }
    
    bool insert(int num) {
        
        // try 
        if(root == nullptr){
            root = create_node(num, nullptr);
            root->is_red = false; // black 
            size++;
            return true;
        }else{
            
            // search parent 
            node* parent = search_node(num, root);
            
            // // added new version
            // if(parent == nullptr){
            //     return false;
            // }
            
            // should be no duplicate 
            
            if(parent->element != num){
                
                node* n = create_node(num, parent);
                
                // check this again. may interchange 
                if(parent->element < num){
                    parent->right = n;
                }else{
                    parent->left = n;
                }
                
                size++; // increased size
                node* nparent = n->parent;
                
                
                while(nparent->is_red && parent->is_red && n->is_red){
                        
                        
                    // search for uncle
                    
                    
                    // if(grandparent->left == parent){
                    //     uncle = grandparent->right;
                    // }else{
                    //     uncle = grandparent->left; 
                    // }
                    
                    // looping 
                    
                    node* grandparent = nparent->parent;
                    node* uncle = (grandparent->left == parent) ? grandparent->right : grandparent->left;
                    
                    // uncle is black
                    if(uncle == nullptr || uncle->is_red == false){
                        
                        // restructure ?
                        cout << "INSERTION Violation: Case 1" << endl;
                        node* a = restructure(n);
                        
                        a->is_red = false;
                        a->left->is_red = true;
                        a->right->is_red = true;
                        break;
                    }
                    
                    // uncle is red 
                    else if(uncle->is_red == true){
                        
                        // would check if the changing of color the grandparent is black
                        cout << "INSERTION Violation: Case 2" << endl;
                        uncle->is_red = false;
                        nparent->is_red = false;
                        
                        if(grandparent != root){
                            grandparent->is_red = true;
                            n = grandparent;
                            nparent = n->parent;
                        }else{
                            break;
                        }
                    }
                }
                
                root->is_red = false;
                return true;
            }
            
            // root->is_red = false;
            // return true;
        }
        
        // print(); 
            return false;
    }
    
    
    
    
    // WARNING. Do not modify these methods below.
    // Doing so will nullify your score for this activity.
    void print() {
        if (isEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        cout << "PRE-ORDER: ";
        print_preorder(root);
        cout << endl << "IN-ORDER: ";
        print_inorder(root);
        cout << endl << "POST-ORDER: ";
        print_postorder(root);
        cout << endl << "STATUS: " << check_parent(root, NULL) << endl;
    }

    bool isEmpty() {
        return size == 0;
    }

    void print_preorder(node* curr) {
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
        if (curr->left != NULL) {
            print_preorder(curr->left);
        }
        if (curr->right != NULL) {
            print_preorder(curr->right);
        }
    }

    void print_inorder(node* curr) {
        if (curr->left != NULL) {
            print_inorder(curr->left);
        }
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
        if (curr->right != NULL) {
            print_inorder(curr->right);
        }
    }

    void print_postorder(node* curr) {
        if (curr->left != NULL) {
            print_postorder(curr->left);
        }
        if (curr->right != NULL) {
            print_postorder(curr->right);
        }
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
    }

    // WARNING. Do not modify this method.
    // Doing so will nullify your score for this activity.
    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                cout << "Illegal parent of " << curr->element << ": NULL -- must be " << par->element << endl;
            } else if (!par) {
                cout << "Illegal parent of " << curr->element << ": " << curr->parent->element << "must be NULL" << endl;
            } else {
                cout << "Illegal parent of " << curr->element << ": " << curr->parent->element << " -- must be " << par->element << endl;
            }
            return false;
        }
        return check_parent(curr->left, curr) && check_parent(curr->right, curr);
    }
};