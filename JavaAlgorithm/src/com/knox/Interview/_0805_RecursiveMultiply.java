package com.knox.Interview;

import com.knox.leetcode._020_isValid;
import com.knox.tools.Asserts;

public class _0805_RecursiveMultiply {

    static class Solution {
        public int multiply(int A, int B) {
            // 取更小的值作为递归的深度
            return helper(Math.min(A, B), Math.max(A, B));
        }

        private int helper(int n, int number) {
            if (n == 1) return number;
            return helper(n - 1, number) + number;
        }
    }


    public static void main(String[] args) {
        Solution ins = new Solution();

        {
            Asserts.testEqual(ins.multiply(3, 4), 12);
        }

        {
            Asserts.testEqual(ins.multiply(1, 10), 10);
        }
    }
}
