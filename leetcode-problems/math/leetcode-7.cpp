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

💡 APPROACH:
Mathematical reversal with overflow detection
1. Extract digits using modulo and division
2. Check for overflow before multiplying by 10
3. Build reversed number digit by digit

⏰ TIME COMPLEXITY:  O(log n) - Process each digit once
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
#include <climits>
using namespace std;

int reverse(int x) {
    int result = 0;
    
    while (x != 0) {
        int digit = x % 10;
        x /= 10;
        
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7)) {
            return 0;
        }
        if (result < INT_MIN / 10 || (result == INT_MIN / 10 && digit < -8)) {
            return 0;
        }
        
        result = result * 10 + digit;
    }
    
    return result;
}

int main() {
    int x = 123;
    int result = reverse(x);
    cout << result << endl;
    return 0;
}