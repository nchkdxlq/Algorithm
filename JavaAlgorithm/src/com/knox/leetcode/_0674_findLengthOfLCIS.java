package com.knox.leetcode;

import com.knox.tools.Asserts;

import java.util.Arrays;

public class _0674_findLengthOfLCIS {

     static class Solution {
        public int findLengthOfLCIS(int[] nums) {
            return findLengthOfLCIS_v2(nums);
        }

         /**
          * 思路: 使用动态规划思想, 算出以nums[i]为结尾的联系递增子序列的长度dp[i],
          * 然后取dp[i]的最大值。
          * 时间复杂度: O(n)
          * 空间复杂度: O(n)
          */
        private int findLengthOfLCIS_v1(int[] nums) {
            if (nums.length <= 1) return nums.length;

            // dp存储的是以nums[i]结尾的子序列连续递增子序列的长度
            int[] dp = new int[nums.length];
            // 一个元素本身就是递增子序列, 所以默认为1
            Arrays.fill(dp, 1);
            int max = dp[0];
            for (int i = 1; i < nums.length; i++) {
                if (nums[i] > nums[i - 1]) {
                    dp[i] = dp[i - 1] + 1;
                    max = Math.max(dp[i], max);
                }
            }
            return max;
        }

         /**
          * 思路:
          *   对v1版本解法的优化, 在状态转移方程中dp[i] = dp[i - 1] + 1, 求dp[i]只需要用到前一项的值,
          *   使用两个变量记录dp[i]和dp[i-1]就可以, 不需要分配一个数组, 达到空间的优化。
          * 时间复杂度: O(n)
          * 空间复杂度: O(n)
          */
         private int findLengthOfLCIS_v2(int[] nums) {
             if (nums.length <= 1) return nums.length;

             int maxLength = 1; //最长增长子序列长度
             int preLength = 1; // 第一个元素默认就是升序子序列, 长度为1
             for (int i = 1; i < nums.length; i++) {
                 if (nums[i] > nums[i - 1]) {
                     preLength += 1;
                     maxLength = Math.max(preLength, maxLength);
                 } else  {
                     // 当nums[i] >= nums[i - 1]时, nums[i]是一个新开始的自增子序列, 所以preLength = 1
                     preLength = 1;
                 }
             }
             return maxLength;
         }

    }


    public static void main(String[] args) {
        Solution ins = new Solution();

        {
            int[] nums = {1,3,5,4,7};
            int res = ins.findLengthOfLCIS(nums);
            Asserts.testEqual(res, 3);
        }

        {
            int[] nums = {2,2,2,2,2};
            int res = ins.findLengthOfLCIS(nums);
            Asserts.testEqual(res, 1);
        }
    }
}
