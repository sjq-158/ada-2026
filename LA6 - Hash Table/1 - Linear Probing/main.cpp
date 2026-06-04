#include <iostream>
#include <stdexcept>
#include "htlinear.hpp"
using namespace std;

int main(void) {
  cout << "Enter capacity of hash table: ";
  int N;
  cin >> N;

  HashTable<int> *table = new HTLinear<int>(N);

  char op;
  int key;
  do {
  	try {
	    cout << "Operation: ";
	    cin >> op;

	    switch (op) {
	      case 'i': // Insert
	        cin >> key;
	        cout << table->insert(key) << endl;
	        break;

	      case 's': // Search
	        cin >> key;
	        cout << table->search(key) << endl;
	        break;

	      case 'r': // Delete
	        cin >> key;
	        cout << table->remove(key) << endl;
	        break;

	      case 'p':
	        table->print();
	        break;

	      case 'x':
	        cout << "Exiting";
	        break;

	      default:
	      	cout << "Invalid operation. Try again." << endl;
	    }
	} catch (exception& e) {
		cout << e.what() << endl;
	}
  } while (op != 'x');

  return 0;
}