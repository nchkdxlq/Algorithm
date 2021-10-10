package com.knox.leetcode;

/*
*
* 有N件物品和一个最多能背重量为W的背包。第i件物品的重量是weight[i]，得到的价值是value[i] 。
* 每件物品都有无限个（也就是可以放入背包多次），求解将哪些物品装入背包里物品价值总和最大。
*
* */
public class FullKnapsack {

    static class Solution {
        int knapsack(int[] weight, int[] value, int c) {
            return knapsack_v2(weight, value, c);
        }

        int knapsack_v2(int[] weight, int[] value, int c) {
            int n = weight.length;
            // dp[i]表示任意取物品放入容量为i的背包中，最大总价值
            int[] dp = new int[c + 1];
            // base case
            dp[0] = 0;
            for (int i = 0; i < n; i++) {
                // 遍历容量从小开始遍历
                for (int j = weight[i]; j <= c; j++) {
                    int ans1 = dp[j]; // 不使用第i个物品
                    int ans2 = dp[j - weight[i]] + value[i];
                    dp[j] = Math.max(ans1, ans2);
                }
            }
            return dp[c];
        }

        int knapsack_v1(int[] weight, int[] value, int c) {
            int n = weight.length;

            // dp[i][j]表示在前i个物品中任意取，每个物品可以取多次，放入容量为j的背包中，物品的总价值最大
            int[][] dp = new int[n+1][c+1];

            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= c; j++) {
                    if (j >= weight[i-1]) {
                        int ans1 = dp[i-1][j]; // 不使用第i个物品
                        /*
                         *  因为物品可以使用多次，所以是dp[i]而不是dp[i-1], 这是和0-1背包问题的核心区别。
                         *
                         * 为什么这样做物品就重复使用了?
                         *  1. dp[i][c1]表示前i个物品在c1容量时价值最大, 计算dp[i][c1]时使用了第i个物品
                         *  2. 现在计算 dp[i][c2], c1 = c2 - weight[i-1], dp[i][c2] = dp[i][c1] + value[i-1];
                         *     在dp[i][c2]在dp[i][c1]的基础上又加了value[i-1], 所以物品就使用了多次.
                         *
                         * */

                        int ans2 = dp[i][j - weight[i-1]] + value[i-1]; // 使用第i个物品
                        dp[i][j] = Math.max(ans1, ans2);
                    } else {
                        dp[i][j] = dp[i-1][j];
                    }
                }
            }

            return dp[n-1][c];
        }
    }

    public static void main(String[] args) {
        Solution ins = new Solution();
        int[] w = {2, 3, 4};
        int[] v = {15, 20, 30};
        int c = 6;
        int ans = ins.knapsack_v1(w, v, c);
        System.out.println("v1 = " + ans);

        ans = ins.knapsack_v2(w, v, c);
        System.out.println("v1 = " + ans);
    }
}
