package com.knox.leetcode;

/*
*
*   给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。
    请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。
    假设每一种面额的硬币有无限个。
* */
public class _0518_change_v2 {

    static class Solution {

        public int change(int amount, int[] coins) {
//            return change_v1(amount, coins);
            return change_v2(amount, coins);
        }
        // 动态规划 - 状态压缩
        private int change_v2(int amount, int[] coins) {
            int n = coins.length;

            // dp[i] 在coins中任意取凑金额i时有多少种组合
            int dp[] = new int[amount + 1];
            // base case
            dp[0] = 1;

            for (int i = 0; i < n; i++) {
                for (int j = coins[i]; j <= amount; j++) {
                    dp[j] += dp[j - coins[i]];
                }
            }
            return dp[amount];
        }

        // 动态规划 -
        private int change_v1(int amount, int[] coins) {
            int n = coins.length;

            // dp[i][j] 表示[0..i]个物品任意取凑成金额为j的组合数
            int[][] dp = new int[n][amount + 1];

            // base case
            dp[0][0] = 1; // 金额为0有一种凑法
            for (int i = 1; i <= amount; i++) {
                if (i >= coins[0]) {
                    dp[0][i] = dp[0][i - coins[0]];
                } else { // coins[0]大于i无法凑
                    dp[0][i] = 0;
                }
            }

            for (int i = 1; i < n; i++) {
                for (int j = 0; j <= amount; j++) {
                    if (j >= coins[i]) {
                        int ans1 = dp[i-1][j]; // 不使用coins[i]
                        int ans2 = dp[i][j - coins[i]]; // 使用coins[i]
                        dp[i][j] = ans1 + ans2;
                    } else {
                        dp[i][j] = dp[i-1][j];
                    }
                }
            }

            return dp[n-1][amount];
        }
    }

    public static void main(String[] args) {
        int[] coins = {1, 2, 5};
        int amount = 5;
        Solution ins = new Solution();
        int ans = ins.change(amount, coins);
        System.out.println("v = " + ans);
    }
}
