package com.knox.leetcode;

import com.knox.tools.Asserts;

public class _0300_lengthOfLIS {
    static class Solution {

        public int lengthOfLIS(int[] nums) {
            return lengthOfLIS_v1(nums);
        }

        /**
         * 动态规划：
         * 时间复杂度: O(n^2)
         * 空间复杂度: O(n)
         */
        public int lengthOfLIS_v1(int[] nums) {
            int length = nums.length;
            if (length <= 1) return length;

            // 定义状态: dp[i]是为以nums[i]结尾的递增子序列的长度
            int[] dp = new int[length];
            // 设定初始状态
            dp[0] = 1;
            int max = dp[0];
            for (int i = 1; i < length; i++) {
                dp[i] = 1;
                // 状态转义方程
                for (int j = 0; j < i; j++) {
                    if (nums[j] < nums[i]) {
                        dp[i] = Math.max(dp[j] + 1, dp[i]);
                    }
                }
                if (dp[i] > max) {
                    max = dp[i];
                }
            }
            return max;
        }



    }

    public static void main(String[] args) {
        Solution ins = new Solution();
        {
            int[] nums = {10,9,2,5,3,7,101,18};
            int ret = ins.lengthOfLIS(nums);
            Asserts.testEqual(ret, 4);
        }

        {
            int[] nums = {};
            int ret = ins.lengthOfLIS(nums);
            Asserts.testEqual(ret, 0);
        }

        {
            int[] nums = {4};
            int ret = ins.lengthOfLIS(nums);
            Asserts.testEqual(ret, 1);
        }

        {
            int[] nums = {7,7,7,7,7,7,7};
            int ret = ins.lengthOfLIS(nums);
            Asserts.testEqual(ret, 1);
        }
    }
}
