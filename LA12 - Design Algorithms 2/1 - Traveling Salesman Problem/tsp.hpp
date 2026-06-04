#include <iostream>
#include <climits>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

class TSP{
    
    private:
    int n; // size
    int** graph;
    bool* visited; // array of visited rows
    int minimumCost;
    
    
    public:
    TSP(int cities, int** matrix){
        n = cities;
        graph = matrix;
        visited = (bool*) malloc(n * sizeof(bool));
        minimumCost = INT_MAX;
    }
    
    int calculateBound(int cost){
        
        int bound = cost;
        
        for(int i = 0; i < n; i++){
            if(!visited[i]){
                
                int minEdge = INT_MAX;
                for(int j = 0; j < n; j++){
                    
                    if(i != j){
                        minEdge = min(graph[i][j], minEdge);
                    }
                    
                }
                
                bound += minEdge;
            }
        }
        
        return bound;
    }
    
    void branchAndBound(int currentCity, int count, int currentCost){
        
        if(count == n){
            
            int totalCost = currentCost + graph[currentCity][0];
            minimumCost = min(totalCost, minimumCost);
            
            return;
        }
        
        for(int nextCity = 0; nextCity < n; nextCity++){
            
            if(!visited[nextCity]){
                visited[nextCity] = true;
                
                
                int newCost = currentCost + graph[currentCity][nextCity];
                int bound = calculateBound(newCost);
                
                // pruning
                if(bound < minimumCost){
                    branchAndBound(nextCity, count + 1, newCost);
                }
                
                visited[nextCity] = false;
            }
            
        }
        
    }
    
    void solve(){
        for(int i = 0; i < n; i++){
            visited[i] = false;
        }
        
        visited[0] = true;
        
        branchAndBound(0, 1, 0);
        
        cout << "Minimum cost: " << minimumCost << endl;
    }
    
    // int bnb(int currentCity, int count, int currentCost){
        
    //     if(count == n){
            
    //         int totalCost = currentCost + graph[currentCity][0];
    //         minimumCost = min(totalCost, minimumCost);
            
    //         return minimumCost;
    //     }
        
    //     for(int nextCity = 0; nextCity < n; nextCity++){
            
    //         if(!visited[nextCity]){
    //             visited[nextCity] = true;
                
                
    //             int newCost = currentCost + graph[currentCity][nextCity];
    //             int bound = calculateBound(newCost);
                
    //             // pruning
    //             if(bound < minimumCost){
    //                 return bnb(nextCity, count + 1, newCost);
    //             }
                
    //             visited[nextCity] = false;
    //         }
            
    //     }
        
    //     return minimumCost;
    // }
};