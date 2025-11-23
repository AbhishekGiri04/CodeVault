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
We'll use the two-pointer technique:
1. Place one pointer at start (left) and one at end (right)
2. Swap characters at these positions
3. Move pointers towards center until they meet

⏰ TIME COMPLEXITY:  O(n) - Visit each character once
💾 SPACE COMPLEXITY: O(1) - Only using two pointer variables
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>
using namespace std;

class Solution {
public:
    /**
     * @brief Reverses string in-place using two-pointer technique (OPTIMAL)
     * @param s Reference to character vector to be reversed
     * 
     * Algorithm:
     * 1. Initialize left pointer at start (0) and right at end (n-1)
     * 2. Swap characters at left and right positions
     * 3. Move left forward and right backward
     * 4. Continue until pointers meet in middle
     */
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        
        // Two-pointer approach: swap from outside to inside
        while (left < right) {
            // Swap characters at left and right positions
            swap(s[left], s[right]);
            
            // Move pointers towards center
            left++;
            right--;
        }
    }
    
    /**
     * @brief Alternative approach using stack (NOT OPTIMAL - for learning)
     * @param s Reference to character vector to be reversed
     * 
     * Note: This uses O(n) extra space, violating the constraint
     * Included for educational purposes to show different approaches
     */
    void reverseStringUsingStack(vector<char>& s) {
        stack<char> st;
        
        // Push all characters onto stack (LIFO structure)
        for (char ch : s) {
            st.push(ch);
        }
        
        // Pop from stack and overwrite original array
        for (int i = 0; i < s.size(); i++) {
            s[i] = st.top();
            st.pop();
        }
    }
    
    /**
     * @brief Using STL reverse function (one-liner solution)
     * @param s Reference to character vector to be reversed
     */
    void reverseStringSTL(vector<char>& s) {
        reverse(s.begin(), s.end());
    }
    
    /**
     * @brief Recursive approach (for educational purposes)
     * @param s Reference to character vector
     * @param left Left boundary index
     * @param right Right boundary index
     */
    void reverseStringRecursive(vector<char>& s, int left = 0, int right = -1) {
        // Initialize right on first call
        if (right == -1) right = s.size() - 1;
        
        // Base case: pointers meet or cross
        if (left >= right) return;
        
        // Swap current positions
        swap(s[left], s[right]);
        
        // Recursive call with updated boundaries
        reverseStringRecursive(s, left + 1, right - 1);
    }
};

/**
 * @brief Utility function to print character vector
 */
void printCharVector(const vector<char>& s, const string& label) {
    cout << label << ": [";
    for (int i = 0; i < s.size(); i++) {
        cout << "\"" << s[i] << "\"";
        if (i < s.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

/**
 * @brief Utility function to convert string to char vector
 */
vector<char> stringToCharVector(const string& str) {
    return vector<char>(str.begin(), str.end());
}

/**
 * @brief Comprehensive test function
 */
void runTests() {
    Solution solution;
    
    // Test Case 1: Basic example "hello"
    vector<char> test1 = {'h', 'e', 'l', 'l', 'o'};
    vector<char> expected1 = {'o', 'l', 'l', 'e', 'h'};
    solution.reverseString(test1);
    assert(test1 == expected1);
    cout << "✅ Test 1 Passed: \"hello\" -> \"olleh\"" << endl;
    
    // Test Case 2: Palindrome "Hannah"
    vector<char> test2 = {'H', 'a', 'n', 'n', 'a', 'h'};
    vector<char> expected2 = {'h', 'a', 'n', 'n', 'a', 'H'};
    solution.reverseString(test2);
    assert(test2 == expected2);
    cout << "✅ Test 2 Passed: \"Hannah\" -> \"hannaH\"" << endl;
    
    // Test Case 3: Single character
    vector<char> test3 = {'A'};
    vector<char> expected3 = {'A'};
    solution.reverseString(test3);
    assert(test3 == expected3);
    cout << "✅ Test 3 Passed: \"A\" -> \"A\"" << endl;
    
    // Test Case 4: Two characters
    vector<char> test4 = {'A', 'B'};
    vector<char> expected4 = {'B', 'A'};
    solution.reverseString(test4);
    assert(test4 == expected4);
    cout << "✅ Test 4 Passed: \"AB\" -> \"BA\"" << endl;
    
    // Test Case 5: Numbers and symbols
    vector<char> test5 = {'1', '2', '3', '!', '@'};
    vector<char> expected5 = {'@', '!', '3', '2', '1'};
    solution.reverseString(test5);
    assert(test5 == expected5);
    cout << "✅ Test 5 Passed: \"123!@\" -> \"@!321\"" << endl;
}

/**
 * @brief Demonstration of different approaches
 */
void demonstrateApproaches() {
    Solution solution;
    
    cout << "\n🔄 Comparing Different Approaches:" << endl;
    cout << "=================================" << endl;
    
    // Original string
    string original = "ALGORITHM";
    
    // Approach 1: Two Pointers (Optimal)
    vector<char> s1 = stringToCharVector(original);
    printCharVector(s1, "Original     ");
    solution.reverseString(s1);
    printCharVector(s1, "Two Pointers ");
    
    // Approach 2: Using Stack
    vector<char> s2 = stringToCharVector(original);
    solution.reverseStringUsingStack(s2);
    printCharVector(s2, "Using Stack  ");
    
    // Approach 3: STL Reverse
    vector<char> s3 = stringToCharVector(original);
    solution.reverseStringSTL(s3);
    printCharVector(s3, "STL Reverse  ");
    
    // Approach 4: Recursive
    vector<char> s4 = stringToCharVector(original);
    solution.reverseStringRecursive(s4);
    printCharVector(s4, "Recursive    ");
}

/**
 * @brief Performance analysis demonstration
 */
void performanceAnalysis() {
    cout << "\n📊 Performance Analysis:" << endl;
    cout << "========================" << endl;
    cout << "Approach        | Time | Space | In-place | Optimal" << endl;
    cout << "----------------|------|-------|----------|--------" << endl;
    cout << "Two Pointers    | O(n) | O(1)  |    ✅    |   ✅   " << endl;
    cout << "Stack           | O(n) | O(n)  |    ❌    |   ❌   " << endl;
    cout << "STL Reverse     | O(n) | O(1)  |    ✅    |   ✅   " << endl;
    cout << "Recursive       | O(n) | O(n)  |    ✅    |   ❌   " << endl;
    cout << "                |      |       |          |        " << endl;
    cout << "Note: Recursive uses O(n) space due to call stack" << endl;
}

/**
 * @brief Main function demonstrating the solution
 */
int main() {
    cout << "🔄 LeetCode 344: Reverse String" << endl;
    cout << "===============================" << endl;
    
    // Run comprehensive tests
    runTests();
    
    // Demonstrate different approaches
    demonstrateApproaches();
    
    // Show performance analysis
    performanceAnalysis();
    
    cout << "\n💡 Step-by-step Example (Two Pointers):" << endl;
    cout << "=======================================" << endl;
    
    vector<char> demo = {'C', 'O', 'D', 'E'};
    cout << "Initial: [C, O, D, E]" << endl;
    cout << "Step 1:  [E, O, D, C] (swap C↔E)" << endl;
    cout << "Step 2:  [E, D, O, C] (swap O↔D)" << endl;
    cout << "Final:   [E, D, O, C]" << endl;
    
    return 0;
}

/*
🎯 KEY LEARNINGS:
1. Two-pointer technique is optimal for in-place array reversal
2. Always consider space complexity constraints in problems
3. Multiple approaches exist - choose based on requirements
4. In-place algorithms are memory efficient

🚀 RELATED PROBLEMS:
- LeetCode 541: Reverse String II
- LeetCode 557: Reverse Words in a String III
- LeetCode 151: Reverse Words in a String
- LeetCode 186: Reverse Words in a String II

📚 CONCEPTS PRACTICED:
- Two-pointer technique
- In-place array manipulation
- String/character array operations
- Space-time complexity trade-offs
- Multiple solution approaches
*/