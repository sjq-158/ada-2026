#include <iostream>
#include <string>
using namespace std;

struct node {
	char ch;
	int weight;
	node *left, *right, *parent;

	node(char c, int w) : ch(c), weight(w), left(nullptr), right(nullptr), parent(nullptr) {};

	// TODO getCode
	string getCode() {
	   // return "";
	   string code = "";
	   node* curr = this;
	   
	   while(curr->parent){
	       code = (curr == curr->parent->left) ? ("0" + code) : ("1" + code);
	       curr = curr->parent;
	   }
	   
	   return code;
	}
};