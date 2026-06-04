#include <iostream>
#include "tsp.hpp"

using namespace std;

int main(){
    
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    
    int** graph = (int**) malloc(n * sizeof(int*));
    
    for(int i = 0; i < n; i++){
        graph[i] = (int*) malloc(n * sizeof(int));
    }
    
    cout << "Enter adjacency matrix: " << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> graph[i][j];
        }
    }
    
    TSP* tsp = new TSP(n, graph);
    tsp->solve();
    // int result = tsp->bnb(0, 1, 0);
    // cout << "Minimum cost: " << result << endl;
    
    return 0;
}