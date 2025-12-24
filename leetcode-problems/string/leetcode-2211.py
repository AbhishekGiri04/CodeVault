"""
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 2211                                                         ║
║ Problem Name  : Count Collisions on a Road                                  ║
║ Difficulty    : Medium                                                       ║
║ Topic         : String, Simulation, Greedy                                  ║
║ Company Tags  : Amazon, Google                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given a string representing car directions ('L', 'R', 'S'), count total collisions.
- 'L': moving left
- 'R': moving right  
- 'S': stationary

Collision rules:
- Opposite directions: +2 collisions
- Moving hits stationary: +1 collision

📝 EXAMPLES:
Input:  directions = "RLRSLL"
Output: 5
Explanation: Multiple collisions occur as cars meet.

Input:  directions = "LLRR"
Output: 0
Explanation: No cars collide (all moving away).

🎯 CONSTRAINTS:
- 1 <= directions.length <= 10^5
- directions[i] is 'L', 'R', or 'S'

💡 APPROACH:
Greedy String Processing
1. Remove leading 'L' (cars moving left from start - no collision)
2. Remove trailing 'R' (cars moving right to end - no collision)
3. Count remaining non-'S' cars (all will collide and become stationary)

Key Insight: After removing edge cases, all moving cars in middle will collide.

⏰ TIME COMPLEXITY:  O(n) - Single pass through string
💾 SPACE COMPLEXITY: O(n) - String operations create new strings
"""

def countCollisions(directions):
    directions = directions.lstrip('L').rstrip('R')
    return sum(c != 'S' for c in directions)

if __name__ == "__main__":
    directions = "RLRSLL"
    result = countCollisions(directions)
    print(result)