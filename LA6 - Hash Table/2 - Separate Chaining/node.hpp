#include <iostream>
#include <string>
#include <cstring>
using namespace std;
struct node {
	string elem;
	node* next;
	
	node(string key){
	    this->elem = key;
	    next = nullptr;
	}
	
};