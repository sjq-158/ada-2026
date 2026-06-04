#include <iostream>
#include "hfile.hpp"
using namespace std;
int main() {
    cout << "Enter a number: ";
    int n;
    cin >> n;
    int res = sumOfDigits(n);
    cout << "Sum of digits of " << n << " = " << res;
    return 0;
}