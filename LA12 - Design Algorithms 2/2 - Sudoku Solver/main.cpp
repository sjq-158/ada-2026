#include <iostream>

using namespace std;

bool isValid(int grid[9][9], int row, int column, int k){
    
    // check row
    for(int j = 0; j < 9; j++){
        if(grid[row][j] == k){
            return false;
        }
    }
    
    // check column
    for(int i = 0; i < 9; i++){
        if(grid[i][column] == k){
            return false;
        }
    }
    
    int startRow = (row / 3) * 3;
    int startColumn = (column / 3) * 3;
    
    for(int i = startRow; i < startRow + 3; i++){
        for(int j = startColumn; j < startColumn + 3; j++){
            
            if(grid[i][j] == k){
                return false;
            }
            
        }
    }
    
    return true;
}

bool solve(int grid[9][9], int row = 0, int column = 0){
    
    if(row == 9){
        return true; 
    }else if(column == 9){
        return solve(grid, row + 1, 0);
    }else if(grid[row][column] != 0){
        return solve(grid, row, column + 1);
    }else{
        
        for(int k = 1; k <= 9; k++){
            if(isValid(grid, row, column, k)){
                grid[row][column] = k;
                
                if(solve(grid, row, column + 1)){
                    return true;
                }
                
                grid[row][column] = 0;
            }
        }
        
        
    }
    
    return false;
}

void print(int grid[9][9]){
    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cout << grid[i][j] << " ";
        }
        
        cout << endl;
        
    }
    
}

int main(){
    
    int grid[9][9];
    
    cout << "Enter the Sudoku board: " << endl;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cin >> grid[i][j];
        }
    }
    
    cout << endl;
    cout << "Solved Board: " << endl;
    if(solve(grid, 0, 0)){
        print(grid);
    }else{
        cout << "No solution" << endl;
    }
    
    return 0;
}