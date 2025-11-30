/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 29                                                           ║
║ Problem Name  : Divide Two Integers                                         ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Math, Bit Manipulation                                      ║
║ Company Tags  : Amazon, Microsoft, Google, Facebook, Apple                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given two integers dividend and divisor, divide two integers without using 
multiplication, division, and mod operator. The integer division should truncate 
toward zero. Return the quotient after dividing dividend by divisor.

📝 EXAMPLES:
Input:  dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.

Input:  dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.

🎯 CONSTRAINTS:
- -2^31 <= dividend, divisor <= 2^31 - 1
- divisor != 0
- Assume 32-bit signed integer range: [-2^31, 2^31 - 1]

💡 APPROACHES:
1. Repeated Subtraction: Keep subtracting divisor - O(dividend/divisor) time
2. Bit Manipulation: Use bit shifts for faster division - O(log n) time (OPTIMAL)
3. Binary Search: Search for quotient in range - O(log n) time

⏰ OPTIMAL SOLUTION: Bit manipulation with exponential search
💾 TIME COMPLEXITY:  O(log n) - Logarithmic in dividend value
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

class Solution {
public:
    /**
     * @brief Divides two integers using bit manipulation (OPTIMAL)
     * @param dividend Number to be divided
     * @param divisor Number to divide by
     * @return int Quotient with overflow handling
     * 
     * Algorithm:
     * 1. Handle edge cases and overflow conditions
     * 2. Determine result sign and work with absolute values
     * 3. Use bit shifts to find largest multiple of divisor ≤ dividend
     * 4. Subtract and repeat until dividend < divisor
     */
    int divide(int dividend, int divisor) {
        // Handle overflow cases
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX; // Overflow case
        }
        if (dividend == INT_MIN && divisor == 1) {
            return INT_MIN; // No overflow
        }
        
        // Determine sign of result
        bool negative = (dividend < 0) ^ (divisor < 0);
        
        // Work with absolute values using long long to prevent overflow
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);
        long long result = 0;
        
        // Use bit manipulation for efficient division
        while (a >= b) {
            long long temp = b;
            long long multiple = 1;
            
            // Find the largest multiple of divisor that fits in dividend
            while (a >= (temp << 1)) {
                temp <<= 1;      // temp *= 2
                multiple <<= 1;  // multiple *= 2
            }
            
            a -= temp;
            result += multiple;
        }
        
        // Apply sign
        if (negative) result = -result;
        
        // Handle overflow
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        
        return (int)result;
    }
    
    /**
     * @brief Binary search approach (for comparison)
     * @param dividend Number to be divided
     * @param divisor Number to divide by
     * @return int Quotient with overflow handling
     */
    int divideBinarySearch(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
        
        bool negative = (dividend < 0) ^ (divisor < 0);
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);
        
        long long left = 0, right = a;
        long long result = 0;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            
            if (mid * b <= a) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (negative) result = -result;
        
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        
        return (int)result;
    }
    
    /**
     * @brief Repeated subtraction approach (for comparison)
     * @param dividend Number to be divided
     * @param divisor Number to divide by
     * @return int Quotient with overflow handling
     */
    int divideSubtraction(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
        
        bool negative = (dividend < 0) ^ (divisor < 0);
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);
        
        long long result = 0;
        
        while (a >= b) {
            a -= b;
            result++;
        }
        
        if (negative) result = -result;
        
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        
        return (int)result;
    }
    
    /**
     * @brief Optimized bit manipulation with early termination
     * @param dividend Number to be divided
     * @param divisor Number to divide by
     * @return int Quotient with overflow handling
     */
    int divideOptimized(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
        
        bool negative = (dividend < 0) ^ (divisor < 0);
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);
        
        if (a < b) return 0; // Early termination
        
        long long result = 0;
        
        // Start from the highest bit position
        for (int i = 31; i >= 0; i--) {
            if ((b << i) <= a) {
                a -= (b << i);
                result += (1LL << i);
            }
        }
        
        if (negative) result = -result;
        
        return (int)min(max(result, (long long)INT_MIN), (long long)INT_MAX);
    }
};

/**
 * @brief Test function for a single case
 */
void testCase(int dividend, int divisor, int expected, const string& description) {
    Solution solution;
    int result = solution.divide(dividend, divisor);
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
    
    // Test Case 1: Basic division
    testCase(10, 3, 3, "dividend=10, divisor=3");
    
    // Test Case 2: Negative result
    testCase(7, -3, -2, "dividend=7, divisor=-3");
    
    // Test Case 3: Overflow case
    testCase(INT_MIN, -1, INT_MAX, "dividend=INT_MIN, divisor=-1 (overflow)");
    
    // Test Case 4: No overflow case
    testCase(INT_MIN, 1, INT_MIN, "dividend=INT_MIN, divisor=1 (no overflow)");
    
    // Test Case 5: Zero result
    testCase(1, 2, 0, "dividend=1, divisor=2 (result=0)");
    
    // Test Case 6: Same numbers
    testCase(5, 5, 1, "dividend=5, divisor=5 (result=1)");
    
    // Test Case 7: Large numbers
    testCase(2147483647, 2, 1073741823, "dividend=INT_MAX, divisor=2");
    
    // Test Case 8: Negative dividend
    testCase(-10, 3, -3, "dividend=-10, divisor=3");
    
    // Test Case 9: Both negative
    testCase(-10, -3, 3, "dividend=-10, divisor=-3");
    
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
    cout << "Bit Manipulation      | O(log n)    | O(1)  | General case (OPTIMAL)" << endl;
    cout << "Binary Search         | O(log n)    | O(1)  | Alternative approach" << endl;
    cout << "Optimized Bits        | O(log n)    | O(1)  | Constant factor optimization" << endl;
    cout << "Repeated Subtraction  | O(n/m)      | O(1)  | Simple but slow" << endl;
    cout << "                      |             |       |" << endl;
    cout << "Recommendation: Use Bit Manipulation for optimal performance!" << endl;
}

/**
 * @brief Step-by-step walkthrough
 */
void stepByStepDemo() {
    cout << "\n💡 Step-by-step Walkthrough (Bit Manipulation):" << endl;
    cout << "===============================================" << endl;
    
    int dividend = 10, divisor = 3;
    cout << "Input: dividend = " << dividend << ", divisor = " << divisor << endl;
    cout << "Goal: Find 10 ÷ 3 without using /, *, % operators" << endl << endl;
    
    cout << "Step 1: Handle signs and edge cases" << endl;
    cout << "  Both positive, no overflow" << endl << endl;
    
    cout << "Step 2: Find largest multiple of 3 ≤ 10" << endl;
    cout << "  3 × 1 = 3 ≤ 10 ✓" << endl;
    cout << "  3 × 2 = 6 ≤ 10 ✓" << endl;
    cout << "  3 × 4 = 12 > 10 ✗" << endl;
    cout << "  Largest multiple: 3 × 2 = 6" << endl << endl;
    
    cout << "Step 3: Subtract and add to result" << endl;
    cout << "  10 - 6 = 4, result = 2" << endl << endl;
    
    cout << "Step 4: Repeat with remainder" << endl;
    cout << "  4 ≥ 3, so 4 - 3 = 1, result = 2 + 1 = 3" << endl;
    cout << "  1 < 3, stop" << endl << endl;
    
    cout << "Final result: 3" << endl;
}

/**
 * @brief Bit manipulation explanation
 */
void bitManipulationExplanation() {
    cout << "\n🔢 Bit Manipulation Technique:" << endl;
    cout << "==============================" << endl;
    
    cout << "Key Insight: Division is finding how many times divisor fits in dividend" << endl;
    cout << "Instead of subtracting divisor one by one, we use powers of 2:" << endl << endl;
    
    cout << "Example: 100 ÷ 3" << endl;
    cout << "Step 1: 3 × 32 = 96 ≤ 100, subtract 96, result += 32" << endl;
    cout << "Step 2: 4 ÷ 3 → 3 × 1 = 3 ≤ 4, subtract 3, result += 1" << endl;
    cout << "Final: result = 32 + 1 = 33" << endl << endl;
    
    cout << "Bit shifts used:" << endl;
    cout << "temp <<= 1  ≡  temp *= 2" << endl;
    cout << "multiple <<= 1  ≡  multiple *= 2" << endl;
    cout << "This gives us exponential growth: 1, 2, 4, 8, 16, 32, ..." << endl;
}

/**
 * @brief Main function demonstrating the solution
 */
int main() {
    cout << "➗ LeetCode 29: Divide Two Integers" << endl;
    cout << "===================================" << endl;
    
    // Run comprehensive tests
    runTests();
    
    // Performance comparison
    performanceComparison();
    
    // Step-by-step demonstration
    stepByStepDemo();
    
    // Bit manipulation explanation
    bitManipulationExplanation();
    
    cout << "\n🚀 Interactive Examples:" << endl;
    cout << "========================" << endl;
    
    Solution solution;
    vector<pair<int, int>> examples = {{10, 3}, {7, -3}, {-10, -3}, {1, 2}, {INT_MIN, -1}};
    
    for (auto& example : examples) {
        int dividend = example.first, divisor = example.second;
        int result = solution.divide(dividend, divisor);
        cout << "divide(" << dividend << ", " << divisor << ") = " << result << endl;
    }
    
    return 0;
}

/*
🎯 KEY LEARNINGS:
1. Bit manipulation can replace multiplication/division operations
2. Handle integer overflow carefully with long long
3. Use exponential search (powers of 2) for efficiency
4. Always consider edge cases like INT_MIN and division by -1

🚀 RELATED PROBLEMS:
- LeetCode 50: Pow(x, n)
- LeetCode 69: Sqrt(x)
- LeetCode 367: Valid Perfect Square
- LeetCode 441: Arranging Coins

📚 CONCEPTS PRACTICED:
- Bit manipulation and bit shifts
- Integer overflow handling
- Mathematical optimization techniques
- Binary search applications
- Edge case analysis
*/