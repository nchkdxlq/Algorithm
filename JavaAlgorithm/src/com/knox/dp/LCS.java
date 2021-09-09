package com.knox.dp;

import com.knox.tools.Asserts;

public class LCS {

    int lcs(int[] nums1, int[] nums2) {
        return lcs_v1(nums1, nums2);
    }


    int lcs_v1(int[] nums1, int[] nums2) {
        if (nums1 == null || nums2 == null || nums1.length == 0 || nums2.length == 0) return 0;
        int l1 = nums1.length;
        int l2 = nums2.length;

        // 定义状态 dp[i][j] 为nums1区间[0, i)之间与nums2区间n[0, j)的最长公共子序列
        int[][] dp = new int[l1 + 1][l2 + 1];

        for (int i = 1; i <= l1; i++) {
            for (int j = 1; j <= l2; j++) {
                // 确定状态转移方程, 区间[0, i)最后一个元素为nums1[i - 1], 区间[0, j)同理。
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else  {
                    int left = dp[i][j - 1];
                    int top = dp[i - 1][j];
                    dp[i][j] = Math.max(left, top);
                }
            }
        }

        return dp[l1][l2];
    }


    public static void main(String[] args) {
        LCS ins = new LCS();

        {
            int[] nums1 = {1, 3, 5, 9, 10};
            int[] nums2 = {1, 4, 9, 10};
            int ret = ins.lcs(nums1, nums2);
            Asserts.testEqual(ret, 3);
        }

        {
            int[] nums1 = {1, 4, 5, 9, 10};
            int[] nums2 = {1, 4, 9, 10};
            int ret = ins.lcs(nums1, nums2);
            Asserts.testEqual(ret, 4);
        }

    }
}
