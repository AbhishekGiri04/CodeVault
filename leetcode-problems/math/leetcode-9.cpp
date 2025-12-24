/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 9                                                            ║
║ Problem Name  : Palindrome Number                                           ║
║ Difficulty    : Easy                                                         ║
║ Topic         : Math, Number Manipulation                                   ║
║ Company Tags  : Amazon, Apple, Microsoft, Google, Facebook                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given an integer x, return true if x is a palindrome, and false otherwise.
A palindrome number reads the same backward as forward.

📝 EXAMPLES:
Input:  x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Input:  x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-.

Input:  x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

🎯 CONSTRAINTS:
- -2^31 <= x <= 2^31 - 1

💡 APPROACH:
Half reversal approach - reverse only half digits
1. Handle negative numbers (always false)
2. Handle numbers ending with 0 (except 0)
3. Reverse only half the digits
4. Compare original half with reversed half

⏰ TIME COMPLEXITY:  O(log n) - Process each digit once
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
using namespace std;

bool isPalindrome(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;
    
    int reversed = 0;
    while (x > reversed) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }
    
    return x == reversed || x == reversed / 10;
}

int main() {
    int x = 121;
    bool result = isPalindrome(x);
    cout << (result ? "true" : "false") << endl;
    return 0;
}