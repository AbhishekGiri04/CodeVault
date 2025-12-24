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
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (map.find(complement) != map.end()) {
            return {map[complement], i};
        }
        map[nums[i]] = i;
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = twoSum(nums, target);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;
    return 0;
}