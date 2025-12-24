/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 202                                                          ║
║ Problem Name  : Happy Number                                                ║
║ Difficulty    : Easy                                                         ║
║ Topic         : Hash Table, Math, Two Pointers                             ║
║ Company Tags  : Amazon, Apple, Google, Microsoft, Facebook                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Write an algorithm to determine if a number n is happy. A happy number is a number 
defined by the following process: Starting with any positive integer, replace the 
number by the sum of the squares of its digits. Repeat the process until the number 
equals 1 (where it will stay), or it loops endlessly in a cycle which does not 
include 1. Those numbers for which this process ends in 1 are happy.

📝 EXAMPLES:
Input:  n = 19
Output: true
Explanation:
1² + 9² = 82
8² + 2² = 68  
6² + 8² = 100
1² + 0² + 0² = 1

Input:  n = 2
Output: false

🎯 CONSTRAINTS:
- 1 <= n <= 2^31 - 1

💡 APPROACH:
Floyd's Cycle Detection (Tortoise and Hare)
1. Use two pointers: slow (one step) and fast (two steps)
2. If they meet and it's not 1, there's a cycle (not happy)
3. If we reach 1, it's a happy number

⏰ TIME COMPLEXITY:  O(log n) - Limited by digit processing
💾 SPACE COMPLEXITY: O(1) - Only using two pointers
*/

#include <iostream>
using namespace std;

int getSumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow = n, fast = n;
    
    do {
        slow = getSumOfSquares(slow);
        fast = getSumOfSquares(getSumOfSquares(fast));
    } while (slow != fast);
    
    return slow == 1;
}

int main() {
    int n = 19;
    bool result = isHappy(n);
    cout << (result ? "true" : "false") << endl;
    return 0;
}