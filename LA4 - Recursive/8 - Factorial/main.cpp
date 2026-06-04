#include <iostream>
#include "hfile.hpp"
using namespace std;
int main() {
    printf("Enter a number: ");
    int n;
    scanf("%d", &n);
    cout << "Factorial of " << n << " is " << factorial(n);

    return 0;
}