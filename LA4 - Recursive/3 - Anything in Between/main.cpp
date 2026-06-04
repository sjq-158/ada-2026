#include <iostream>
#include "hfile.hpp"
using namespace std;
int main() {
    int n, m;
    cout << "From: ";
    cin >> n;
    cout << "To: ";
    cin >> m;
    between(n, m);
    return 0;
}