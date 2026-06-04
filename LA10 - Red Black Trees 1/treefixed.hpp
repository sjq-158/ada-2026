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
        node* n = new node;
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
        
        if(curr->right){
            return search_node(num, curr->right);
        }
        return curr; 
    }
    
    
    void zigright(node* x){
        if (!x || !x->parent) return;

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
        
        if(x) x->parent = z;
        if(x) x->right = y;
        y->parent = x;
        y->left = t2;
        
        // Update child's parent pointer
        if(t2){
            t2->parent = y;
        }
        
    }
    
    void zigleft(node* x){
        if (!x || !x->parent) return;

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
        
        if(x) x->parent = z;
        if(x) x->left = y;
        y->parent = x;
        y->right = t2;
        
        // Update child's parent pointer
        if(t2){
            t2->parent = y;
        }
    }
    
    node* restructure(node* child){
        node* parent = child->parent;
        node* grandparent = parent->parent;

        bool ptoc = (parent->right == child);
        bool gtop = (grandparent->right == parent);

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
        return nullptr;
    }
    
    bool insert(int num) {
        if(root == nullptr){
            root = create_node(num, nullptr);
            root->is_red = false; // black 
            size++;
            return true;
        }else{
            // search parent 
            node* parent = search_node(num, root);
            
            if(parent->element != num){
                node* n = create_node(num, parent);
                
                if(parent->element < num){
                    parent->right = n;
                }else{
                    parent->left = n;
                }
                
                size++; 
                
                // Rebalance loop: Check for Double Red Violation
                // A violation exists if node n is red and its parent is also red
                while(n != root && n->parent->is_red){
                    node* curr_parent = n->parent;
                    node* grandparent = curr_parent->parent;
                    node* uncle = (grandparent->left == curr_parent) ? grandparent->right : grandparent->left;
                    
                    // uncle is black
                    if(uncle == nullptr || uncle->is_red == false){
                        cout << "INSERTION Violation: Case 1" << endl;
                        node* a = restructure(n);
                        
                        a->is_red = false;
                        // Children of the restructured root become red
                        if (a->left) a->left->is_red = true;
                        if (a->right) a->right->is_red = true;
                        
                        // After Case 1, local property is restored
                        break;
                    }
                    // uncle is red 
                    else {
                        cout << "INSERTION Violation: Case 2" << endl;
                        uncle->is_red = false;
                        if (curr_parent) curr_parent->is_red = false;
                        
                        if(grandparent != root){
                            grandparent->is_red = true;
                            // Propagate red color up
                            n = grandparent;
                        }else{
                            // Grandparent is root, stays black
                            n = root;
                            break; 
                        }
                    }
                }
                
                root->is_red = false;
                return true;
            }
            
        }
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