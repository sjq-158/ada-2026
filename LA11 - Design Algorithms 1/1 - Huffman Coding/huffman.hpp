#include "heap.hpp"

// TODO huffman
node* huffman_code(Heap* heap) {
    // return nullptr;
    
    while(heap->size() > 1){
        
        node* n1 = heap->removeMin();
        node* n2 = heap->removeMin();
        
        node* parent = new node('\0', n1->weight + n2->weight);
        
        parent->left = n1;
        parent->right = n2;
        
        n1->parent = parent;
        n2->parent = parent;
        
        heap->insert(parent);
        
    }
    
    return heap->removeMin();
}