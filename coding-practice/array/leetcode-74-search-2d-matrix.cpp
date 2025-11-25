/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 74                                                           ║
║ Problem Name  : Search a 2D Matrix                                          ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Array, Binary Search, Matrix                                ║
║ Company Tags  : Amazon, Microsoft, Google, Facebook, Apple                  ║
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

💡 APPROACHES:
1. Brute Force: Check every element - O(m*n) time, O(1) space
2. Row-wise Binary Search: Binary search each row - O(m*log n) time, O(1) space
3. Treat as 1D Array: Single binary search - O(log(m*n)) time, O(1) space (OPTIMAL)

⏰ OPTIMAL SOLUTION: Treat 2D matrix as 1D sorted array
💾 TIME COMPLEXITY:  O(log(m*n)) - Single binary search
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution {
public:
    /**
     * @brief Searches target in 2D matrix using binary search (OPTIMAL)
     * @param matrix 2D sorted matrix
     * @param target Target value to search
     * @return bool True if target found, false otherwise
     * 
     * Algorithm:
     * 1. Treat 2D matrix as 1D sorted array
     * 2. Use binary search on virtual 1D array
     * 3. Convert 1D index to 2D coordinates: row = mid/n, col = mid%n
     * 4. Compare matrix[row][col] with target
     */
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        
        int m = matrix.size();    // number of rows
        int n = matrix[0].size(); // number of columns
        
        int left = 0;
        int right = m * n - 1;    // total elements - 1
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Convert 1D index to 2D coordinates
            int row = mid / n;
            int col = mid % n;
            int midValue = matrix[row][col];
            
            if (midValue == target) {
                return true;
            } else if (midValue < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return false;
    }
    
    /**
     * @brief Row-wise binary search approach (for comparison)
     * @param matrix 2D sorted matrix
     * @param target Target value to search
     * @return bool True if target found, false otherwise
     */
    bool searchMatrixRowWise(vector<vector<int>>& matrix, int target) {
        for (auto& row : matrix) {
            if (binarySearch(row, target)) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * @brief Helper function for binary search in 1D array
     */
    bool binarySearch(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return true;
            else if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return false;
    }
    
    /**
     * @brief Brute force approach (for comparison)
     * @param matrix 2D sorted matrix
     * @param target Target value to search
     * @return bool True if target found, false otherwise
     */
    bool searchMatrixBruteForce(vector<vector<int>>& matrix, int target) {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] == target) {
                    return true;
                }
            }
        }
        return false;
    }
    
    /**
     * @brief Smart linear search starting from top-right (alternative approach)
     * @param matrix 2D sorted matrix
     * @param target Target value to search
     * @return bool True if target found, false otherwise
     */
    bool searchMatrixTopRight(vector<vector<int>>& matrix, int target) {
        int row = 0;
        int col = matrix[0].size() - 1;
        
        while (row < matrix.size() && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                col--; // Move left
            } else {
                row++; // Move down
            }
        }
        return false;
    }
};

/**
 * @brief Utility function to print 2D matrix
 */
void printMatrix(const vector<vector<int>>& matrix, const string& label) {
    cout << label << ":" << endl;
    for (const auto& row : matrix) {
        cout << "[";
        for (int i = 0; i < row.size(); i++) {
            cout << row[i];
            if (i < row.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

/**
 * @brief Test function for a single case
 */
void testCase(vector<vector<int>>& matrix, int target, bool expected, const string& description) {
    Solution solution;
    bool result = solution.searchMatrix(matrix, target);
    string status = (result == expected) ? "✅ PASSED" : "❌ FAILED";
    cout << status << ": " << description << " -> " << (result ? "true" : "false") << endl;
    assert(result == expected);
}

/**
 * @brief Comprehensive test function
 */
void runTests() {
    cout << "🧪 Running Comprehensive Tests:" << endl;
    cout << "===============================" << endl;
    
    // Test Case 1: Target exists
    vector<vector<int>> matrix1 = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    testCase(matrix1, 3, true, "Target 3 exists in matrix");
    
    // Test Case 2: Target doesn't exist
    vector<vector<int>> matrix2 = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    testCase(matrix2, 13, false, "Target 13 doesn't exist in matrix");
    
    // Test Case 3: Single element matrix - target exists
    vector<vector<int>> matrix3 = {{1}};
    testCase(matrix3, 1, true, "Single element matrix - target exists");
    
    // Test Case 4: Single element matrix - target doesn't exist
    vector<vector<int>> matrix4 = {{1}};
    testCase(matrix4, 2, false, "Single element matrix - target doesn't exist");
    
    // Test Case 5: Target at first position
    vector<vector<int>> matrix5 = {{1,3,5,7},{10,11,16,20}};
    testCase(matrix5, 1, true, "Target at first position");
    
    // Test Case 6: Target at last position
    vector<vector<int>> matrix6 = {{1,3,5,7},{10,11,16,20}};
    testCase(matrix6, 20, true, "Target at last position");
    
    // Test Case 7: Single row matrix
    vector<vector<int>> matrix7 = {{1,3,5,7,9,11}};
    testCase(matrix7, 5, true, "Single row matrix - target exists");
    
    // Test Case 8: Single column matrix
    vector<vector<int>> matrix8 = {{1},{3},{5},{7}};
    testCase(matrix8, 5, true, "Single column matrix - target exists");
    
    cout << "\n🎉 All tests passed!" << endl;
}

/**
 * @brief Performance comparison demonstration
 */
void performanceComparison() {
    cout << "\n📊 Performance Comparison:" << endl;
    cout << "=========================" << endl;
    cout << "Approach              | Time        | Space | Best For" << endl;
    cout << "----------------------|-------------|-------|----------" << endl;
    cout << "Binary Search (1D)    | O(log(m*n)) | O(1)  | Optimal solution" << endl;
    cout << "Row-wise Binary       | O(m*log n)  | O(1)  | When rows are independent" << endl;
    cout << "Top-Right Search      | O(m + n)    | O(1)  | Alternative approach" << endl;
    cout << "Brute Force           | O(m * n)    | O(1)  | Simple but inefficient" << endl;
    cout << "                      |             |       |" << endl;
    cout << "Recommendation: Use Binary Search (1D) for optimal O(log(m*n)) solution!" << endl;
}

/**
 * @brief Step-by-step walkthrough
 */
void stepByStepDemo() {
    cout << "\n💡 Step-by-step Walkthrough (Binary Search):" << endl;
    cout << "============================================" << endl;
    
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    int target = 11;
    
    cout << "Matrix: [[1,3,5,7],[10,11,16,20],[23,30,34,60]]" << endl;
    cout << "Target: " << target << endl;
    cout << "Treat as 1D: [1,3,5,7,10,11,16,20,23,30,34,60]" << endl;
    cout << "Indices:      0 1 2 3 4  5  6  7  8  9 10 11" << endl << endl;
    
    cout << "Step 1: left=0, right=11, mid=5" << endl;
    cout << "  1D index 5 -> 2D: row=5/4=1, col=5%4=1" << endl;
    cout << "  matrix[1][1] = 11 == target ✓" << endl;
    cout << "  Found at position (1,1)!" << endl;
}

/**
 * @brief Demonstrate coordinate conversion
 */
void demonstrateCoordinateConversion() {
    cout << "\n🔄 1D to 2D Coordinate Conversion:" << endl;
    cout << "==================================" << endl;
    
    int m = 3, n = 4; // 3x4 matrix
    cout << "For 3x4 matrix:" << endl;
    cout << "1D Index | 2D Coordinates (row, col)" << endl;
    cout << "---------|------------------------" << endl;
    
    for (int i = 0; i < m * n; i++) {
        int row = i / n;
        int col = i % n;
        cout << "   " << i << "     |     (" << row << ", " << col << ")" << endl;
    }
}

/**
 * @brief Main function demonstrating the solution
 */
int main() {
    cout << "🔍 LeetCode 74: Search a 2D Matrix" << endl;
    cout << "===================================" << endl;
    
    // Run comprehensive tests
    runTests();
    
    // Performance comparison
    performanceComparison();
    
    // Step-by-step demonstration
    stepByStepDemo();
    
    // Coordinate conversion demo
    demonstrateCoordinateConversion();
    
    cout << "\n🚀 Interactive Example:" << endl;
    cout << "=======================" << endl;
    
    Solution solution;
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    
    printMatrix(matrix, "Matrix");
    
    vector<int> testTargets = {3, 11, 13, 1, 60};
    for (int target : testTargets) {
        bool found = solution.searchMatrix(matrix, target);
        cout << "Search " << target << ": " << (found ? "Found ✓" : "Not Found ✗") << endl;
    }
    
    return 0;
}

/*
🎯 KEY LEARNINGS:
1. Treat sorted 2D matrix as 1D array for optimal binary search
2. Coordinate conversion: row = index/cols, col = index%cols
3. Binary search achieves O(log(m*n)) time complexity
4. Matrix properties enable efficient search algorithms

🚀 RELATED PROBLEMS:
- LeetCode 240: Search a 2D Matrix II
- LeetCode 378: Kth Smallest Element in Sorted Matrix
- LeetCode 1351: Count Negative Numbers in Sorted Matrix
- LeetCode 1572: Matrix Diagonal Sum

📚 CONCEPTS PRACTICED:
- Binary search optimization
- 2D to 1D coordinate mapping
- Matrix traversal techniques
- Time complexity analysis
- Multiple solution approaches comparison
*/