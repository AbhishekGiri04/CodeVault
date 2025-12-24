/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                           ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 1492                                                         ║
║ Problem Name  : The kth Factor of n                                          ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Math, Number Theory                                          ║
║ Company Tags  : Amazon, Microsoft, Google, Facebook                          ║
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

💡 APPROACH:
Early termination with sqrt optimization
1. Iterate from 1 to sqrt(n)
2. For each divisor i, we get factor pair (i, n/i)
3. Count factors and return kth when found
4. Handle perfect squares carefully to avoid duplicates

⏰ TIME COMPLEXITY:  O(min(k, √n)) - Stop early when possible
💾 SPACE COMPLEXITY: O(1) - Only using variables
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int kthFactor(int n, int k) {
    vector<int> factors;
    int sqrtN = sqrt(n);
    
    for (int i = 1; i <= sqrtN; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            if (factors.size() == k) {
                return factors[k - 1];
            }
        }
    }
    
    for (int i = sqrtN; i >= 1; i--) {
        if (n % i == 0) {
            int complement = n / i;
            if (complement != i) {
                factors.push_back(complement);
                if (factors.size() == k) {
                    return factors[k - 1];
                }
            }
        }
    }
    
    return -1;
}

int main() {
    int n = 12, k = 3;
    int result = kthFactor(n, k);
    cout << result << endl;
    return 0;
}
