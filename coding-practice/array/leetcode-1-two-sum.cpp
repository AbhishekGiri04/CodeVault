/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 1                                                            ║
║ Problem Name  : Two Sum                                                      ║
║ Difficulty    : Easy                                                         ║
║ Topic         : Array, Hash Table                                           ║
║ Company Tags  : Amazon, Apple, Google, Microsoft, Facebook                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given an array of integers nums and an integer target, return indices of the two numbers 
such that they add up to target. You may assume that each input would have exactly one 
solution, and you may not use the same element twice.

📝 EXAMPLES:
Input:  nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Input:  nums = [3,2,4], target = 6
Output: [1,2]

Input:  nums = [3,3], target = 6
Output: [0,1]

🎯 CONSTRAINTS:
- 2 <= nums.length <= 10^4
- -10^9 <= nums[i] <= 10^9
- -10^9 <= target <= 10^9
- Only one valid answer exists

💡 APPROACHES:
1. Brute Force: Check all pairs - O(n²) time, O(1) space
2. Hash Map: Single pass with complement lookup - O(n) time, O(n) space

⏰ OPTIMAL SOLUTION: Hash Map approach
💾 TIME COMPLEXITY:  O(n) - Single pass through array
💾 SPACE COMPLEXITY: O(n) - Hash map storage
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
using namespace std;

class Solution {
public:
    /**
     * @brief Finds two indices that sum to target using hash map (OPTIMAL)
     * @param nums Input array of integers
     * @param target Target sum value
     * @return vector<int> Indices of two numbers that sum to target
     * 
     * Algorithm:
     * 1. Use hash map to store {value -> index} mapping
     * 2. For each element, calculate complement = target - current
     * 3. Check if complement exists in hash map
     * 4. If found, return current index and complement's index
     * 5. Otherwise, add current element to hash map
     */
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numMap; // {value -> index}
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // Check if complement exists in hash map
            if (numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }
            
            // Add current number and its index to hash map
            numMap[nums[i]] = i;
        }
        
        // Should never reach here given problem constraints
        return {};
    }
    
    /**
     * @brief Brute force approach - O(n²) solution (for comparison)
     * @param nums Input array of integers
     * @param target Target sum value
     * @return vector<int> Indices of two numbers that sum to target
     */
    vector<int> twoSumBruteForce(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
    
    /**
     * @brief Two-pointer approach (only works on sorted array)
     * @param nums Input array (must be sorted)
     * @param target Target sum value
     * @return vector<int> Values (not indices) that sum to target
     * 
     * Note: This approach loses original indices due to sorting
     */
    vector<int> twoSumTwoPointer(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                return {nums[left], nums[right]};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {};
    }
};

/**
 * @brief Utility function to print vector
 */
void printVector(const vector<int>& vec, const string& label) {
    cout << label << ": [";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

/**
 * @brief Comprehensive test function
 */
void runTests() {
    Solution solution;
    
    // Test Case 1: Basic example
    vector<int> test1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = solution.twoSum(test1, target1);
    vector<int> expected1 = {0, 1};
    assert(result1 == expected1);
    cout << "✅ Test 1 Passed: [2,7,11,15], target=9 -> [0,1]" << endl;
    
    // Test Case 2: Different positions
    vector<int> test2 = {3, 2, 4};
    int target2 = 6;
    vector<int> result2 = solution.twoSum(test2, target2);
    vector<int> expected2 = {1, 2};
    assert(result2 == expected2);
    cout << "✅ Test 2 Passed: [3,2,4], target=6 -> [1,2]" << endl;
    
    // Test Case 3: Duplicate numbers
    vector<int> test3 = {3, 3};
    int target3 = 6;
    vector<int> result3 = solution.twoSum(test3, target3);
    vector<int> expected3 = {0, 1};
    assert(result3 == expected3);
    cout << "✅ Test 3 Passed: [3,3], target=6 -> [0,1]" << endl;
    
    // Test Case 4: Negative numbers
    vector<int> test4 = {-1, -2, -3, -4, -5};
    int target4 = -8;
    vector<int> result4 = solution.twoSum(test4, target4);
    vector<int> expected4 = {2, 4}; // -3 + -5 = -8
    assert(result4 == expected4);
    cout << "✅ Test 4 Passed: [-1,-2,-3,-4,-5], target=-8 -> [2,4]" << endl;
    
    // Test Case 5: Large numbers
    vector<int> test5 = {1000000000, 999999999, 1};
    int target5 = 1999999999;
    vector<int> result5 = solution.twoSum(test5, target5);
    vector<int> expected5 = {0, 1};
    assert(result5 == expected5);
    cout << "✅ Test 5 Passed: Large numbers test" << endl;
}

/**
 * @brief Performance comparison demonstration
 */
void performanceComparison() {
    cout << "\n📊 Performance Comparison:" << endl;
    cout << "=========================" << endl;
    cout << "Approach        | Time     | Space | Best For" << endl;
    cout << "----------------|----------|-------|----------" << endl;
    cout << "Hash Map        | O(n)     | O(n)  | General case (OPTIMAL)" << endl;
    cout << "Brute Force     | O(n²)    | O(1)  | Small arrays, space-critical" << endl;
    cout << "Two Pointer     | O(n log n)| O(1) | Sorted arrays (loses indices)" << endl;
    cout << "                |          |       |" << endl;
    cout << "Recommendation: Use Hash Map approach for this problem!" << endl;
}

/**
 * @brief Step-by-step walkthrough
 */
void stepByStepDemo() {
    cout << "\n💡 Step-by-step Walkthrough (Hash Map):" << endl;
    cout << "=======================================" << endl;
    
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    
    cout << "Array: [2, 7, 11, 15], Target: 9" << endl;
    cout << "Hash Map: {}" << endl << endl;
    
    cout << "Step 1: i=0, nums[0]=2" << endl;
    cout << "  Complement = 9 - 2 = 7" << endl;
    cout << "  7 not in hash map" << endl;
    cout << "  Add {2: 0} to hash map" << endl;
    cout << "  Hash Map: {2: 0}" << endl << endl;
    
    cout << "Step 2: i=1, nums[1]=7" << endl;
    cout << "  Complement = 9 - 7 = 2" << endl;
    cout << "  2 found in hash map at index 0!" << endl;
    cout << "  Return [0, 1]" << endl;
}

/**
 * @brief Main function demonstrating the solution
 */
int main() {
    cout << "🎯 LeetCode 1: Two Sum" << endl;
    cout << "======================" << endl;
    
    // Run comprehensive tests
    runTests();
    
    // Performance comparison
    performanceComparison();
    
    // Step-by-step demonstration
    stepByStepDemo();
    
    cout << "\n🚀 Interactive Example:" << endl;
    cout << "=======================" << endl;
    
    Solution solution;
    
    // Interactive example
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    
    printVector(nums, "Input Array");
    cout << "Target: " << target << endl;
    
    vector<int> result = solution.twoSum(nums, target);
    printVector(result, "Result Indices");
    
    cout << "Verification: nums[" << result[0] << "] + nums[" << result[1] 
         << "] = " << nums[result[0]] << " + " << nums[result[1]] 
         << " = " << (nums[result[0]] + nums[result[1]]) << endl;
    
    return 0;
}

/*
🎯 KEY LEARNINGS:
1. Hash map provides O(n) solution vs O(n²) brute force
2. Trade space for time - classic algorithmic principle
3. Complement calculation: target - current_number
4. Single pass is possible with hash map approach

🚀 RELATED PROBLEMS:
- LeetCode 15: 3Sum
- LeetCode 18: 4Sum
- LeetCode 167: Two Sum II - Input array is sorted
- LeetCode 170: Two Sum III - Data structure design

📚 CONCEPTS PRACTICED:
- Hash table/map usage
- Array traversal
- Complement calculation
- Time-space complexity trade-offs
- Multiple solution approaches
*/