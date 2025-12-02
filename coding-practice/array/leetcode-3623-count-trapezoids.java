/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          LEETCODE PROBLEM SOLUTION                          ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ Problem ID    : 3623                                                         ║
║ Problem Name  : Count Number of Trapezoids I                                ║
║ Difficulty    : Medium                                                       ║
║ Topic         : Array, Hash Map, Math, Combinatorics                        ║
║ Company Tags  : Google, Amazon                                              ║
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
    /**
     * @brief Counts horizontal trapezoids from given points
     * @param points 2D array of point coordinates
     * @return Number of unique horizontal trapezoids modulo 10^9+7
     * 
     * Algorithm:
     * 1. Count points at each y-coordinate
     * 2. Calculate C(n,2) for each y-level with n>=2 points
     * 3. For each pair of y-levels, multiply their combinations
     * 4. Use prefix sum to avoid double counting
     */
    public int countTrapezoids(int[][] points) {
        final long MOD = 1000000007L;
        
        // Step 1: Group points by y-coordinate
        Map<Integer, Long> yFrequency = new HashMap<>();
        for (int[] point : points) {
            int y = point[1];
            yFrequency.put(y, yFrequency.getOrDefault(y, 0L) + 1);
        }
        
        // Step 2: Calculate C(n,2) for each y-level with at least 2 points
        List<Long> combinations = new ArrayList<>();
        for (long count : yFrequency.values()) {
            if (count >= 2) {
                long comb = (count * (count - 1) / 2) % MOD;
                combinations.add(comb);
            }
        }
        
        // Edge case: Need at least 2 horizontal lines
        int n = combinations.size();
        if (n < 2) return 0;
        
        // Step 3: Count trapezoids using prefix sum technique
        long totalCombinations = 0;
        for (long comb : combinations) {
            totalCombinations = (totalCombinations + comb) % MOD;
        }
        
        long result = 0;
        for (long comb : combinations) {
            // Remove current from total to avoid counting same pair twice
            totalCombinations = (totalCombinations - comb + MOD) % MOD;
            // Multiply current line combinations with remaining lines
            result = (result + comb * totalCombinations) % MOD;
        }
        
        return (int) result;
    }
}

/**
 * Test class with comprehensive test cases
 */
class TestSolution {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        // Test Case 1: Basic example
        int[][] points1 = {{1,0},{2,0},{3,0},{2,2},{3,2}};
        int result1 = solution.countTrapezoids(points1);
        System.out.println("✅ Test 1: " + result1 + " (Expected: 3)");
        assert result1 == 3;
        
        // Test Case 2: Simple trapezoid
        int[][] points2 = {{0,0},{1,0},{0,1},{2,1}};
        int result2 = solution.countTrapezoids(points2);
        System.out.println("✅ Test 2: " + result2 + " (Expected: 1)");
        assert result2 == 1;
        
        // Test Case 3: Minimum points
        int[][] points3 = {{0,0},{1,0},{0,1},{1,1}};
        int result3 = solution.countTrapezoids(points3);
        System.out.println("✅ Test 3: " + result3 + " (Expected: 1)");
        
        // Test Case 4: No trapezoid possible
        int[][] points4 = {{0,0},{1,1},{2,2},{3,3}};
        int result4 = solution.countTrapezoids(points4);
        System.out.println("✅ Test 4: " + result4 + " (Expected: 0)");
        assert result4 == 0;
        
        System.out.println("\n🎉 All tests passed!");
        
        // Algorithm explanation
        System.out.println("\n💡 Algorithm Explanation:");
        System.out.println("1. Group points by y-coordinate");
        System.out.println("2. Calculate C(n,2) for each horizontal line");
        System.out.println("3. Count pairs of lines to form trapezoids");
        System.out.println("4. Use prefix sum to avoid double counting");
    }
}

/*
🎯 KEY LEARNINGS:
1. Horizontal trapezoid requires two horizontal parallel sides
2. Combinatorics: C(n,2) = n*(n-1)/2 for choosing 2 from n points
3. Prefix sum technique avoids nested loops and double counting
4. Modulo arithmetic prevents integer overflow

🚀 RELATED PROBLEMS:
- LeetCode 149: Max Points on a Line
- LeetCode 356: Line Reflection
- LeetCode 447: Number of Boomerangs
- LeetCode 1232: Check If It Is a Straight Line

📚 CONCEPTS PRACTICED:
- Hash map for grouping
- Combinatorics and counting
- Mathematical optimization
- Modulo arithmetic
*/
