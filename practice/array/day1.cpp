/*
LeetCode Problem 1480: Running Sum of 1d Array
Difficulty: Easy
Topic: Arrays

Problem Statement:
Given an array nums, return the running sum of nums.
The running sum is defined as runningSum[i] = sum(nums[0] … nums[i]).

Example:
Input: nums = [1,2,3,4]
Output: [1,3,6,10]

Input: nums = [3,1,2,10,1]
Output: [3,4,6,16,17]
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> running_sum; // Vector to store running sum
        int sum = 0;             // Initialize sum to 0

        // Traverse the array and calculate running sum
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i];           // Add current element to sum
            running_sum.push_back(sum); // Append sum to running_sum vector
        }

        return running_sum; // Return the final running sum array
    }
};

// Example usage (for testing)
int main() {
    Solution sol;
    vector<int> nums = {1,2,3,4};
    vector<int> result = sol.runningSum(nums);

    cout << "Running sum: ";
    for(int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
