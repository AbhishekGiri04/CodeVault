/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                           ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 3623                                                         ║
║ Problem Name  : Count Number of Trapezoids I                                 ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Array, Hash Map, Math, Combinatorics                         ║
║ Company Tags  : Google, Amazon                                               ║
╚══════════════════════════════════════════════════════════════════════════════╝

📋 PROBLEM STATEMENT:
Given a 2D array of points, count the number of unique horizontal trapezoids that can 
be formed by choosing any four distinct points. A horizontal trapezoid has at least 
one pair of horizontal sides (parallel to x-axis).

📝 EXAMPLES:
Input:  points = [[1,0],[2,0],[3,0],[2,2],[3,2]]
Output: 3
Explanation: Three distinct trapezoids can be formed with horizontal parallel sides.

Input:  points = [[0,0],[1,0],[0,1],[2,1]]
Output: 1

🎯 CONSTRAINTS:
- 4 <= points.length <= 10^5
- -10^8 <= xi, yi <= 10^8
- All points are pairwise distinct

💡 APPROACH:
Mathematical Combinatorics + Hash Map
1. Group points by y-coordinate (horizontal lines)
2. For each y-level with n points, we can choose 2 points: C(n,2) = n*(n-1)/2
3. Count pairs of horizontal lines that can form trapezoid bases
4. For two lines with c1 and c2 combinations, total trapezoids = c1 * c2

⏰ TIME COMPLEXITY:  O(n + k²) where n = points, k = unique y-coordinates
💾 SPACE COMPLEXITY: O(k) for storing y-coordinate frequencies
*/

import java.util.*;

class Solution {
    public int countTrapezoids(int[][] points) {
        final long MOD = 1000000007L;
        
        Map<Integer, Long> yFrequency = new HashMap<>();
        for (int[] point : points) {
            int y = point[1];
            yFrequency.put(y, yFrequency.getOrDefault(y, 0L) + 1);
        }
        
        List<Long> combinations = new ArrayList<>();
        for (long count : yFrequency.values()) {
            if (count >= 2) {
                long comb = (count * (count - 1) / 2) % MOD;
                combinations.add(comb);
            }
        }
        
        int n = combinations.size();
        if (n < 2) return 0;
        
        long totalCombinations = 0;
        for (long comb : combinations) {
            totalCombinations = (totalCombinations + comb) % MOD;
        }
        
        long result = 0;
        for (long comb : combinations) {
            totalCombinations = (totalCombinations - comb + MOD) % MOD;
            result = (result + comb * totalCombinations) % MOD;
        }
        
        return (int) result;
    }
}

public class Main {
    public static void main(String[] args) {
        Solution solution = new Solution();
        int[][] points = {{1,0},{2,0},{3,0},{2,2},{3,2}};
        int result = solution.countTrapezoids(points);
        System.out.println(result);
    }
}
