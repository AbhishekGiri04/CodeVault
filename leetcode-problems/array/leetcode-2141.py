"""
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 2141                                                         ║
║ Problem Name  : Maximum Running Time of N Computers                        ║
║ Difficulty    : Hard                                                        ║
║ Topic         : Array, Binary Search, Greedy                               ║
║ Company Tags  : Google, Amazon, Microsoft                                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
You have n computers and batteries array where batteries[i] can run a computer for 
batteries[i] minutes. You can swap batteries between computers at any time (instant).
Return the maximum number of minutes you can run all n computers simultaneously.

📝 EXAMPLES:
Input:  n = 2, batteries = [3,3,3]
Output: 4
Explanation: Use batteries strategically to run 2 computers for 4 minutes total.

Input:  n = 2, batteries = [1,1,1,1]
Output: 2
Explanation: Total power = 4, distributed across 2 computers = 2 minutes each.

🎯 CONSTRAINTS:
- 1 <= n <= batteries.length <= 10^5
- 1 <= batteries[i] <= 10^9

💡 APPROACH:
Binary Search + Greedy Validation
1. Binary search on the answer (time duration)
2. For each candidate time, check if we can run n computers for that duration
3. Key insight: If battery > time, we can only use 'time' minutes from it
4. Sum all usable power and check if total >= n * time

⏰ TIME COMPLEXITY:  O(m * log(sum/n)) where m = len(batteries)
💾 SPACE COMPLEXITY: O(1) - Only using constant extra space
"""

def maxRunTime(n, batteries):
    left, right = 0, sum(batteries) // n
    
    def can_run(time):
        total = sum(min(battery, time) for battery in batteries)
        return total >= time * n
    
    while left < right:
        mid = (left + right + 1) // 2
        if can_run(mid):
            left = mid
        else:
            right = mid - 1
    
    return left

if __name__ == "__main__":
    n = 2
    batteries = [3, 3, 3]
    result = maxRunTime(n, batteries)
    print(result)