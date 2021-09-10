package com.knox.leetcode;

import java.util.Arrays;

public class _0509_fib {

    static class Solution {
        public int fib(int n) {
//            return fib_v1(n);
            return fib_v2(n);
        }

        /**
         *  递归解法, 自顶向下的解决问题,
         *  存在的问题：存在大量重复计算
         *
         */
        private int fib_v1(int n) {
            if (n <= 1) return n;
            return fib_v1(n-1) + fib_v1(n - 2);
        }

        int[] memo;
        private int fib_v2(int n) {
            if (n <= 1) return n;
            memo = new int[n+1];
            Arrays.fill(memo, -1);
            return fib_v2_helper(n);
        }

        private int fib_v2_helper(int n) {
            if (n <= 1) return n;
            if (memo[n] == -1) {
                memo[n] = fib_v2_helper(n - 1) + fib_v2_helper(n - 2);
            }
            return memo[n];
        }

        /**
         *  先解决最小数据时的结果，然后通过递推，得到大规模时的结果.
         */
        private int fib_v3(int n) {
            int[] dp = new int[n+1];
            dp[0] = 0;
            dp[1] = 1;
            for (int i = 2; i <= n; i++) {
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            return dp[n];
        }
    }


    public static void main(String[] args) {
        Solution ins = new Solution();
        int ans = ins.fib(20);
        System.out.println(ans);
    }
}
