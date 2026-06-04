#include <iostream>
#include "hfile.hpp"
using namespace std;
int main() {
    cout << "Enter a number: ";
    int n;
    cin >> n;
    cout << fibonacci(n);

    return 0;
}