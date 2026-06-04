#include <iostream>
#include <algorithm> // for swap()
#include <cstdlib>   // for malloc()

using namespace std;

int* arr;
int n;
void print();
void sort_pivot(int, int);

int main(void) {
    // Hey there, start typing your C++ code here...
    cout << "Enter number of elements: ";
    cin >> n;
    arr = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i+1 << ": ";
        cin >> arr[i];
    }

    sort_pivot(0, n-1);
    cout << "Finish: ";
    print();

    return 0;
}

// TODO implement the sort_pivot method recursively
void sort_pivot(int start, int end) {
    // Pivot is the first element
    int pivot = arr[start];
    int lastGreen = start;

    // Partitioning iteration
    for (int i = start + 1; i <= end; i++) {
        // Green if smaller than pivot, purple if equal or larger
        if (arr[i] < pivot) {
            lastGreen++;
            // If purple exists, i will be ahead of lastGreen
            if (i != lastGreen) {
                swap(arr[i], arr[lastGreen]);
                print();
            }
        }
    }

    // Swap pivot with the last green if it exists
    if (lastGreen != start) {
        swap(arr[start], arr[lastGreen]);
        print();
    }

    // Recursive calls: Only do it when start is less than end
    // Left partition
    if (start < lastGreen - 1) {
        sort_pivot(start, lastGreen - 1);
    }
    // Right partition
    if (lastGreen + 1 < end) {
        sort_pivot(lastGreen + 1, end);
    }
}

void print() {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n-1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}