package com.knox.leetcode;

import com.knox.tools.Asserts;

public class _0718_findLength {

    static class Solution {
        public int findLength(int[] nums1, int[] nums2) {
            int l1 = nums1.length;
            int l2 = nums2.length;
            // 定义状态: dp[i][j]的值表示以公共子串以nums1[i-1]结尾 和 以nums2[j-1]结尾的公共子串长度。
            int[][] dp = new int[l1 + 1][l2 + 1];
            int max = 0;
            for (int i = 1; i <= l1; i++) {
                int num1 = nums1[i - 1];
                for (int j = 1; j <= l2; j++) {
                    if (num1 == nums2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = 0;
                    }
                    if (dp[i][j] > max) {
                        max = dp[i][j];
                    }
                }
            }
            return max;
        }
    }

    public static void main(String[] args) {
        Solution ins = new Solution();

        {
            int[] num1 = {1,2,3,2,1};
            int[] num2 = {3,2,1,4,7};
            int ret = ins.findLength(num1, num2);
            Asserts.testEqual(ret, 3);
        }

        {
            int[] num1 = {0,1,1,1,1};
            int[] num2 = {1,0,1,0,1};
            int ret = ins.findLength(num1, num2);
            Asserts.testEqual(ret, 2);
        }
    }
}
