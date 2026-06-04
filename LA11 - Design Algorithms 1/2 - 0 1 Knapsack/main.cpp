#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// function 
int knapsack(int n, int w, int items[], int weight[]){
    
    int dp[n + 1][w + 1]; 
    
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= w; j++){
            
            if(i == 0 || w == 0){
                dp[i][j] = 0;
            }else if(weight[i - 1] <= j){
                dp[i][j] = max((items[i - 1] + dp[i - 1][j - weight[i - 1]]), dp[i - 1][j]);
            }else{
                dp[i][j] = dp[i - 1][j];
            }
            
        }
    }
    
    return dp[n][w];
}

int main(){
    
    // n items, w weight capacity
    int n, w;
    cout << "Enter number of items and weight capacity: ";
    cin >> n;
    cin >> w;
    
    int items[n];
    int weight[n]; // capacity is the limit of the values not the size
    
    cout << "Enter value and weight of each item:" << endl;
    for(int i = 0; i < n; i++){
        cin >> items[i] >> weight[i];
    }
    
    cout << "Maximum value in Knapsack = " << knapsack(n, w, items, weight);
    
    return 0;
}