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

💡 APPROACHES:
1. Hash Set Detection: Store seen numbers to detect cycles - O(log n) time, O(log n) space
2. Floyd's Cycle Detection: Two pointers to detect cycles - O(log n) time, O(1) space (OPTIMAL)
3. Mathematical Analysis: Known cycle patterns - O(log n) time, O(1) space

⏰ OPTIMAL SOLUTION: Floyd's Cycle Detection (Tortoise and Hare)
💾 TIME COMPLEXITY:  O(log n) - Limited by digit processing
💾 SPACE COMPLEXITY: O(1) - Only using two pointers
*/

#include <iostream>
#include <unordered_set>
#include <cassert>
using namespace std;

class Solution {
public:
    /**
     * @brief Determines if number is happy using Floyd's cycle detection (OPTIMAL)
     * @param n Input positive integer
     * @return bool True if happy number, false otherwise
     * 
     * Algorithm:
     * 1. Use two pointers: slow (one step) and fast (two steps)
     * 2. If they meet and it's not 1, there's a cycle (not happy)
     * 3. If we reach 1, it's a happy number
     */
    bool isHappy(int n) {
        int slow = n;
        int fast = n;
        
        do {
            slow = getSumOfSquares(slow);           // Move one step
            fast = getSumOfSquares(getSumOfSquares(fast)); // Move two steps
        } while (slow != fast);
        
        return slow == 1; // If they meet at 1, it's happy
    }
    
    /**
     * @brief Hash set approach for cycle detection (for comparison)
     * @param n Input positive integer
     * @return bool True if happy number, false otherwise
     */
    bool isHappyHashSet(int n) {
        unordered_set<int> seen;
        
        while (n != 1) {
            if (seen.count(n)) {
                return false; // Cycle detected
            }
            seen.insert(n);
            n = getSumOfSquares(n);
        }
        
        return true;
    }
    
    /**
     * @brief Mathematical approach using known cycle pattern
     * @param n Input positive integer
     * @return bool True if happy number, false otherwise
     */
    bool isHappyMath(int n) {
        // Known fact: All unhappy numbers eventually reach the cycle:
        // 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4
        unordered_set<int> unhappyCycle = {4, 16, 37, 58, 89, 145, 42, 20};
        
        while (n != 1 && unhappyCycle.find(n) == unhappyCycle.end()) {
            n = getSumOfSquares(n);
        }
        
        return n == 1;
    }
    
    /**
     * @brief Recursive approach with memoization
     * @param n Input positive integer
     * @param memo Memoization map
     * @return bool True if happy number, false otherwise
     */
    bool isHappyRecursive(int n, unordered_set<int>& memo) {
        if (n == 1) return true;
        if (memo.count(n)) return false;
        
        memo.insert(n);
        return isHappyRecursive(getSumOfSquares(n), memo);
    }
    
    bool isHappyRecursive(int n) {
        unordered_set<int> memo;
        return isHappyRecursive(n, memo);
    }

private:
    /**
     * @brief Helper function to calculate sum of squares of digits
     * @param n Input number
     * @return int Sum of squares of all digits
     */
    int getSumOfSquares(int n) {
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
};

/**
 * @brief Test function for a single case
 */
void testCase(int n, bool expected, const string& description) {
    Solution solution;
    bool result = solution.isHappy(n);
    string status = (result == expected) ? "✅ PASSED" : "❌ FAILED";
    cout << status << ": " << description << " -> " << (result ? "true" : "false") << endl;
    assert(result == expected);
}

/**
 * @brief Comprehensive test function
 */
void runTests() {
    cout << "🧪 Running Comprehensive Tests:" << endl;
    cout << "===============================" << endl;
    
    // Test Case 1: Happy number example
    testCase(19, true, "n = 19 (happy number)");
    
    // Test Case 2: Unhappy number example
    testCase(2, false, "n = 2 (unhappy number)");
    
    // Test Case 3: Single digit happy numbers
    testCase(1, true, "n = 1 (trivial happy)");
    testCase(7, true, "n = 7 (single digit happy)");
    
    // Test Case 4: Single digit unhappy numbers
    testCase(4, false, "n = 4 (enters unhappy cycle)");
    testCase(8, false, "n = 8 (unhappy number)");
    
    // Test Case 5: Multi-digit happy numbers
    testCase(10, true, "n = 10 (happy number)");
    testCase(23, true, "n = 23 (happy number)");
    
    // Test Case 6: Multi-digit unhappy numbers
    testCase(20, false, "n = 20 (unhappy number)");
    testCase(37, false, "n = 37 (part of unhappy cycle)");
    
    // Test Case 7: Large numbers
    testCase(100, true, "n = 100 (large happy number)");
    testCase(999, false, "n = 999 (large unhappy number)");
    
    cout << "\n🎉 All tests passed!" << endl;
}

/**
 * @brief Performance comparison demonstration
 */
void performanceComparison() {
    cout << "\n📊 Performance Comparison:" << endl;
    cout << "=========================" << endl;
    cout << "Approach              | Time     | Space | Pros & Cons" << endl;
    cout << "----------------------|----------|-------|-------------" << endl;
    cout << "Floyd's Cycle (Optimal)| O(log n) | O(1)  | Space efficient, elegant" << endl;
    cout << "Hash Set Detection    | O(log n) | O(log n) | Simple, easy to understand" << endl;
    cout << "Mathematical Pattern  | O(log n) | O(1)  | Fast, uses known cycle" << endl;
    cout << "Recursive Memoization | O(log n) | O(log n) | Clean code, stack overhead" << endl;
    cout << "                      |          |       |" << endl;
    cout << "Recommendation: Use Floyd's Cycle Detection for optimal space!" << endl;
}

/**
 * @brief Step-by-step walkthrough
 */
void stepByStepDemo() {
    cout << "\n💡 Step-by-step Walkthrough (Floyd's Cycle Detection):" << endl;
    cout << "=====================================================" << endl;
    
    int n = 19;
    cout << "Input: n = " << n << endl;
    cout << "Goal: Detect if process leads to 1 or cycles" << endl << endl;
    
    Solution solution;
    int slow = n, fast = n;
    int step = 0;
    
    cout << "Initial: slow = fast = " << n << endl;
    
    do {
        step++;
        slow = solution.getSumOfSquares(slow);
        fast = solution.getSumOfSquares(solution.getSumOfSquares(fast));
        
        cout << "Step " << step << ": slow = " << slow << ", fast = " << fast << endl;
        
        if (step > 10) break; // Prevent infinite output
    } while (slow != fast);
    
    cout << "\nResult: " << (slow == 1 ? "Happy number!" : "Cycle detected, not happy") << endl;
}

/**
 * @brief Demonstrate the sum of squares calculation
 */
void demonstrateSumOfSquares() {
    cout << "\n🔢 Sum of Squares Calculation Examples:" << endl;
    cout << "=======================================" << endl;
    
    Solution solution;
    vector<int> examples = {19, 82, 68, 100, 1, 23, 4, 16};
    
    for (int num : examples) {
        int result = solution.getSumOfSquares(num);
        cout << "Sum of squares of " << num << " = ";
        
        // Show digit breakdown
        int temp = num;
        string breakdown = "";
        while (temp > 0) {
            int digit = temp % 10;
            if (!breakdown.empty()) breakdown = " + " + breakdown;
            breakdown = to_string(digit) + "² " + breakdown;
            temp /= 10;
        }
        
        cout << breakdown << "= " << result << endl;
    }
}

/**
 * @brief Show the unhappy cycle pattern
 */
void showUnhappyCycle() {
    cout << "\n🔄 The Unhappy Number Cycle:" << endl;
    cout << "============================" << endl;
    
    Solution solution;
    vector<int> cycle = {4, 16, 37, 58, 89, 145, 42, 20};
    
    cout << "All unhappy numbers eventually enter this cycle:" << endl;
    for (int i = 0; i < cycle.size(); i++) {
        int current = cycle[i];
        int next = solution.getSumOfSquares(current);
        cout << current << " → " << next;
        if (i < cycle.size() - 1) cout << " → ";
    }
    cout << " → 4 (cycle repeats)" << endl;
}

/**
 * @brief Main function demonstrating the solution
 */
int main() {
    cout << "😊 LeetCode 202: Happy Number" << endl;
    cout << "=============================" << endl;
    
    // Run comprehensive tests
    runTests();
    
    // Performance comparison
    performanceComparison();
    
    // Step-by-step demonstration
    stepByStepDemo();
    
    // Demonstrate sum of squares
    demonstrateSumOfSquares();
    
    // Show unhappy cycle
    showUnhappyCycle();
    
    cout << "\n🚀 Interactive Examples:" << endl;
    cout << "========================" << endl;
    
    Solution solution;
    vector<int> examples = {1, 7, 10, 19, 23, 2, 4, 20};
    
    for (int n : examples) {
        bool result = solution.isHappy(n);
        cout << "isHappy(" << n << ") = " << (result ? "true" : "false") << endl;
    }
    
    return 0;
}

/*
🎯 KEY LEARNINGS:
1. Floyd's cycle detection is space-optimal for cycle problems
2. Mathematical patterns can provide elegant solutions
3. Sum of squares operation has interesting convergence properties
4. All unhappy numbers eventually enter the same cycle

🚀 RELATED PROBLEMS:
- LeetCode 141: Linked List Cycle
- LeetCode 142: Linked List Cycle II  
- LeetCode 287: Find the Duplicate Number
- LeetCode 457: Circular Array Loop

📚 CONCEPTS PRACTICED:
- Floyd's cycle detection algorithm
- Hash set for cycle detection
- Mathematical pattern recognition
- Digit manipulation and processing
- Space-time complexity optimization
*/