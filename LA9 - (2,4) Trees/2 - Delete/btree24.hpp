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
    
    // TODO remove
	bool remove(int num) {
// 		return false;

        node* w = search(num, root);
        
        if(w == nullptr){
            return false;
        }
        
        if(!w->contains(num)){
	        return false;
	    }
        
        for(int i = 0; i < w->size; i++){
	       w->keys[i] = w->keys[i + 1];
	   }
        
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

// #include "node.hpp"
// #include <iostream>

// using namespace std;

// class BTree24 {
// 	node* root;
    
//     // sir's 
//     node* search(int num, node* n){
//         if(n == nullptr){
//             return nullptr;
//         }
        
//         for(int i = 0; i < n->size; i++){
//             if(num == n->keys[i]){
//                 return n; // duplicate values
//             }
                    
//             if(num < n->keys[i]){
//                 if(n->children[i]){
//                     return search(num, n->children[i]);
//                 }
                        
//                 return n;
//             }
                        
                    
//         }
//         if(n->children[n->size]){
//             return search(num, n->children[n->size]);
//         }
//         return n;
//     }
    
    
    
//     // ================================================================================
//     // to add
//     // node* search(int num){
        
//     //     // okay?
//     //     node* curr = root;
        
//     //     if(curr == nullptr){
//     //         return nullptr;
//     //     }else{
            
//     //         // traverse nodes
//     //         while(curr->children_size != 0){
                
//     //             for(int i = 0; i < curr->size; i++){
//     //                 if(num == curr->keys[i]){
//     //                     return nullptr; // duplicate values
//     //                 }
                    
//     //                 if(num < curr->keys[i]){
//     //                     curr = curr->children[i];
//     //                     break;
//     //                 }else if(i == curr->size - 1){
//     //                     curr = curr->children[curr->children_size - 1];
//     //                 }
//     //             }
//     //         }
            
//     //     }
        
//     //     // check duplicate keys again
//     //     for(int i = 0; i < curr->size; i++){
//     //         if(num == curr->keys[i]){
//     //             return nullptr;
//     //         }
//     //     }
        
//     //     return curr;
//     // }
    
//     // void split(node* curr){
        
//     //     node* left = new node;
//     //     node* right = new node;
        
//     //     // set left and right
//     //     // left - keys[0], keys[1]
//     //     // middle - keys[2]
//     //     // right - keys[3]
        
//     //     left->addKey(curr->keys[0]);
//     //     left->addKey(curr->keys[1]);
        
//     //     right->addKey(curr->keys[3]);
        
//     //     node* parent = nullptr; // create parent node 
        
//     //     if(curr == root){
//     //         parent = new node;
            
//     //         parent->addKey(curr->keys[2]);
//     //         parent->setChildren(left, right, curr);
            
//     //         // parent->children_size++;
//     //         root = parent;
//     //     }else{
//     //         parent = curr->parent;
            
//     //         parent->addKey(curr->keys[2]);
//     //         parent->setChildren(left, right, curr);
            
//     //         // parent->children_size++;
//     //         if(parent->isFullNode()){
//     //             split(parent); // recursive call 
//     //         }
//     //     }
        
//     // }
    
    
//     // original
// 	public:
// 	BTree24() {
// 		root = nullptr;
// 	}
    
//     // sir's version
//     bool insert(int num) {
// 	   // return false;
	   
// 	   node* w = search(num, root);
	   
// 	   if(w == nullptr){
// 	       root = new node(num);
// 	       return true;
// 	   }
	   
// 	   if(w->contains(num)){
// 	       return false;
// 	   }
	   
// 	   int i = 0;
// 	   for(i = 0; i < w->size; i++){
// 	       if(num < w->keys[i]){
// 	           break;
// 	       }
// 	   }
	   
// 	   w->insertKeysAt(num, i);
// 	   //while(w->size != 4){
// 	   //    return true;
// 	   //}
	   
// 	   while(w->size == 4){
	       
// 	       node* u;
// 	       int uch;
	       
// 	       if(w->parent == nullptr){
// 	           u = new node(w->keys[2]);
// 	           uch = 0;
// 	           root = u;
// 	       }else{
// 	           u = w->parent;
	           
// 	           for(int i = 0; i <= u->size; i++){
// 	               if(w == u->children[i]){
// 	                   uch = i;
// 	                   break;
// 	               }
// 	           }
	           
// 	           for(i = 0; i < u->size; i++){
// 	               if(num < u->keys[i]){
// 	                   break;
// 	               }
// 	           }
	           
	           
// 	           u->insertKeysAt(w->keys[2], i);
	           
// 	       }
	       
// 	       // latest part
// 	       node* wpr = new node(w->keys[0], u);
// 	       wpr->insertKeysAt(w->keys[1], 1);
	       
// 	       for(int j = 0; j < 3; j++){
// 	           wpr->children[j] = w->children[j];
	           
// 	           if(wpr->children[j]){
// 	               wpr->children[j]->parent = wpr;
// 	           }
	           
// 	       }
	       
// 	       node* w2pr = new node(w->keys[3], u);
// 	       for(int j = 0; j < 2; j++){
// 	           w2pr->children[j] = w->children[j + 3];
	           
// 	           if(w2pr->children[j]){
// 	               w2pr->children[j]->parent =  w2pr;
// 	           }
	           
// 	       }
	       
// 	       for(int i = 4; i >= uch; i--){
// 	           u->children[i] = u->children[i - 1];
	           
// 	       }
	       
// 	       u->children[uch] = wpr;
// 	       u->children[uch + 1] = w2pr;
	       
// 	       delete w;
// 	       w = u;
// 	   }
	   
// 	   return true;
// 	}
    
// // 	bool insert(int num) {
// // 	   // return false; // original
	   
// // 	   // okay
// // 	   if(root == nullptr){
// // 	       root = new node;
// // 	       root->addKey(num);
// // 	   }else{
	       
// // 	       node* searchednode = search(num);
	       
// // 	       if(searchednode == nullptr){
// // 	           return false; // duplicate
// // 	       }
	       
// // 	       searchednode->addKey(num);
	       
// // 	       if(searchednode->isFullNode()){
// // 	           split(searchednode);
// // 	       }
	       
// // 	   }
	   
// // 	   return true;
// // 	}

// 	// WARNING. Do not modify these methods.
//     // Doing so will nullify your score for this activity.
// 	void print_node(string s, node* n) {
// 		cout << s << ": ";
// 		for (int i = 0; i < n->size; i++) {
// 			cout << n->keys[i] << " ";
// 		}
// 		cout << endl;
// 		for (int i = 0; i <= n->size; i++) {
// 			if (n->children[i]) {
// 				print_node("Child " + to_string(i+1) + " of " + s,n->children[i]);
// 			}
// 		}
// 	}
//     bool check_parent(node* curr, node* par) {
//         if (!curr) {
//             return true;
//         }
//         if (curr->parent != par) {
//             if (!curr->parent) {
//                 cout << "Illegal parent of [" << curr->keys[0] << ",...]: NULL -- must be [" << par->keys[0] << ",...]" << endl;
//             } else if (!par) {
//                 cout << "Illegal parent of [" << curr->keys[0] << ",...]: [" << curr->parent->keys[0] << ",...] -- must be NULL" << endl;
//             } else {
//                 cout << "Illegal parent of [" << curr->keys[0] << ",...]: [" << curr->parent->keys[0] << ",...] -- must be [" << par->keys[0] << ",...]" << endl;
//             }
//             return false;
//         }
//         bool res = true;
//         for (int i = 0; i < curr->size; i++) {
//         	res &= check_parent(curr->children[i], curr);
// 		}
//         return res;
//     }

// 	void print() {
// 		print_node("Root", root);
// 		check_parent(root, NULL);
// 	}
// };