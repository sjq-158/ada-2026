#include <iostream>
#include "hfile.hpp"
using namespace std;
int main() {
    cout << "Enter a number: ";
    int n;
    cin >> n;
    int res = factor(n);
    cout << endl << "Number of factors: " << res;
    return 0;
}