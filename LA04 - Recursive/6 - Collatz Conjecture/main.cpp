#include <iostream>
#include "hfile.hpp"
using namespace std;
int main() {
    cout << "Enter a number: ";
    int n;
    cin >> n;
    collatz(n);
    return 0;
}   