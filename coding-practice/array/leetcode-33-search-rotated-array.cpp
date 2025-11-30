/*
 * LeetCode 33: Search in Rotated Sorted Array
 * Difficulty: Medium
 * 
 * Problem:
 * Given a rotated sorted array and a target value, return the index of target.
 * If target is not found, return -1.
 * Must achieve O(log n) runtime complexity.
 * 
 * Example:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * 
 * Approach: Modified Binary Search
 * Key Insight: At least one half of the array is always sorted
 * 
 * Steps:
 * 1. Find mid element using binary search
 * 2. Determine which half is sorted (left or right)
 * 3. Check if target lies in the sorted half
 * 4. Adjust search boundaries accordingly
 * 5. Repeat until target is found or search space is exhausted
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            }
            
            // Check if left half is sorted
            if (nums[left] <= nums[mid]) {
                // Target is in left sorted half
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            // Right half is sorted
            else {
                // Target is in right sorted half
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
};

int main() {
    Solution solution;
    
    // Test Case 1
    vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Test 1: " << solution.search(nums1, 0) << " (Expected: 4)" << endl;
    
    // Test Case 2
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Test 2: " << solution.search(nums2, 3) << " (Expected: -1)" << endl;
    
    // Test Case 3
    vector<int> nums3 = {1};
    cout << "Test 3: " << solution.search(nums3, 0) << " (Expected: -1)" << endl;
    
    // Test Case 4
    vector<int> nums4 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Test 4: " << solution.search(nums4, 5) << " (Expected: 1)" << endl;
    
    return 0;
}