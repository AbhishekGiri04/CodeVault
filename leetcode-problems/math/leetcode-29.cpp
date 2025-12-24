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

💡 APPROACH:
Bit manipulation with exponential search
1. Handle edge cases and overflow conditions
2. Determine result sign and work with absolute values
3. Use bit shifts to find largest multiple of divisor ≤ dividend
4. Subtract and repeat until dividend < divisor

⏰ TIME COMPLEXITY:  O(log n) - Logarithmic in dividend value
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
#include <climits>
using namespace std;

int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;
    
    bool negative = (dividend < 0) ^ (divisor < 0);
    long long a = abs((long long)dividend);
    long long b = abs((long long)divisor);
    long long result = 0;
    
    while (a >= b) {
        long long temp = b, multiple = 1;
        while (a >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        a -= temp;
        result += multiple;
    }
    
    if (negative) result = -result;
    if (result > INT_MAX) return INT_MAX;
    if (result < INT_MIN) return INT_MIN;
    
    return (int)result;
}

int main() {
    int dividend = 10, divisor = 3;
    int result = divide(dividend, divisor);
    cout << result << endl;
    return 0;
}