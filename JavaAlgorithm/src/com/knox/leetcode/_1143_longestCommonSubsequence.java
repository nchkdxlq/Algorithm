package com.knox.leetcode;


import com.knox.tools.Asserts;

/**
 * 1143. 最长公共子序列
 * 给定两个字符串text1 和text2，返回这两个字符串的最长公共子序列的长度。
 *
 * 一个字符串的子序列是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
 * 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。
 *
 * 若这两个字符串没有公共子序列，则返回 0。
 *
 *  https://leetcode-cn.com/problems/longest-common-subsequence/
 */
public class _1143_longestCommonSubsequence {

    static class Solution {
        public int longestCommonSubsequence(String text1, String text2) {
            return longestCommonSubsequence_v1(text1, text2);
        }


        public int longestCommonSubsequence_v1(String text1, String text2) {
            if (text1 == null || text2 == null || text1.isEmpty() || text2.isEmpty()) return 0;

            int l1 = text1.length();
            int l2 = text2.length();
            // 定义状态 dp[i][j]表示text1区间[0, i)和text2区间[0, j)最长公共子串
            int[][] dp = new int[l1 + 1][l2 + 1];

            for (int i = 1; i <= l1; i++) {
                char ch1 = text1.charAt(i - 1);
                for (int j = 1; j <= l2; j++) {
                    if (ch1 == text2.charAt(j - 1)) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else  {
                        int top = dp[i - 1][j];
                        int left = dp[i][j - 1];
                        dp[i][j] = Math.max(top, left);
                    }
                }
            }

            return dp[l1][l2];
        }
    }


    public static void main(String[] args) {
        Solution ins = new Solution();

        String text1 = "abcde";
        String text2 = "ace";
        int ret = ins.longestCommonSubsequence(text1, text2);
        Asserts.testEqual(ret, 3);
    }
}
