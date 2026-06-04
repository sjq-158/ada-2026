    #include "mybinarytree.hpp"

    class BST {
        BinaryTree* tree = new MyBinaryTree();
        
        void checkavl(node* curr){
            int left = 0, right = 0;

            // ERROR FIX: Replaced 'else if' with a separate 'if' to check both children.
            // Logic: Calculate height for both subtrees independently to find the balance factor.
            if(curr->left){
                left = curr->left->height();
            }
            if(curr->right){
                right = curr->right->height();
            }
            
            if(abs(left - right) > 1){
                restructure(curr);
            }
            
        }
        
        public:
        bool search(int num) {
            return search_node(tree->getRoot(), num);
        }

        bool search_node(node* n, int num) {
            if (n == NULL) {
                return false;
            }
            if (n->elem == num) {
                return true;
            }
            if (num > n->elem) {
                // proceed to right
                return search_node(n->right, num);
            } else {
                return search_node(n->left, num);
            }
        }

        // TODO perform post-processing by checking for violation after insertion
        // from the node inserted (or from its parent) until the root
        node* insert(int num) {
            node* n = tree->getRoot();
            if (n == NULL) {
                return tree->addRoot(num);
            }
            
            n = insert_node(n, num);
            node* curr  = n->parent;
            while(curr){
                checkavl(curr);
                curr = curr->parent;
            }
            
            return n; // DO NOT EDIT
        }

        node* insert_node(node* n, int num) {
            if (n == NULL) {
                return NULL;
            }
            if (n->elem == num) {
                return NULL;
            }
            if (num > n->elem) {
                if (!n->right) {
                    return tree->addRight(n, num);
                    
                } else {
                    return insert_node(n->right, num);
                }
            } else {
                if (!n->left) {
                    return tree->addLeft(n, num);
                } else {
                    return insert_node(n->left, num);
                }
            }
        }


        // TODO perform post-processing by checking for violation after deletion
        // from the parent of the node removed until the root
        bool remove(int num) {
            return remove_node(tree->getRoot(), num);
        }

        bool remove_node(node* n, int num) {
            if (n == NULL) {
                return false;
            }
            
            node* parent = nullptr;
            if (n->elem == num) {
                if (n->left && n->right) {
                    
                    node* r = n->right;
                    while (r->left) {
                        r = r->left;
                    }
                    
                    node* curr = r->parent;
                    int rem = tree->remove(r);
                    n->elem = rem;
                    while(curr){
                        checkavl(curr);
                        curr = curr->parent;
                    }
                    
                } else {
                    // Logic: For nodes with 0 or 1 child, we store the parent before removal.
                    parent = n->parent;
                    tree->remove(n);
                    
                    // ERROR FIX: Added the rebalancing loop for the single/no child case.
                    node* curr = parent;
                    while(curr){
                        checkavl(curr);
                        curr = curr->parent;
                    }
                }
                
                return true;
            }
            if (num > n->elem) {
                return remove_node(n->right, num);
            } else {
                return remove_node(n->left, num);
            }
        }

        // TODO copy and paste your completed restructure method here
        bool restructure(node* gp) {
            node* par; // parent
            // TODO find parent
            
            int lefth = gp->left == nullptr ? 0 : gp->left->height();
            int righth = gp->right == nullptr ? 0 : gp->right->height();
            
            // cout << lefth << " a nd " << righth << endl;
            if(lefth > righth){
                par = gp->left;
            }else{
                par = gp->right;
            }
            
            // This is an indicator of the placement of grandparent to parent (gtop)
            bool gtop_right = false;
            if (gp->right == par) {
                gtop_right = true;
            }

            node* child;
            // TODO find child
            
            lefth = par->left == nullptr ? 0 : par->left->height();
            righth = par->right == nullptr ? 0 : par->right->height();
            // cout << lefth << " a nd " << righth << endl;
            if(lefth == righth){
                if(gtop_right){
                    child = par->right;
                }else{
                    child = par->left;
                }
            }else if(lefth > righth){
                child = par->left;
            }else{
                child = par->right;
            }
            
            
            // This is an indicator of the placement of parent to child (ptoc)
            bool ptoc_right = false;
            if (par->right == child) {
                ptoc_right = true;
            }

            // FOR THE FOLLOWING: Write in each of the if statements a console output
            // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

            // z
            //  \
            //   y
            //    \
            //     x
            if (gtop_right && ptoc_right) {
                // TODO call to either zigleft or zigright or both
                cout << "ZIGLEFT" << endl;
                zigleft(par);
            }

            // z
            //   \
            //     y
            //    /
            //   x
            else if (gtop_right && !ptoc_right) {
                // TODO call to either zigleft or zigright or both
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
                cout << "ZIGRIGHT" << endl;
                zigright(par);
            }

            //      z
            //    /
            //  y
            //   \
            //    x
            else {
                // TODO call to either zigleft or zigright or both
                cout << "ZIGZAGRIGHT" << endl;
                zigleft(child);
                zigright(child);
            }

            return true;
        }
        
        
        
        void zigleft(node* curr) {
            tree->zigleft(curr);
        }

        void zigright(node* curr) {
            tree->zigright(curr);
        }

        void print() {
            tree->print();
        }

        // sample to solve
        // bool restructure(node* gp) {
        //     node* par; // parent
        //     // TODO find parent

        //     // This is an indicator of the placement of grandparent to parent (gtop)
        //     bool gtop_right = false;
        //     if (gp->right == par) {
        //         gtop_right = true;
        //     }

        //     node* child;
        //     // TODO find child

        //     // This is an indicator of the placement of parent to child (ptoc)
        //     bool ptoc_right = false;
        //     if (par->right == child) {
        //         ptoc_right = true;
        //     }

        //     // FOR THE FOLLOWING: Write in each of the if statements a console output
        //     // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        //     // z
        //     //  \
        //     //   y
        //     //    \
        //     //     x
        //     if (gtop_right && ptoc_right) {
        //         // TODO call to either zigleft or zigright or both
        //     }

        //     // z
        //     //   \
        //     //     y
        //     //    /
        //     //   x
        //     else if (gtop_right && !ptoc_right) {
        //         // TODO call to either zigleft or zigright or both
        //     }

        //     //     z
        //     //    /
        //     //   y
        //     //  /
        //     // x
        //     else if (!gtop_right && !ptoc_right) {
        //         // TODO call to either zigleft or zigright or both
        //     }

        //     //      z
        //     //    /
        //     //  y
        //     //   \
        //     //    x
        //     else {
        //         // TODO call to either zigleft or zigright or both
        //     }

        //     return true;
        // }


        // me version
        // GIVEN the grandparent (or z), find the parent (or y), and the child (or x).
        // bool restructure(node* gp) {
            
        //     // if(gp->left == nullptr && gp->right == nullptr){
        //     //     return false;
        //     // }
            
        //     node* par; // parent
        //     // TODO find parent
        //     int gplh = gp->left ? gp->left->height() : 0;
        //     int gprh = gp->right ? gp->right->height() : 0;
            
        //     int balancegp = gplh - gprh;
            
        //     // wouldnt print the rotation - to change
        //     // if(abs(balancegp) == 1 || abs(balancegp) == 0){
        //     //     return false; // balanced
        //     // }
            
        //     par = ((gplh - gprh) < 0) ? gp->right : gp->left;
            
        //     if(par->left == nullptr && par->right == nullptr){
        //         return false;
        //     }
            
        //     // This is an indicator of the placement of grandparent to parent (gtop)
        //     bool gtop_right = false;
        //     if (gp->right == par) {
        //         gtop_right = true;
        //     }

        //     node* child;
        //     // TODO find child
        //     int plh = par->left ? par->left->height() : 0;
        //     int prh = par->right ? par->right->height() : 0;
            
        //     int balancep = plh - prh;
            
        //     // goods - case 3
        //     // child = (balancep != 0) ? (gtop_right ? par->right : par->left) : (((balancep) < 0) ? par->right : par->left);
        //     // child = (balancep != 0) ? (gtop_right ? par->right : par->left) : (((balancep) < 0) ? par->left : par->right);
            
        //     // goods - case 1
        //     child = (balancep == 0) ? (gtop_right ? par->right : par->left) : ((balancep < 0) ? par->right : par->left);
        //     // child = (balancep == 0) ? (gtop_right ? par->right : par->left) : ((balancep < 0) ? par->left : par->right);
            
        //     // if(balancep == 0){
                
        //     //     if(gtop_right){
        //     //         child = par->right;
        //     //     }else{
        //     //         child = par->left;
        //     //     }
                
        //     // }else{
        //     //     if(balancep < 0){
        //     //         child = par->right;
        //     //     }else{
        //     //         child = par->left;
        //     //     }
        //     // }
            
        //     // This is an indicator of the placement of parent to child (ptoc)
        //     bool ptoc_right = false;
        //     if (par->right == child) {
        //         ptoc_right = true;
        //     }

        //     // FOR THE FOLLOWING: Write in each of the if statements a console output
        //     // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)
            
        //     // ===================================================================
            
        //     // z
        //     //  \
        //     //   y
        //     //    \
        //     //     x
        //     if (gtop_right && ptoc_right) {
        //         // TODO call to either zigleft or zigright or both
        //         cout << "ZIGLEFT" << endl;
        //         // tree->zigleft(par);
        //         zigleft(par);
        //     }
            
        //     // ===================================================================
            
        //     // z
        //     //   \
        //     //     y
        //     //    /
        //     //   x
        //     else if (gtop_right && !ptoc_right) {
        //         // TODO call to either zigleft or zigright or both
        //         cout << "ZIGZAGLEFT" << endl;
        //         // tree->zigright(child);
        //         // tree->zigleft(child);
                
        //         // tree->zigright(par);
        //         // tree->zigleft(par);
                
        //         zigright(child);
        //         zigleft(child);
        //     }
            
        //     // ===================================================================
            
                
        //     //     z
        //     //    /
        //     //   y
        //     //  /
        //     // x
        //     else if (!gtop_right && !ptoc_right) {
        //         // TODO call to either zigleft or zigright or both
        //         cout << "ZIGRIGHT" << endl;
        //         // tree->zigright(par);
        //         zigright(par);
        //     }
            
        //     // ===================================================================
            
        //     //      z
        //     //    /
        //     //  y
        //     //   \
        //     //    x
        //     else {
        //         // TODO call to either zigleft or zigright or both
        //         cout << "ZIGZAGRIGHT" << endl;
        //         // tree->zigleft(child);
        //         // tree->zigright(child);
                
        //         // tree->zigleft(par);
        //         // tree->zigright(par);
                
        //         zigleft(child);
        //         zigright(child);
        //     }

        //     return true;
        // }

    };
