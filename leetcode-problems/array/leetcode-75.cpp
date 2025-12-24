/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 75                                                           ║
║ Problem Name  : Sort Colors                                                  ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Array, Two Pointers, Sorting                                ║
║ Company Tags  : Amazon, Microsoft, Google, Facebook, Apple                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given an array nums with n objects colored red, white, or blue, sort them in-place 
so that objects of the same color are adjacent, with the colors in the order red, 
white, and blue. We will use the integers 0, 1, and 2 to represent the color red, 
white, and blue, respectively. You must solve this problem without using the 
library's sort function.

📝 EXAMPLES:
Input:  nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Input:  nums = [2,0,1]
Output: [0,1,2]

🎯 CONSTRAINTS:
- n == nums.length
- 1 <= n <= 300
- nums[i] is either 0, 1, or 2

💡 APPROACH:
Dutch National Flag Algorithm - Three-way partitioning
1. Use three pointers: low (0s), mid (current), high (2s)
2. Process elements: 0 → swap with low, 1 → move mid, 2 → swap with high
3. Continue until mid crosses high

⏰ TIME COMPLEXITY:  O(n) - Single pass through array
💾 SPACE COMPLEXITY: O(1) - Only using pointer variables
*/

#include <iostream>
#include <vector>
using namespace std;

void sortColors(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

int main() {
    vector<int> nums = {2, 0, 2, 1, 1, 0};
    sortColors(nums);
    cout << "[";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    return 0;
}