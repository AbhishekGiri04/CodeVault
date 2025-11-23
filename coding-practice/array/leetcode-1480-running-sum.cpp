/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 1480                                                         ║
║ Problem Name  : Running Sum of 1d Array                                     ║
║ Difficulty    : Easy                                                         ║
║ Topic         : Array, Prefix Sum                                           ║
║ Company Tags  : Amazon, Microsoft, Google                                   ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).
Return the running sum of nums.

📝 EXAMPLES:
Input:  nums = [1,2,3,4]
Output: [1,3,6,10]
Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].

Input:  nums = [1,1,1,1,1]
Output: [1,2,3,4,5]

Input:  nums = [3,1,2,10,1]
Output: [3,4,6,16,17]

🎯 CONSTRAINTS:
- 1 <= nums.length <= 1000
- -10^6 <= nums[i] <= 10^6

💡 APPROACH:
This is a classic prefix sum problem. We can solve it in-place by modifying the original array.
For each position i, we add the previous running sum to current element.

⏰ TIME COMPLEXITY:  O(n) - Single pass through array
💾 SPACE COMPLEXITY: O(1) - In-place modification (excluding output space)
*/

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution {
public:
    /**
     * @brief Calculates running sum of 1D array using prefix sum technique
     * @param nums Input array of integers
     * @return vector<int> Array containing running sums
     * 
     * Algorithm:
     * 1. Iterate through array starting from index 1
     * 2. Add previous element to current element (in-place)
     * 3. This creates cumulative sum at each position
     */
    vector<int> runningSum(vector<int>& nums) {
        // Edge case: empty array (though constraints guarantee non-empty)
        if (nums.empty()) return nums;
        
        // Calculate running sum in-place
        // nums[i] = nums[i] + nums[i-1] for i >= 1
        for (int i = 1; i < nums.size(); i++) {
            nums[i] += nums[i - 1];
        }
        
        return nums;
    }
    
    /**
     * @brief Alternative approach using separate result array
     * @param nums Input array (remains unchanged)
     * @return vector<int> New array with running sums
     */
    vector<int> runningSumAlternative(vector<int>& nums) {
        vector<int> result(nums.size());
        result[0] = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            result[i] = result[i - 1] + nums[i];
        }
        
        return result;
    }
};

/**
 * @brief Test function to validate solution with multiple test cases
 */
void runTests() {
    Solution solution;
    
    // Test Case 1: Basic example
    vector<int> test1 = {1, 2, 3, 4};
    vector<int> expected1 = {1, 3, 6, 10};
    vector<int> result1 = solution.runningSum(test1);
    assert(result1 == expected1);
    cout << "✅ Test 1 Passed: [1,2,3,4] -> [1,3,6,10]" << endl;
    
    // Test Case 2: All same elements
    vector<int> test2 = {1, 1, 1, 1, 1};
    vector<int> expected2 = {1, 2, 3, 4, 5};
    vector<int> result2 = solution.runningSum(test2);
    assert(result2 == expected2);
    cout << "✅ Test 2 Passed: [1,1,1,1,1] -> [1,2,3,4,5]" << endl;
    
    // Test Case 3: Mixed positive numbers
    vector<int> test3 = {3, 1, 2, 10, 1};
    vector<int> expected3 = {3, 4, 6, 16, 17};
    vector<int> result3 = solution.runningSum(test3);
    assert(result3 == expected3);
    cout << "✅ Test 3 Passed: [3,1,2,10,1] -> [3,4,6,16,17]" << endl;
    
    // Test Case 4: Single element
    vector<int> test4 = {5};
    vector<int> expected4 = {5};
    vector<int> result4 = solution.runningSum(test4);
    assert(result4 == expected4);
    cout << "✅ Test 4 Passed: [5] -> [5]" << endl;
}

/**
 * @brief Utility function to print array elements
 */
void printArray(const vector<int>& arr, const string& label) {
    cout << label << ": [";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

/**
 * @brief Main function demonstrating the solution
 */
int main() {
    cout << "🚀 LeetCode 1480: Running Sum of 1d Array" << endl;
    cout << "===========================================" << endl;
    
    // Run comprehensive tests
    runTests();
    
    cout << "\n📊 Interactive Example:" << endl;
    Solution solution;
    
    // Interactive example
    vector<int> nums = {1, 2, 3, 4};
    printArray(nums, "Original Array");
    
    vector<int> result = solution.runningSum(nums);
    printArray(result, "Running Sum   ");
    
    cout << "\n💡 Explanation:" << endl;
    cout << "Position 0: 1 = 1" << endl;
    cout << "Position 1: 1 + 2 = 3" << endl;
    cout << "Position 2: 1 + 2 + 3 = 6" << endl;
    cout << "Position 3: 1 + 2 + 3 + 4 = 10" << endl;
    
    return 0;
}

/*
🎯 KEY LEARNINGS:
1. Prefix sum is a fundamental technique for range sum queries
2. In-place modification can optimize space complexity
3. Always consider edge cases (empty array, single element)
4. Test with various inputs to ensure correctness

🚀 RELATED PROBLEMS:
- LeetCode 303: Range Sum Query - Immutable
- LeetCode 304: Range Sum Query 2D - Immutable
- LeetCode 560: Subarray Sum Equals K

📚 CONCEPTS PRACTICED:
- Array manipulation
- Prefix sum technique
- In-place algorithms
- Time/space complexity optimization
*/