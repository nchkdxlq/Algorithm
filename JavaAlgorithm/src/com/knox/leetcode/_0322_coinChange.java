package com.knox.leetcode;

import java.util.Arrays;

public class _0322_coinChange {

    static class Solution {

        public int coinChange(int[] coins, int amount) {
//            return coinChange_v1(coins, amount);
            return coinChange_v2(coins, amount);
        }

        private int coinChange_v2(int[] coins, int amount) {
            int n = coins.length;
            // dp[i]总结额为i时，所需要的最少硬币数量
            int[] dp = new int[amount + 1];
            Arrays.fill(dp, amount + 1);

            // base case
            dp[0] = 0;
            for (int i = 0; i < n; i++) {
                for (int j = coins[i]; j <= amount; j++) {
                    int ans1 = dp[j]; // 不使用coins[i]
                    int ans2 = dp[j - coins[i]] + 1; // 使用coins[i]
                    dp[j] = Math.min(ans1, ans2);
                }
            }
            return dp[amount] > amount ? -1 : dp[amount];
        }

        private int coinChange_v1(int[] coins, int amount) {
            int n = coins.length;
            // dp[i][j] 表示从[0..i]的硬币中任意取，可以重复取，凑成总额为j时需要的最少硬币数量
            int[][] dp = new int[n][amount + 1];
            for (int i = 0; i < n; i++) {
                Arrays.fill(dp[i], amount + 1);
            }
            // base case
            dp[0][0] = 0;
            for (int i = 1; i <= amount; i++) {
                if (i >= coins[0]) { // 总额比币值还大才能使用
                    dp[0][i] = dp[0][i - coins[0]] + 1;
                }
            }

            for (int i = 1; i < n; i++) {
                for (int j = 0; j <= amount; j++) {
                    if (j >= coins[i]) {
                        int ans1 = dp[i-1][j]; // 在总金额为j的不使用coins[i]
                        int ans2 = dp[i][j - coins[i]] + 1; // 使用coins[i]
                        dp[i][j] = Math.min(ans1, ans2);
                    } else {
                        dp[i][j] = dp[i-1][j]; // 总额比币值还小，不能使用
                    }
                }
            }

            return dp[n-1][amount] > amount ? -1 : dp[n-1][amount];
        }
    }

    public static void main(String[] args) {
        int[] coins = {1, 2, 5};
        int amount = 11;
        Solution ins = new Solution();
        int ans = ins.coinChange(coins, amount);
        System.out.println("v = " + ans);
    }
}
