/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 344                                                          ║
║ Problem Name  : Reverse String                                              ║
║ Difficulty    : Easy                                                         ║
║ Topic         : Two Pointers, String, Array                                 ║
║ Company Tags  : Apple, Amazon, Microsoft, Google                            ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Write a function that reverses a string. The input string is given as an array of characters s.
You must do this by modifying the input array in-place with O(1) extra memory.

📝 EXAMPLES:
Input:  s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Input:  s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]

🎯 CONSTRAINTS:
- 1 <= s.length <= 10^5
- s[i] is a printable ascii character

💡 APPROACH:
Two-pointer technique:
1. Place one pointer at start (left) and one at end (right)
2. Swap characters at these positions
3. Move pointers towards center until they meet

⏰ TIME COMPLEXITY:  O(n) - Visit each character once
💾 SPACE COMPLEXITY: O(1) - Only using two pointer variables
*/

#include <iostream>
#include <vector>
using namespace std;

void reverseString(vector<char>& s) {
    int left = 0, right = s.size() - 1;
    
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}

int main() {
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    reverseString(s);
    cout << "[";
    for (int i = 0; i < s.size(); i++) {
        cout << "\"" << s[i] << "\"";
        if (i < s.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    return 0;
}