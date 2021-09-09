package com.knox.leetcode;

/*
* 有N件物品和一个最多能被重量为C的背包。第i件物品的重量是weight[i]，得到的价值是value[i] 。
* 每件物品只能用一次，求解将哪些物品装入背包里物品价值总和最大。
*
* */
public class Knapsack {
    static class Solution {

        int knapsack(int[] weight, int[] value, int c) {
            int count = weight.length;

            // dp[i][j]表示从下标为[0..i]的物品中任务取,放进容量为j的背包中, 价值的最大值
            int[][] dp = new int[count+1][c+1];

            // 把[0..i]的物品任意取放入容量为0的背包中的价值
//            for (int i = 0; i <= count; i++) {
//                dp[i][0] = 0;
//            }

            // 先遍历物品, 在遍历背包
            for (int i = 1; i <= count; i++) {
                for (int j = 1; j <= c; j++) {
                    if (j < weight[i-1]) {
                        dp[i][j] = dp[i-1][j];
                    } else {
                        dp[i][j] = Math.max(dp[i-1][j], dp[i-1][j-weight[i-1]] + value[i-1]);
                    }
                }
            }
            return dp[count][c];
        }

        int knapsack_v2(int[] weight, int[] value, int c) {
            int count = weight.length;
            int[] dp = new int[c+1]; // 容量为j的背包，所背的物品价值可以最大为dp[j]。
            for (int i = 0; i < count; i++) {
                for (int j = c; j >= weight[i]; j--) {
                    dp[j] = Math.max(dp[j], dp[j-weight[i]] + value[i]);
                }
            }
            return dp[c];
        }
    }

    public static void main(String[] args) {
        Solution ins = new Solution();
        int[] w = {1, 3, 4};
        int[] v = {15, 20, 30};
        int c = 4;
        int ans = ins.knapsack(w, v, c);
        System.out.println(ans);

        ans = ins.knapsack_v2(w, v, c);
        System.out.println(ans);
    }
}
