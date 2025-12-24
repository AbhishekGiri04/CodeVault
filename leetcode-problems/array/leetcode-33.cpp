/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 33                                                           ║
║ Problem Name  : Search in Rotated Sorted Array                              ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Array, Binary Search                                        ║
║ Company Tags  : Amazon, Microsoft, Facebook, Google, Apple                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given a rotated sorted array and a target value, return the index of target.
If target is not found in the array, return -1.
You must write an algorithm with O(log n) runtime complexity.

📝 EXAMPLES:
Input:  nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Input:  nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Input:  nums = [1], target = 0
Output: -1

🎯 CONSTRAINTS:
- 1 <= nums.length <= 5000
- -10^4 <= nums[i] <= 10^4
- All values of nums are unique
- nums is an ascending array that is possibly rotated
- -10^4 <= target <= 10^4

💡 APPROACH:
Modified Binary Search - Key insight: At least one half is always sorted.
1. Find mid element
2. Determine which half is sorted (left or right)
3. Check if target lies in the sorted half's range
4. Eliminate the half that cannot contain target
5. Repeat until found or search space exhausted

⏰ TIME COMPLEXITY:  O(log n) - Binary search elimination
💾 SPACE COMPLEXITY: O(1) - Constant extra space
*/

#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) return mid;
        
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;
    int result = search(nums, target);
    cout << result << endl;
    return 0;
}