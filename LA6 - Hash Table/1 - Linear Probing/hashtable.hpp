#include <cstdlib>
#include <iostream>
using namespace std;

template <typename K>
class HashTable {
  public:
  virtual int hash_code(K key) = 0;
  virtual int compress(int code) = 0;
  virtual int insert(K key) = 0;
  virtual int search(K key) = 0;
  virtual int remove(K key) = 0;
  virtual void print() = 0;

  // Using the knowledge that a hash function is composed of two portions
  int hashfn(K key) {
    return compress(hash_code(key));
  }
};