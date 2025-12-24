/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                           ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 540                                                          ║
║ Problem Name  : Single Element in a Sorted Array                             ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Array, Binary Search, Bit Manipulation                       ║
║ Company Tags  : Amazon, Microsoft, Google, Facebook                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given a sorted array where every element appears exactly twice except for one element 
which appears exactly once, find that single element.
Must run in O(log n) time and O(1) space.

📝 EXAMPLES:
Input:  nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Input:  nums = [3,3,7,7,10,11,11]
Output: 10

🎯 CONSTRAINTS:
- 1 <= nums.length <= 10^5
- 0 <= nums[i] <= 10^5

💡 APPROACH:
Binary Search - Key insight: Before single element, pairs start at even indices
After single element, pairs start at odd indices
1. Ensure mid is even for consistent comparison
2. If nums[mid] == nums[mid+1]: single is on right
3. Otherwise: single is on left

⏰ TIME COMPLEXITY:  O(log n) - Binary search
💾 SPACE COMPLEXITY: O(1) - Constant extra space
*/

#include <iostream>
#include <vector>
using namespace std;

int singleNonDuplicate(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (mid % 2 == 1) mid--;
        
        if (nums[mid] == nums[mid + 1]) {
            left = mid + 2;
        } else {
            right = mid;
        }
    }
    return nums[left];
}

int main() {
    vector<int> nums = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    int result = singleNonDuplicate(nums);
    cout << result << endl;
    return 0;
}
