package com.knox.leetcode;


import com.knox.leetcode.List.ListHelper;
import com.knox.tools.Asserts;

import java.util.ArrayList;
import java.util.List;

/**
 * 120. 三角形最小路径和
 *  给定一个三角形 triangle ，找出自顶向下的最小路径和。
 *
 * 每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
 * 也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。
 *
 * https://leetcode-cn.com/problems/triangle/
 *
 * */
public class _0120_minimumTotal {

    static class Solution {
        public int minimumTotal(List<List<Integer>> triangle) {
            return minimumTotal_v3(triangle);
        }

        /**
         *  递归方式
         *  result(i, j) = Min( result(i + 1, j), result(i + 1, j + 1) );
         *
         *  triangle[i][j]这个位置到达最底层的最小路径为 triangle[i+1][j]位置 triangle[i+1][j+1]位置到最底部路径两者的最小值,
         *  在加上数组元素triangle[i][j]的值. 问题的规模不断的减小,所以可以使用递归求解
         *
         *  递归结束条件
         *  保证数组不越界即 row == triangle.size() || triangle.get(row).size() == col
         *
         *  时间复杂度: O(2^n)  2^0 + 2^1 + 2^2 + ... + 2^(n-1)
         *  空间复杂度: O(n) 递归的深度, n为数组的长度
         *
         *  存在的问题
         *  如果把递归树画出来, 会发现在整个求解的过程中, 存在大量的重复计算, 所以可以使用记忆化搜索缓存计算过的结果.
         *
         */
        private int minimumTotal_v1(List<List<Integer>> triangle) {
            return minimumTotal_v1(triangle, 0, 0);
        }

        private int minimumTotal_v1(List<List<Integer>> triangle, int row, int col) {
            if (row == triangle.size() || triangle.get(row).size() == col) {
                return 0;
            }

            int ret1 = minimumTotal_v1(triangle, row + 1, col);
            int ret2 = minimumTotal_v1(triangle, row + 1, col + 1);
            return Math.min(ret1, ret2) + triangle.get(row).get(col);
        }

        private Integer[][] min;
        private int minimumTotal_v2(List<List<Integer>> triangle) {
            min = new Integer[triangle.size()][triangle.size()];
            return minimumTotal_v1(triangle, 0, 0);
        }

        /**
         *  对v1版本的优化, 利用记忆化搜索缓存计算的结果, 避免重复计算
         *
         *  时间复杂度: O(n) n为二维数组的个数
         *  空间复杂度: O(n) n为二维数组的个数
         *
         * */
        private int minimumTotal_v2(List<List<Integer>> triangle, int row, int col) {
            if (row == triangle.size() || triangle.get(row).size() == col) {
                return 0;
            }
            if (min[row][col] == null) {
                int ret1 = minimumTotal_v2(triangle, row + 1, col) ;
                int ret2 = minimumTotal_v2(triangle, row + 1, col + 1);
                min[row][col] = Math.min(ret1, ret2) + triangle.get(row).get(col);
            }
            return min[row][col];
        }


        /**
         *
         *
         *
         * */
        private int minimumTotal_v3(List<List<Integer>> triangle) {
            int size = triangle.size();
            // 定义状态, dp[i][j]表示从triangle[i][j]位置到最底层的最小路径和
            int[][] dp = new int[size][size];

            // 初始状态值, 最后一行元素本身就是最后一行到最后一行的最小路径
            List<Integer> lastRow = triangle.get(size - 1);
            for (int i = 0; i < size; i++) {
                dp[size - 1][i] = lastRow.get(i);
            }

            for (int i = size - 2; i >= 0; i--) {
                List<Integer> row = triangle.get(i);
                for (int j = 0; j < row.size(); j++) {
                    // 状态转移方程
                    dp[i][j] = Math.min(dp[i+1][j], dp[i+1][j+1]) + row.get(j);
                }
            }
            return dp[0][0];
        }

    }


    public static void main(String[] args) {
        Solution ins = new Solution();

        {
            int[][] triangle = { {2}, {3,4}, {6,5,7}, {4,1,8,3} };
            List<List<Integer>> list = ListHelper.listFromArray(triangle);
            int ret = ins.minimumTotal(list);
            Asserts.testEqual(ret, 11);
        }

        {
            int[][] triangle = {{-10}};
            List<List<Integer>> list = ListHelper.listFromArray(triangle);
            int ret = ins.minimumTotal(list);
            Asserts.testEqual(ret, -10);
        }
    }

}
