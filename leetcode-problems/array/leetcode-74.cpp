/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                           ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 74                                                           ║
║ Problem Name  : Search a 2D Matrix                                           ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Array, Binary Search, Matrix                                 ║
║ Company Tags  : Amazon, Microsoft, Google, Facebook, Apple                   ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
You are given an m x n integer matrix with the following properties:
- Each row is sorted in non-decreasing order
- The first integer of each row is greater than the last integer of the previous row
Given an integer target, return true if target is in matrix or false otherwise.
You must write a solution in O(log(m * n)) time complexity.

📝 EXAMPLES:
Input:  matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Input:  matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false

🎯 CONSTRAINTS:
- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 100
- -10^4 <= matrix[i][j], target <= 10^4

💡 APPROACH:
Treat 2D matrix as 1D sorted array
1. Use binary search on virtual 1D array
2. Convert 1D index to 2D coordinates: row = mid/n, col = mid%n
3. Compare matrix[row][col] with target

⏰ TIME COMPLEXITY:  O(log(m*n)) - Single binary search
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / n, col = mid % n;
        int midValue = matrix[row][col];
        
        if (midValue == target) return true;
        else if (midValue < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

int main() {
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    int target = 3;
    bool result = searchMatrix(matrix, target);
    cout << (result ? "true" : "false") << endl;
    return 0;
}
