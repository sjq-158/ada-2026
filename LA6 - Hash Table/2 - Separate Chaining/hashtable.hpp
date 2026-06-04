#include <cstdlib>
#include <iostream>
using namespace std;

class HashTable {
  public:
  virtual int hash_code(string key) = 0;
  virtual int compress(int code) = 0;
  virtual int insert(string key) = 0;
  virtual int search(string key) = 0;
  virtual int remove(string key) = 0;
  virtual void print() = 0;

  // Using the knowledge that a hash function is composed of two portions
  int hashfn(string key) {
    return compress(hash_code(key));
  }
};