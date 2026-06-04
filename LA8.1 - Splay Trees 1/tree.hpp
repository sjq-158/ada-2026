#include "node.hpp"
#include <iostream>
using namespace std;
class BSTree {
    node* root;
    int size;

    node* create_node(int num, node* parent) {
        node* n = (node*) malloc( sizeof(node) );
        n->element = num;
        n->parent = parent;
        n->right = NULL;
        n->left = NULL;
        return n;
    }

    bool search(node* curr, int num) {
        if (curr == NULL) {
            return false;
        }
        if (num == curr->element) {
            return true;
        }

        if (num < curr->element) {
            return search(curr->left, num);
        }
        return search(curr->right, num);
    }

    node* search_node(node* curr, int num) {
        if (num == curr->element) {
            return curr;
        }

        if (num < curr->element) {
            if (curr->left != NULL) {
                return search_node(curr->left, num);
            }
            return curr;
        }
        if (curr->right != NULL) {
            return search_node(curr->right, num);
        }
        return curr;
    }

    public:
    BSTree() {
        root = NULL;
        size = 0;
    }

    bool search(int num) {
        // return search(root, num); // original
        
        // edited 
        // include search() in splay tree 
        if(root == nullptr){
            return false;
        }
        
        node* result = search_node(root, num);
        
        if(result){
            restructure(result); // continuously splay 
        }
        
        return result->element == num; // found 
    }

    bool insert(int num) {
        if (root == NULL) {
            root = create_node(num, NULL);
            size++;
            return true;
        } else {
            node* parent = search_node(root, num);
            if (parent->element != num) {
                node* newest = create_node(num, parent);
                if (parent->element < num) {
                    parent->right = newest;
                } else {
                    parent->left = newest;
                }
                size++;
                
                // edited
                restructure(newest); // create_node(num, parent)
                
                return true;
            }
        }
        return false;
    }

    bool remove(int num) {
      if (isEmpty()) {
        return false;
      }
      node* rem_node = search_node(root, num);
      if (rem_node->element != num) {
        return false;
      }

      // FIND the number of children.
      int children = 0;
      // 0 - no children
      // -1 - left child only
      // 1 - right child only
      // 2 - both children
      if (rem_node->right) {
        children = 1;
      }
      if (rem_node->left) {
        if (children == 1) {
          children = 2;
        } else {
          children = -1;
        }
      }

      if (children == 0) { // NO CHILDREN
        node* parent = rem_node->parent;
        if (!parent) {
          root = NULL;
        } else {
          if (rem_node == parent->left) {
            parent->left = NULL;
          } else {
            parent->right = NULL;
          }
        }

        free(rem_node);
        size--;
      } else if (children == -1 || children == 1) { // ONE CHILD
        node* parent = rem_node->parent;
        node* child;
        if (children == -1) {
          child = rem_node->left;
        } else {
          child = rem_node->right;
        }

        child->parent = parent;
        if (!parent) {
          root = child;
        } else {
          if (parent->left == rem_node) {
            parent->left = child;
          } else {
            parent->right = child;
          }
        }

        free(rem_node);
        size--;
      } else { // TWO CHILDREN
        node* right_st = rem_node->right;
        while (right_st->left != NULL) {
          right_st = right_st->left;
        }

        int temp = right_st->element;
        remove(temp);
        rem_node->element = temp;
      }
      return true;
    }

    // TODO implementation of rotate operation of x where
    //  |
    //  y
    //   \
    //    x <- curr
    void zigleft(node* curr) {
        
        node* parent = curr->parent;
        node* grandparent = parent->parent; // curr->parent->parent
        node* t2 = curr->left;
        
        if(parent == nullptr){
            return;
        }
        
        if(grandparent){
            if(grandparent->right == parent){
                grandparent->right = curr;
            }else{
                grandparent->left = curr;
            }
            
            curr->parent = grandparent;
        }
        
        curr->left = parent;
        parent->parent = curr;
        parent->right = t2;
        
        if(t2){
            t2->parent = parent;
        }
        
        if(grandparent == nullptr){
            root = curr;
            curr->parent = nullptr;
        }
        
        // if(root == parent){
        //     root = curr;
        // }else if(grandparent->left == parent){
        //     grandparent->left = curr;
        // }else{
        //     grandparent->right = curr;
        // }
        
        
        // curr->parent = grandparent;
        // parent->right = curr->left;
        
        // if(curr->left){
        //     curr->left->parent = parent;
        // }
        
        // curr->left = parent;
        // parent->parent = curr;
        
        
    }

    // TODO implementation of rotate operation of x where
    //   |
    //   y
    //  /
    // x <- curr
    void zigright(node* curr) {
        
        node* parent = curr->parent;
        node* grandparent = parent->parent; // curr->parent->parent
        node* t2 = curr->right;
        
        if(parent == nullptr){
            return;
        }
        
        if(grandparent){
            if(grandparent->right == parent){
                grandparent->right = curr;
            }else{
                grandparent->left = curr;
            }
            
            curr->parent = grandparent;
        }
        
        curr->right = parent;
        parent->parent = curr;
        parent->left = t2;
        
        if(t2){
            t2->parent = parent;
        }
        
        if(grandparent == nullptr){
            root = curr;
            curr->parent = nullptr;
        }
        
        // if(root == parent){
        //     root = curr;
        // }else if(grandparent->left == parent){
        //     grandparent->left = curr;
        // }else{
        //     grandparent->right = curr;
        // }
        
        // curr->parent = grandparent;
        // parent->left = curr->right;
        
        // if(curr->right){
        //     curr->right->parent = parent;
        // }
        
        // curr->right = parent;
        // parent->parent = curr;
    }

    // GIVEN the child (or x), find the parent (or y), and the grandparent if any (or z).
    // Splay the child to the root recursively or iteratively.
    void restructure(node* child) {
        
        // add
        if(child == nullptr){
            return;
        }
        
        node* par; // parent
        // TODO find parent
        
        par = child->parent; // no height in node.hpp since it is a splay
        if(par == nullptr){
            return; // error
        }
        
        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        node* gp;
        // TODO find grandparent. If gp does not exist, proceed to doing ZIGLEFT or ZIGRIGHT.
        
        gp = par->parent;
        if(gp == nullptr){
            // if(par->left == child){
            //     // do ZIGRIGHT
            //     cout << "ZIGRIGHT" << endl;
            //     zigright(child);
                
            // }else{
            //     // do ZIGLEFT
            //     cout << "ZIGLEFT" << endl;
            //     zigleft(child);
            // }
            
            if(par->right == child){
                // do ZIGLEFT
                cout << "ZIGLEFT" << endl;
                zigleft(child);
            }else{
                // do ZIGRIGHT
                cout << "ZIGRIGHT" << endl;
                zigright(child);
            }
            
            return;
        }
        
        
        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGZIGLEFT, ZIGZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

      // z
      //  \
      //   y
      //    \
      //     x
      if (gtop_right && ptoc_right) {
        // TODO call to either zigleft or zigright or both
            // ZIGZIGLEFT
            cout << "ZIGZIGLEFT" << endl;
            zigleft(par);
            zigleft(child);
      }

      // z
      //   \
      //     y
      //    /
      //   x
      else if (gtop_right && !ptoc_right) {
        // TODO call to either zigleft or zigright or both
            // ZIGZAGLEFT
            cout << "ZIGZAGLEFT" << endl;
            zigright(child);
            zigleft(child);
        
      }

      //     z
      //    /
      //   y
      //  /
      // x
      else if (!gtop_right && !ptoc_right) {
        // TODO call to either zigleft or zigright or both
            // ZIGZIGRIGHT
            cout << "ZIGZIGRIGHT" << endl;
            zigright(par);
            zigright(child);
      }

      //      z
      //    /
      //  y
      //   \
      //    x
      else {
        // TODO call to either zigleft or zigright or both
            // ZIGZAGRIGHT
            cout << "ZIGZAGRIGHT" << endl;
            zigleft(child);
            zigright(child);
      }
      
      // check ?
      if(child->parent){
          restructure(child);
      }
      
      
      return;
    }

    // WARNING. Do not modify the methods below.
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
        cout << curr->element << " ";
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
        cout << curr->element << " ";
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
        cout << curr->element << " ";
    }

    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                // cout << "Illegal parent of " << curr->element << ": NULL -- must be " << par->elem << endl; // would cause error 
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