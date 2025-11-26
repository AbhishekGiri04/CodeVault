/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 7                                                            ║
║ Problem Name  : Reverse Integer                                             ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Math, Integer Manipulation                                  ║
║ Company Tags  : Amazon, Apple, Microsoft, Google, Facebook                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given a signed 32-bit integer x, return x with its digits reversed. If reversing x 
causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], 
then return 0. Assume the environment does not allow you to store 64-bit integers.

📝 EXAMPLES:
Input:  x = 123
Output: 321

Input:  x = -123
Output: -321

Input:  x = 120
Output: 21

🎯 CONSTRAINTS:
- -2^31 <= x <= 2^31 - 1

💡 APPROACHES:
1. String Reversal: Convert to string and reverse - O(log n) time, O(log n) space
2. Mathematical Reversal: Extract digits and build reverse - O(log n) time, O(1) space
3. Overflow Check: Handle 32-bit integer overflow carefully - O(log n) time, O(1) space (OPTIMAL)

⏰ OPTIMAL SOLUTION: Mathematical reversal with overflow detection
💾 TIME COMPLEXITY:  O(log n) - Process each digit once
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <climits>
using namespace std;

class Solution {
public:
    /**
     * @brief Reverses integer with overflow detection (OPTIMAL)
     * @param x Input integer to reverse
     * @return int Reversed integer or 0 if overflow
     * 
     * Algorithm:
     * 1. Handle edge cases (0, INT_MIN)
     * 2. Extract digits using modulo and division
     * 3. Check for overflow before multiplying by 10
     * 4. Build reversed number digit by digit
     */
    int reverse(int x) {
        int result = 0;
        
        while (x != 0) {
            int digit = x % 10;
            x /= 10;
            
            // Check for overflow before multiplying by 10
            // INT_MAX = 2147483647, so INT_MAX/10 = 214748364
            // INT_MIN = -2147483648, so INT_MIN/10 = -214748364
            if (result > INT_MAX / 10 || 
                (result == INT_MAX / 10 && digit > 7)) {
                return 0; // Positive overflow
            }
            if (result < INT_MIN / 10 || 
                (result == INT_MIN / 10 && digit < -8)) {
                return 0; // Negative overflow
            }
            
            result = result * 10 + digit;
        }
        
        return result;
    }
    
    /**
     * @brief Alternative approach with sign handling (for comparison)
     * @param x Input integer to reverse
     * @return int Reversed integer or 0 if overflow
     */
    int reverseWithSignHandling(int x) {
        // Handle special case of INT_MIN
        if (x == INT_MIN) return 0;
        
        // Handle zero
        if (x == 0) return 0;
        
        // Determine sign and work with absolute value
        int sign = (x > 0) ? 1 : -1;
        x = abs(x);
        
        int result = 0;
        while (x != 0) {
            int digit = x % 10;
            
            // Check overflow for positive numbers
            if (result > INT_MAX / 10 || 
                (result == INT_MAX / 10 && digit > 7)) {
                return 0;
            }
            
            result = result * 10 + digit;
            x /= 10;
        }
        
        return sign * result;
    }
    
    /**
     * @brief String-based approach (for comparison)
     * @param x Input integer to reverse
     * @return int Reversed integer or 0 if overflow
     */
    int reverseUsingString(int x) {
        string s = to_string(x);
        bool isNegative = (s[0] == '-');
        
        if (isNegative) {
            s = s.substr(1); // Remove negative sign
        }
        
        reverse(s.begin(), s.end());
        
        // Remove leading zeros
        size_t firstNonZero = s.find_first_not_of('0');
        if (firstNonZero == string::npos) return 0;
        s = s.substr(firstNonZero);
        
        // Check if result fits in 32-bit integer
        if (s.length() > 10) return 0;
        if (s.length() == 10) {
            string maxInt = "2147483647";
            string minInt = "2147483648";
            if (!isNegative && s > maxInt) return 0;
            if (isNegative && s > minInt) return 0;
        }
        
        long long result = stoll(s);
        return isNegative ? -result : result;
    }
    
    /**
     * @brief Long long approach (violates constraint but for understanding)
     * @param x Input integer to reverse
     * @return int Reversed integer or 0 if overflow
     */
    int reverseUsingLongLong(int x) {
        long long result = 0;
        
        while (x != 0) {
            result = result * 10 + x % 10;
            x /= 10;
        }
        
        // Check if result is within 32-bit range
        if (result > INT_MAX || result < INT_MIN) {
            return 0;
        }
        
        return (int)result;
    }
};

/**
 * @brief Test function for a single case
 */
void testCase(int x, int expected, const string& description) {
    Solution solution;
    int result = solution.reverse(x);
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
    
    // Test Case 1: Positive number
    testCase(123, 321, "x = 123 (positive number)");
    
    // Test Case 2: Negative number
    testCase(-123, -321, "x = -123 (negative number)");
    
    // Test Case 3: Number with trailing zeros
    testCase(120, 21, "x = 120 (trailing zeros)");
    
    // Test Case 4: Zero
    testCase(0, 0, "x = 0 (zero)");
    
    // Test Case 5: Single digit positive
    testCase(7, 7, "x = 7 (single digit positive)");
    
    // Test Case 6: Single digit negative
    testCase(-7, -7, "x = -7 (single digit negative)");
    
    // Test Case 7: Overflow case (positive)
    testCase(1534236469, 0, "x = 1534236469 (overflow)");
    
    // Test Case 8: Overflow case (negative)
    testCase(-2147483648, 0, "x = INT_MIN (overflow)");
    
    // Test Case 9: Edge case near overflow
    testCase(1463847412, 2147483641, "x = 1463847412 (near overflow)");
    
    cout << "\n🎉 All tests passed!" << endl;
}

/**
 * @brief Performance comparison demonstration
 */
void performanceComparison() {
    cout << "\n📊 Performance Comparison:" << endl;
    cout << "=========================" << endl;
    cout << "Approach              | Time     | Space | Constraint Compliance" << endl;
    cout << "----------------------|----------|-------|----------------------" << endl;
    cout << "Math with Overflow    | O(log n) | O(1)  | ✅ Compliant (OPTIMAL)" << endl;
    cout << "Sign Handling         | O(log n) | O(1)  | ✅ Compliant" << endl;
    cout << "String Reversal       | O(log n) | O(log n) | ✅ Compliant" << endl;
    cout << "Long Long (violates)  | O(log n) | O(1)  | ❌ Uses 64-bit" << endl;
    cout << "                      |          |       |" << endl;
    cout << "Recommendation: Use Math with Overflow Detection!" << endl;
}

/**
 * @brief Step-by-step walkthrough
 */
void stepByStepDemo() {
    cout << "\n💡 Step-by-step Walkthrough (Overflow Detection):" << endl;
    cout << "=================================================" << endl;
    
    int x = -123;
    cout << "Input: x = " << x << endl;
    cout << "Goal: Reverse digits while checking overflow" << endl << endl;
    
    cout << "Step 1: x = -123, result = 0" << endl;
    cout << "  digit = -123 % 10 = -3" << endl;
    cout << "  x = -123 / 10 = -12" << endl;
    cout << "  result = 0 * 10 + (-3) = -3" << endl << endl;
    
    cout << "Step 2: x = -12, result = -3" << endl;
    cout << "  digit = -12 % 10 = -2" << endl;
    cout << "  x = -12 / 10 = -1" << endl;
    cout << "  result = -3 * 10 + (-2) = -32" << endl << endl;
    
    cout << "Step 3: x = -1, result = -32" << endl;
    cout << "  digit = -1 % 10 = -1" << endl;
    cout << "  x = -1 / 10 = 0" << endl;
    cout << "  result = -32 * 10 + (-1) = -321" << endl << endl;
    
    cout << "Final: x = 0, loop ends" << endl;
    cout << "Result: -321" << endl;
}

/**
 * @brief Overflow detection explanation
 */
void overflowExplanation() {
    cout << "\n🚨 Overflow Detection Logic:" << endl;
    cout << "============================" << endl;
    
    cout << "32-bit Integer Limits:" << endl;
    cout << "INT_MAX = 2,147,483,647" << endl;
    cout << "INT_MIN = -2,147,483,648" << endl << endl;
    
    cout << "Overflow Check Before Multiplication:" << endl;
    cout << "if (result > INT_MAX/10) → Definitely overflow" << endl;
    cout << "if (result == INT_MAX/10 && digit > 7) → Overflow" << endl;
    cout << "if (result < INT_MIN/10) → Definitely underflow" << endl;
    cout << "if (result == INT_MIN/10 && digit < -8) → Underflow" << endl << endl;
    
    cout << "Why check before multiplication?" << endl;
    cout << "Because result * 10 might already overflow!" << endl;
}

/**
 * @brief Main function demonstrating the solution
 */
int main() {
    cout << "🔄 LeetCode 7: Reverse Integer" << endl;
    cout << "==============================" << endl;
    
    // Run comprehensive tests
    runTests();
    
    // Performance comparison
    performanceComparison();
    
    // Step-by-step demonstration
    stepByStepDemo();
    
    // Overflow explanation
    overflowExplanation();
    
    cout << "\n🚀 Interactive Examples:" << endl;
    cout << "========================" << endl;
    
    Solution solution;
    vector<int> examples = {123, -123, 120, 0, 1534236469, -2147483648};
    
    for (int x : examples) {
        int result = solution.reverse(x);
        cout << "reverse(" << x << ") = " << result << endl;
    }
    
    return 0;
}

/*
🎯 KEY LEARNINGS:
1. Always check for overflow before performing operations
2. Use INT_MAX/10 and INT_MIN/10 for overflow detection
3. Handle negative numbers correctly with modulo operation
4. Mathematical approach is more efficient than string conversion

🚀 RELATED PROBLEMS:
- LeetCode 9: Palindrome Number
- LeetCode 8: String to Integer (atoi)
- LeetCode 190: Reverse Bits
- LeetCode 191: Number of 1 Bits

📚 CONCEPTS PRACTICED:
- Integer overflow detection
- Mathematical digit manipulation
- Edge case handling
- 32-bit integer constraints
- Multiple solution approaches comparison
*/