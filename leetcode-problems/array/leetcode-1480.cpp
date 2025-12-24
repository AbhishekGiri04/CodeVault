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
Prefix sum technique - modify array in-place
1. Iterate through array starting from index 1
2. Add previous element to current element
3. This creates cumulative sum at each position

⏰ TIME COMPLEXITY:  O(n) - Single pass through array
💾 SPACE COMPLEXITY: O(1) - In-place modification
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> runningSum(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        nums[i] += nums[i - 1];
    }
    return nums;
}

int main() {
    vector<int> nums = {1, 2, 3, 4};
    vector<int> result = runningSum(nums);
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    return 0;
}