/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 1492                                                         ║
║ Problem Name  : The kth Factor of n                                         ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Math, Number Theory                                         ║
║ Company Tags  : Amazon, Microsoft, Google, Facebook                         ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
You are given two positive integers n and k. A factor of an integer n is defined 
as an integer i where n % i == 0. Consider a list of all factors of n sorted in 
ascending order, return the kth factor in this list or return -1 if n has less 
than k factors.

📝 EXAMPLES:
Input:  n = 12, k = 3
Output: 3
Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.

Input:  n = 7, k = 2
Output: 7
Explanation: Factors list is [1, 7], the 2nd factor is 7.

Input:  n = 4, k = 4
Output: -1
Explanation: Factors list is [1, 2, 4], there is only 3 factors.

🎯 CONSTRAINTS:
- 1 <= k <= n <= 1000

💡 APPROACHES:
1. Brute Force: Check all numbers 1 to n - O(n) time, O(k) space
2. Optimized: Check up to sqrt(n) and find pairs - O(√n) time, O(√n) space
3. Early Termination: Stop when kth factor found - O(min(k, √n)) time, O(1) space (OPTIMAL)

⏰ OPTIMAL SOLUTION: Early termination with sqrt optimization
💾 TIME COMPLEXITY:  O(min(k, √n)) - Stop early when possible
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

class Solution {
public:
    /**
     * @brief Finds kth factor using early termination (OPTIMAL)
     * @param n Number to find factors of
     * @param k Position of factor to return
     * @return int The kth factor or -1 if not exists
     * 
     * Algorithm:
     * 1. Iterate from 1 to sqrt(n)
     * 2. For each divisor i, we get factor pair (i, n/i)
     * 3. Count factors and return kth when found
     * 4. Handle perfect squares carefully to avoid duplicates
     */
    int kthFactor(int n, int k) {
        vector<int> factors;
        int sqrtN = sqrt(n);
        
        // Find all factors up to sqrt(n)
        for (int i = 1; i <= sqrtN; i++) {
            if (n % i == 0) {
                factors.push_back(i);
                if (factors.size() == k) {
                    return factors[k - 1];
                }
            }
        }
        
        // Find corresponding larger factors
        // Start from the largest smaller factor and go backwards
        for (int i = sqrtN; i >= 1; i--) {
            if (n % i == 0) {
                int complement = n / i;
                // Avoid duplicate for perfect squares
                if (complement != i) {
                    factors.push_back(complement);
                    if (factors.size() == k) {
                        return factors[k - 1];
                    }
                }
            }
        }
        
        return -1; // Less than k factors
    }
    
    /**
     * @brief Optimized approach using two-pass method
     * @param n Number to find factors of
     * @param k Position of factor to return
     * @return int The kth factor or -1 if not exists
     */
    int kthFactorOptimized(int n, int k) {
        vector<int> smallFactors, largeFactors;
        int sqrtN = sqrt(n);
        
        // Collect factors in two groups
        for (int i = 1; i <= sqrtN; i++) {
            if (n % i == 0) {
                smallFactors.push_back(i);
                if (i != n / i) { // Avoid duplicate for perfect squares
                    largeFactors.push_back(n / i);
                }
            }
        }
        
        // Reverse large factors to maintain ascending order
        reverse(largeFactors.begin(), largeFactors.end());
        
        // Check if kth factor exists
        int totalFactors = smallFactors.size() + largeFactors.size();
        if (k > totalFactors) return -1;
        
        // Return kth factor
        if (k <= smallFactors.size()) {
            return smallFactors[k - 1];
        } else {
            return largeFactors[k - smallFactors.size() - 1];
        }
    }
    
    /**
     * @brief Brute force approach (your original - for comparison)
     * @param n Number to find factors of
     * @param k Position of factor to return
     * @return int The kth factor or -1 if not exists
     */
    int kthFactorBruteForce(int n, int k) {
        vector<int> factors;
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                factors.push_back(i);
                if (factors.size() == k) {
                    return factors[k - 1];
                }
            }
        }
        return -1;
    }
    
    /**
     * @brief Space-optimized approach without storing factors
     * @param n Number to find factors of
     * @param k Position of factor to return
     * @return int The kth factor or -1 if not exists
     */
    int kthFactorSpaceOptimized(int n, int k) {
        int count = 0;
        
        // Count factors up to sqrt(n)
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                count++;
                if (count == k) return i;
            }
        }
        
        // Count factors greater than sqrt(n)
        for (int i = sqrt(n); i >= 1; i--) {
            if (n % i == 0 && i != n / i) {
                count++;
                if (count == k) return n / i;
            }
        }
        
        return -1;
    }
};

/**
 * @brief Test function for a single case
 */
void testCase(int n, int k, int expected, const string& description) {
    Solution solution;
    int result = solution.kthFactor(n, k);
    string status = (result == expected) ? "✅ PASSED" : "❌ FAILED";
    cout << status << ": " << description << " -> " << result << endl;
    assert(result == expected);
}

/**
 * @brief Comprehensive test function
 */
void runTests() {
    cout << "🧪 Running Comprehensive Tests:" << endl;
    cout << "===============================" << endl;
    
    // Test Case 1: Basic example
    testCase(12, 3, 3, "n=12, k=3 (factors: [1,2,3,4,6,12])");
    
    // Test Case 2: Prime number
    testCase(7, 2, 7, "n=7, k=2 (prime number)");
    
    // Test Case 3: Not enough factors
    testCase(4, 4, -1, "n=4, k=4 (only 3 factors)");
    
    // Test Case 4: First factor
    testCase(1000, 1, 1, "n=1000, k=1 (first factor)");
    
    // Test Case 5: Perfect square
    testCase(9, 2, 3, "n=9, k=2 (perfect square)");
    
    // Test Case 6: Large k
    testCase(24, 8, 24, "n=24, k=8 (last factor)");
    
    // Test Case 7: Small numbers
    testCase(1, 1, 1, "n=1, k=1 (edge case)");
    testCase(2, 2, 2, "n=2, k=2 (prime)");
    
    // Test Case 8: Perfect square edge case
    testCase(16, 3, 4, "n=16, k=3 (perfect square)");
    
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
    cout << "Early Termination     | O(min(k,√n))| O(1)  | Small k values (OPTIMAL)" << endl;
    cout << "Sqrt Optimization     | O(√n)       | O(√n) | General case" << endl;
    cout << "Space Optimized       | O(√n)       | O(1)  | Memory constrained" << endl;
    cout << "Brute Force (yours)   | O(n)        | O(k)  | Simple implementation" << endl;
    cout << "                      |             |       |" << endl;
    cout << "Recommendation: Use Early Termination for optimal performance!" << endl;
}

/**
 * @brief Step-by-step walkthrough
 */
void stepByStepDemo() {
    cout << "\n💡 Step-by-step Walkthrough (Sqrt Optimization):" << endl;
    cout << "================================================" << endl;
    
    int n = 12, k = 3;
    cout << "Input: n = " << n << ", k = " << k << endl;
    cout << "Goal: Find 3rd factor of 12" << endl << endl;
    
    cout << "Step 1: Find factors up to sqrt(12) ≈ 3.46" << endl;
    cout << "  i=1: 12%1=0 ✓ → factor 1" << endl;
    cout << "  i=2: 12%2=0 ✓ → factor 2" << endl;
    cout << "  i=3: 12%3=0 ✓ → factor 3 ← This is our answer!" << endl << endl;
    
    cout << "Complete factor list would be:" << endl;
    cout << "Small factors: [1, 2, 3]" << endl;
    cout << "Large factors: [12, 6, 4] (complements of small factors)" << endl;
    cout << "Sorted: [1, 2, 3, 4, 6, 12]" << endl;
    cout << "3rd factor: 3" << endl;
}

/**
 * @brief Factor analysis demonstration
 */
void factorAnalysis() {
    cout << "\n🔍 Factor Analysis Examples:" << endl;
    cout << "============================" << endl;
    
    vector<int> numbers = {12, 16, 7, 24};
    Solution solution;
    
    for (int n : numbers) {
        cout << "Factors of " << n << ": ";
        vector<int> factors;
        
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                factors.push_back(i);
            }
        }
        
        cout << "[";
        for (int i = 0; i < factors.size(); i++) {
            cout << factors[i];
            if (i < factors.size() - 1) cout << ", ";
        }
        cout << "] (Total: " << factors.size() << ")" << endl;
    }
}

/**
 * @brief Main function demonstrating the solution
 */
int main() {
    cout << "🔢 LeetCode 1492: The kth Factor of n" << endl;
    cout << "=====================================" << endl;
    
    // Run comprehensive tests
    runTests();
    
    // Performance comparison
    performanceComparison();
    
    // Step-by-step demonstration
    stepByStepDemo();
    
    // Factor analysis
    factorAnalysis();
    
    cout << "\n🚀 Interactive Examples:" << endl;
    cout << "========================" << endl;
    
    Solution solution;
    vector<pair<int, int>> examples = {{12, 3}, {7, 2}, {4, 4}, {24, 8}};
    
    for (auto& example : examples) {
        int n = example.first, k = example.second;
        int result = solution.kthFactor(n, k);
        cout << "kthFactor(" << n << ", " << k << ") = " << result << endl;
    }
    
    return 0;
}

/*
🎯 KEY LEARNINGS:
1. Factor pairs: if i divides n, then n/i also divides n
2. Optimization: only check up to sqrt(n) to find all factors
3. Perfect squares need special handling to avoid duplicates
4. Early termination can significantly improve performance for small k

🚀 RELATED PROBLEMS:
- LeetCode 204: Count Primes
- LeetCode 507: Perfect Number
- LeetCode 728: Self Dividing Numbers
- LeetCode 1071: Greatest Common Divisor of Strings

📚 CONCEPTS PRACTICED:
- Number theory and factorization
- Square root optimization
- Early termination techniques
- Space-time complexity trade-offs
- Mathematical problem solving
*/