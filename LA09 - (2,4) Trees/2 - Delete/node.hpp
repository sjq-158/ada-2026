#pragma once
#include <cstdlib>

using namespace std;

struct node {
	node* parent;
	int keys[4];
	node** children;
	int size = 0;
	
	// sir's version
	node(int key) : children((node**) calloc(5, sizeof(node*))), parent(nullptr), size(1){
	    keys[0] = key;
	}
	
	node(int key, node* p) : children((node**) calloc(5, sizeof(node*))), parent(p), size(1){
	    keys[0] = key;
	}
	
    void insertKeyAt(int key, int index){
	    for(int i = 3; i > index; i--){
	        keys[i] = keys[i - 1];
	    }
	    
	    keys[index] = key;
	    size++;
	}
	
	bool contains(int num){
	    // okay
        for(int i = 0; i < size; i++){
            if(num == keys[i]){
                return true;
            }
        }
        return false;
        
	}
	
};


// previous
// #include <cstdlib>

// using namespace std;

// struct node {
// 	node* parent;
// 	int keys[4];
// 	node** children; // original
// 	int size = 0; // no of keys
	
// 	// sir's version
// 	node(int key) : children((node**) calloc(5, sizeof(node*))), parent(nullptr), size(1){
// 	    keys[0] = key;
// 	}
	
// 	node(int key, node* p) : children((node**) calloc(5, sizeof(node*))), parent(p), size(1){
// 	    keys[0] = key;
// 	}
	
//     void insertKeysAt(int key, int index){
// 	    for(int i = 3; i > index; i--){
// 	        keys[i] = keys[i - 1];
// 	    }
	    
// 	    keys[index] = key;
// 	    size++;
// 	}
	
// 	bool contains(int num){
// 	    // okay
//         for(int i = 0; i < size; i++){
//             if(num == keys[i]){
//                 return true;
//             }
//         }
//         return false;
        
// 	}
	
// 	// ======================================================================
//     // added
// //     node** children = (node**) calloc(5, sizeof(node*));
// // 	int children_size = 0; // no of nodes 
	
// // 	// added functions
// // 	bool searchKey(int num){
        
// //         // okay
// //         for(int i = 0; i < size; i++){
// //             if(num == keys[i]){
// //                 return true;
// //             }
// //         }
// //         return false;
        
// //     }
	
// // 	void addKey(int num){
	    
// // 	   // if(size == 0){
// // 	   //     // add last
// // 	   //     keys[size++] = num;
// // 	   //     return;
// // 	   // }else{
	        
// // 	   //     // there is size - 1 and traverse --> where??? HAHHAHAHH 
// // 	   //     for(int i = 0; i < size - 1; i++){
	            
// // 	   //         if(num < keys[i]){
// // 	   //             // shift left --> ???
// // 	   //             for(int j = size; j > i; j--){
// // 	   //                 keys[j] = keys[j - 1];
// // 	   //             }
	                
// // 	   //             keys[i] = num;
// // 	   //             size++;
// // 	   //             return;
// // 	   //         }
	            
// // 	   //     }
	        
// // 	   //     keys[size++] = num; // add last large
// // 	   // }
	    
// // 	    // another version
// // 	    if(size == 0){
// // 	        // add last
// // 	        keys[size++] = num;
// // 	        return;
// // 	    }else{
	        
// // 	        // there is size - 1 and traverse --> where??? HAHHAHAHH 
// // 	        for(int i = 0; i < size; i++){
	            
// // 	            if(num < keys[i]){
// // 	                // shift left --> ???
// // 	                for(int j = size; j > i; j--){
// // 	                    keys[j] = keys[j - 1];
// // 	                }
	                
// // 	                keys[i] = num;
// // 	                size++;
// // 	                return;
// // 	            }
	            
// // 	        }
	        
// // 	        keys[size++] = num; // add last large
// // 	    }
	    
// // 	    // sir's
// // 	   // for(int i = 3; i > 0; i--){
// // 	   //     keys[i] = keys[i - 1];
// // 	   // }
	    
// // 	   // keys[0] = num;
// // 	   // size++;
// // 	}
    
// //     void removeKey(int num){
        
// //         // kinda similar to insert
        
// //         for(int i = 0; i < size - 1; i++){
// //             if(num == keys[i]){
// //                 for(int j = size; j > i; j--){
// //                     keys[j] = keys[j - 1];
// //                     size--;
// //                 }
// //             }
// //         }
        
// //     }
    
// //     void setChildren(node* left, node* right, node* curr){
        
// //         // has parameters - left, right, curr 
// //         // setting the children stupidddd 
        
// //         if(children_size == 0){
// //             children[0] = left;
// //             children[1] = right;
// //             children_size+=2; // either one or two --> i think it is two since it is 2,4 tree
// //             // children_size++;
// //             return;
// //         }else{
            
// //             // similar to removeKey
// //             for(int i = 0; i < children_size - 1; i++){
                
// //                 if(curr == children[i]){
                    
// //                     // shift the children nodes 
// //                     for(int j = children_size; j > i; j--){
// //                         children[j] = children[j - 1];
// //                     }
                    
// //                     // left - node - right
// //                     children[i] = left;
// //                     children[i + 1] = right;
// //                     break;
// //                 }
                
// //             }
            
// //             children_size++;
            
// //             // left - keys[0], keys[1] ----- children[0], children[1], children[2]
// //             // middle - keys[2]
// //             // right - keys[3] ----- children[3], children[4]
            
                        
// //         }
        
// //         if(children_size != 0){
                
// //                 adopt(left, 0, curr, 0);
// //                 adopt(left, 1, curr, 1);
// //                 adopt(left, 2, curr, 2);
                
// //                 adopt(right, 0, curr, 3);
// //                 adopt(right, 1, curr, 4); 
// //             }
        
// //     }
    
// //     // reassignment of nodes 
// //     void adopt(node* newparent, int pos1, node* oldparent, int pos2){
        
// //         // okay
// //         // node* child = oldparent->children[pos2];
// //         // newparent->children[pos1] = child;
// //         // child->parent = newparent;
// //         // newparent->children_size++;
        
// //         node* child = oldparent->children[pos2];
// //         newparent->children[pos1] = child;
// //         child->parent = newparent;
// //         newparent->children_size++;
        
// //     }
    
// //     bool isFullNode(){
// //         return children_size == 5; //  max capacity of nodes 
// //     }
    
// //     bool isFullKey(){
// //         return size == 4; // max capacity of keys 
// //     }
    
// };