#include "node.hpp"
#include <iostream>
using namespace std;

class BTree24 {
	public:
	node* root;
    
    // sir's
    node* search(int num, node* n){
        if(n == nullptr){
            return nullptr;
        }
        
        for(int i = 0; i < n->size; i++){
            if(num == n->keys[i]){
                return n; // duplicate values
            }
                    
            if(num < n->keys[i]){
                if(n->children[i]){
                    return search(num, n->children[i]);
                }
                        
                return n;
            }
                        
                    
        }
        if(n->children[n->size]){
            return search(num, n->children[n->size]);
        }
        return n;
    }
    
    
	BTree24() {
		root = nullptr;
	}

// 	virtual bool insert(int num) = 0;
// 	virtual node* search(int, node*) = 0;
// 	virtual void print() = 0;
    
    /**
     * Removes an element from the (2,4) Tree.
     * 
     * Step-by-Step Logic:
     * 1. Search for the node containing the key.
     * 2. If the key is in an internal node, swap it with its inorder successor 
     *    (the first key in the leftmost leaf of its right child's subtree).
     * 3. Remove the key from the leaf and shift remaining keys left.
     * 4. Handle Underflow: If the node becomes empty (size 0):
     *    a. Transfer: If a sibling has > 1 key, borrow from parent and move sibling key to parent.
     *       - Priority: Choose 4-node sibling if available, otherwise choose Right.
     *    b. Fusion: If siblings have only 1 key, merge node, parent key, and sibling.
     *       - Priority: Choose Right sibling for fusion.
     *    c. Propagate: If fusion occurs, the parent's size decreases; check for underflow there.
     * 5. Root Adjustment: If root becomes empty, the only child becomes the new root.
     */
    bool remove(int num) {
        // Step 1: Locate the key
		node* w = search(num, root);
		if (w == nullptr || !w->contains(num)) return false;

		int i = 0;
		while (w->keys[i] != num) i++;

        // Step 2: Swap internal node key with inorder successor
		if (w->children[0] != nullptr) {
			node* s = w->children[i + 1];
			while (s->children[0] != nullptr) s = s->children[0];
			w->keys[i] = s->keys[0];
			w = s;
			i = 0;
		}

        // Step 3: Delete key from leaf
		for (int j = i; j < w->size - 1; j++) w->keys[j] = w->keys[j + 1];
		w->size--;

        // Step 4: Resolve Underflow
		while (w->size == 0 && w != root) {
			node* p = w->parent;
			int idx = 0;
			while (p->children[idx] != w) idx++;

			node* left_sib = (idx > 0) ? p->children[idx - 1] : nullptr;
			node* right_sib = (idx < p->size) ? p->children[idx + 1] : nullptr;

			bool can_left = (left_sib && left_sib->size > 1);
			bool can_right = (right_sib && right_sib->size > 1);

            // Case 4a: Transfer Operation
			if (can_left || can_right) {
				bool choose_right = false;
                // Rule: If both are same size, choose Right. If one is 4-node, choose it.
				if (can_left && can_right) {
					if (right_sib->size >= left_sib->size) choose_right = true;
				} else choose_right = can_right;

				if (choose_right) {
                    // Rotate parent key down, sibling key up
					w->keys[0] = p->keys[idx];
                    w->size = 1;
					p->keys[idx] = right_sib->keys[0];
					w->children[1] = right_sib->children[0];
					if (w->children[1]) w->children[1]->parent = w;
					w->size = 1;
					for (int j = 0; j < right_sib->size - 1; j++) right_sib->keys[j] = right_sib->keys[j + 1];
					for (int j = 0; j < right_sib->size; j++) right_sib->children[j] = right_sib->children[j + 1];
					right_sib->size--;
				} else {
                    // Shift to make room for parent key
					w->children[1] = w->children[0];
					w->keys[0] = p->keys[idx - 1];
                    w->size = 1;
					p->keys[idx - 1] = left_sib->keys[left_sib->size - 1];
					w->children[0] = left_sib->children[left_sib->size];
					if (w->children[0]) w->children[0]->parent = w;
					left_sib->size--;
				}
				return true; // Underflow resolved via transfer
			} 
            // Case 4b: Fusion Operation
            else {
				if (right_sib) { // Rule: Priority choose Right for fusion
					w->keys[0] = p->keys[idx];
					w->size = 1;
					w->children[1] = right_sib->children[0];
					if (w->children[1]) w->children[1]->parent = w;
					for (int j = 0; j < right_sib->size; j++) {
						w->keys[w->size] = right_sib->keys[j];
						w->children[w->size + 1] = right_sib->children[j + 1];
						if (w->children[w->size + 1]) w->children[w->size + 1]->parent = w;
						w->size++;
					}
                    // Shrink parent: shift keys and children left
					for (int j = idx; j < p->size - 1; j++) p->keys[j] = p->keys[j + 1];
					for (int j = idx + 1; j < p->size; j++) p->children[j] = p->children[j + 1];
					p->size--;
					delete right_sib;
				} else { // Fuse with left sibling
					left_sib->keys[left_sib->size] = p->keys[idx - 1];
                    // Attach w's only child to left sibling
					left_sib->children[left_sib->size + 1] = w->children[0];
					if (left_sib->children[left_sib->size + 1]) left_sib->children[left_sib->size + 1]->parent = left_sib;
					left_sib->size++;
					for (int j = idx - 1; j < p->size - 1; j++) p->keys[j] = p->keys[j + 1];
					for (int j = idx; j < p->size; j++) p->children[j] = p->children[j + 1];
					p->size--;
					delete w;
				}
				w = p; // Step 4c: Propagate underflow check up to parent
			}
		}

		// Step 5: Adjust root if it was emptied by propagation
        if (root && root->size == 0) {
			node* old = root;
			root = root->children[0];
			if (root) root->parent = nullptr;
			delete old;
		}
		return true;
	}
    
    // sir's version
    bool insert(int num) {
	   // return false;
	   
	   node* w = search(num, root);
	   
	   if(w == nullptr){
	       root = new node(num);
	       return true;
	   }
	   
	   if(w->contains(num)){
	       return false;
	   }
	   
	   int i = 0;
	   for(i = 0; i < w->size; i++){
	       if(num < w->keys[i]){
	           break;
	       }
	   }
	   
	   w->insertKeyAt(num, i);
	   //while(w->size != 4){
	   //    return true;
	   //}
	   
	   while(w->size == 4){
	       
	       node* u;
	       int uch;
	       
	       if(w->parent == nullptr){
	           u = new node(w->keys[2]);
	           uch = 0;
	           root = u;
	       }else{
	           u = w->parent;
	           
	           for(int i = 0; i <= u->size; i++){
	               if(w == u->children[i]){
	                   uch = i;
	                   break;
	               }
	           }
	           
	           for(i = 0; i < u->size; i++){
	               if(num < u->keys[i]){
	                   break;
	               }
	           }
	           
	           
	           u->insertKeyAt(w->keys[2], i);
	           
	       }
	       
	       // latest part
	       node* wpr = new node(w->keys[0], u);
	       wpr->insertKeyAt(w->keys[1], 1);
	       
	       for(int j = 0; j < 3; j++){
	           wpr->children[j] = w->children[j];
	           
	           if(wpr->children[j]){
	               wpr->children[j]->parent = wpr;
	           }
	           
	       }
	       
	       node* w2pr = new node(w->keys[3], u);
	       for(int j = 0; j < 2; j++){
	           w2pr->children[j] = w->children[j + 3];
	           
	           if(w2pr->children[j]){
	               w2pr->children[j]->parent =  w2pr;
	           }
	           
	       }
	       
	       for(int i = 4; i >= uch; i--){
	           u->children[i] = u->children[i - 1];
	           
	       }
	       
	       u->children[uch] = wpr;
	       u->children[uch + 1] = w2pr;
	       
	       delete w;
	       w = u;
	   }
	   
	   return true;
	}
    
    // WARNING. Do not modify these methods.
    // Doing so will nullify your score for this activity.
	void print_node(string s, node* n) {
		cout << s << ": ";
		for (int i = 0; i < n->size; i++) {
			cout << n->keys[i] << " ";
		}
		cout << endl;
		for (int i = 0; i <= n->size; i++) {
			if (n->children[i]) {
				print_node("Child " + to_string(i+1) + " of " + s,n->children[i]);
			}
		}
	}
    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                cout << "Illegal parent of [" << curr->keys[0] << ",...]: NULL -- must be [" << par->keys[0] << ",...]" << endl;
            } else if (!par) {
                cout << "Illegal parent of [" << curr->keys[0] << ",...]: [" << curr->parent->keys[0] << ",...] -- must be NULL" << endl;
            } else {
                cout << "Illegal parent of [" << curr->keys[0] << ",...]: [" << curr->parent->keys[0] << ",...] -- must be [" << par->keys[0] << ",...]" << endl;
            }
            return false;
        }
        bool res = true;
        for (int i = 0; i < curr->size; i++) {
        	res &= check_parent(curr->children[i], curr);
		}
        return res;
    }

	void print() {
		print_node("Root", root);
		check_parent(root, NULL);
	}
    
    
};
