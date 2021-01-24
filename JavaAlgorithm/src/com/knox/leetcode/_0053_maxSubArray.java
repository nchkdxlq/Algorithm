package com.knox.leetcode;

import com.knox.tools.Asserts;

/**
 * 53. 最大子序和
 * 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 *
 * https://leetcode-cn.com/problems/maximum-subarray/
 *
 */
public class _0053_maxSubArray {

    static class Solution {
        public int maxSubArray(int[] nums) {
            return maxSubArray_v0(nums);
        }

        /**
         * 暴力解法
         * 时间复杂度: O(n^2)
         */
        private int maxSubArray_v0(int[] nums) {
            int n = nums.length;
            if (n == 0) return 0;

            int max = Integer.MIN_VALUE;
            // 任意区间的子数组的和, 然后取最大值
            for (int i = 0; i < n; i++) {
                int sum = 0;
                for (int j = i; j < n; j++) {
                    sum += nums[j];
                    if (sum > max) {
                        max = sum;
                    }
                }
            }
            return max;
        }

        /**
         * 动态规划
         * 时间复杂度: O(n)
         * 空间复杂度: O(n)
         */
        private int maxSubArray_v1(int[] nums) {
            int n = nums.length;
            if (n == 0) return 0;

            // 以nums[i]为结尾的"最大子数组和"为dp[i]
            int[] dp = new int[n];

            // base case, 第一个元素前面没有子数组
            dp[0] = nums[0];

            // 状态转移方程
            for (int i = 1; i < n; i++) {
                dp[i] = Math.max(nums[i], dp[i - 1] + nums[i]);
            }

            int max = dp[0];
            for (int i = 1; i < n; i++) {
                if (dp[i] > max) {
                    max = dp[i];
                }
            }
            return max;
        }


        /**
         * 对上面动态规划优空间复杂度优化
         * 时间复杂度: O(n)
         * 空间复杂度: O(1)
         */
        private int maxSubArray_v2(int[] nums) {
            int n = nums.length;
            if (n == 0) return 0;

            // base case, 第一个元素前面没有子数组
            int max = nums[0];
            int dp_prev = nums[0]; // 以nums[i-1]结尾的子数组的和的最大值

            // 状态转移方程 f(i) = max(nums[i], f(i-1) + nums[i])
            for (int i = 1; i < n; i++) {
                dp_prev = Math.max(nums[i], dp_prev + nums[i]);
                max = Math.max(dp_prev, max);
            }
            return max;
        }

        /**
         * 贪心策略
         * 时间复杂度: O(n)
         * 空间复杂度: O(1)
         */
        private int maxSubArray_v3(int[] nums) {
            int n = nums.length;
            if (n == 0) return 0;

            int max = nums[0];
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += nums[i];
                if (sum > max) {
                    max = sum;
                }
                if (sum < 0) { // 重置最大和子序列的其实位置
                    sum = 0;
                }
            }
            return max;
        }
    }


    public static void main(String[] args) {
        Solution ins = new Solution();

        {
            int[] nums = {-2,1,-3,4,-1,2,1,-5,4};
            Asserts.testEqual(ins.maxSubArray(nums), 6);
        }
    }
}
