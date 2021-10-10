package com.knox.leetcode;

import java.util.Arrays;

/*
* 有N件物品和一个最多能被重量为C的背包。第i件物品的重量是weight[i]，得到的价值是value[i] 。
* 每件物品只能用一次，求解将哪些物品装入背包里物品价值总和最大。
*
* */
public class Knapsack {
    static class Solution {

        int knapsack(int[] weight, int[] value, int c) {
            return knapsack_v3(weight, value, c);
//            return knapsack_v5(weight, value, c);
        }

        int knapsack_v5(int[] weight, int[] value, int c) {
            int count = weight.length;
            int[] dp = new int[c+1]; // dp[j]是容量为j时, 所有物品可装下的的最大价值
            for (int i = 0; i < count; i++) {
                // 为什么容量从大的开始而不是从小的开始, 因为求大容量时需要用到小容量的解, 避免覆盖。
                for (int j = c; j >= weight[i]; j--) {
                    dp[j] = Math.max(dp[j], dp[j-weight[i]] + value[i]);
                }
            }
            return dp[c];
        }

        // 动态规划 - 在knapsack_v3的基础上状态压缩, 在递推方程中, 只需要前一个状态
        int knapsack_v4(int[] weight, int[] value, int c) {
            int count = weight.length;
            if  (count == 0 || c == 0) return 0;

            int[][] dp = new int[2][c+1];

            for (int i = 1; i <= count; i++) {
                for (int j = 1; j <= c; j++) {
                    int curIndex = i % 2;
                    int prevIndex = (i - 1) % 2;
                    int ans1 = dp[prevIndex][j];
                    int ans2 = 0;
                    if (j >= weight[i-1]) {
                        ans2 = dp[prevIndex][j - weight[i-1]] + value[i-1];
                    }
                    dp[curIndex][j] = Math.max(ans1, ans2);
                }
            }

            return dp[count % 2][c];
        }

        // 动态规划 - 自底向上的解决问题, 状态转移方程 f(n, c) = f(n-1, c) + f(n-1, c - w[n])
        int knapsack_v3(int[] weight, int[] value, int c) {
            int count = weight.length;
            if  (count == 0 || c == 0) return 0;

            // dp[i][j]表示从前i个物品中任意取，放进容量为j的背包中，物品的价值总和最大
            int[][] dp = new int[count+1][c+1];

            for (int i = 1; i <= count; i++) {
                for (int j = 1; j <= c; j++) {
                    // 1. 不放第i-1个物品
                    int ans1 = dp[i-1][j];
                    // 2. 放第i-1个物品,
                    // 2.1 如果weight[i-1] > j, 超过容量,无法放下, 最大价值为0
                    // 2.2 如果weight[i-1] <= j, 需要加上前i-1个物品, j-weight[i-1]的容量下的最大价值, 即dp[i-1][j - weight[i-1]]
                    int ans2 = 0;
                    if (j >= weight[i-1]) {
                        ans2 = dp[i-1][j - weight[i-1]] + value[i-1];
                    }
                    dp[i][j] = Math.max(ans1, ans2);
                }
            }

            return dp[count][c];
        }

        // 在knapsack_v1上增加记忆化搜索, 缓存子问题的解
        private int[][] memo;
        int knapsack_v2(int[] weight, int[] value, int c) {
            memo = new int[weight.length][c + 1];
            for (int i = 0; i < weight.length; i++) {
                Arrays.fill(memo[i], -1);
            }
            return v2_dfs(weight, value, value.length - 1, c);
        }

        int v2_dfs(int[] weight, int[] value, int index, int c) {
            if (index < 0 || c <= 0) return 0;

            if (memo[index][c] > -1) return memo[index][c];
            // 1. 不选择下标为index的物品
            int ans1 = v2_dfs(weight, value, index - 1, c);

            // 2. 选择下标为index的物品
            int ans2 = 0;
            if (c >= weight[index]) {
                ans2 = value[index] + v2_dfs(weight, value, index - 1, c - weight[index]);
            }
            int ans = Math.max(ans1, ans2);
            memo[index][c] = ans;
            return ans;
        }

        int knapsack_v1(int[] weight, int[] value, int c) {
            return v1_dfs(weight, value, value.length - 1, c);
        }

        /**
         *  递归解决 - 自顶向下的解决问题
         *  在物品的[0...index]区间中, 选择物品装入背包中, 使得物品总价值最大
         * @param weight 物品的重量
         * @param value 物品的价值
         * @param index 物品的最大下标
         * @param c 背包的容量
         * @return 背包所装物品的最大价值
         */
        int v1_dfs(int[] weight, int[] value, int index, int c) {
            if (index < 0 || c <= 0) return 0;

            // 1. 不选择下标为index的物品
            int ans1 = v1_dfs(weight, value, index - 1, c);

            // 2. 选择下标为index的物品
            int ans2 = 0;
            if (c >= weight[index]) {
                ans2 = value[index] + v1_dfs(weight, value, index - 1, c - weight[index]);
            }

            return Math.max(ans1, ans2);
        }
    }

    public static void main(String[] args) {
        Solution ins = new Solution();
        int[] w = {1, 3, 4};
        int[] v = {15, 20, 30};
        int c = 4;
        int ans = ins.knapsack_v1(w, v, c);
        System.out.println("v1 = " + ans);

        ans = ins.knapsack_v2(w, v, c);
        System.out.println("v2 = " + ans);

        ans = ins.knapsack_v3(w, v, c);
        System.out.println("v3 = " + ans);

        ans = ins.knapsack_v4(w, v, c);
        System.out.println("v4 = " + ans);

        ans = ins.knapsack_v5(w, v, c);
        System.out.println("v5 = " + ans);
    }
}
