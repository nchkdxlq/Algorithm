package com.knox.recursion;

import com.knox.tools.Times;

import java.sql.Time;

public class Fib {


    private static int fib_v0(int n) {
        if (n <= 1) return n;

        return fib_v0(n - 1) + fib_v0(n - 2);
    }

    private static int fib_v1(int n) {
        if (n <= 1) return n;

        int[] fibArray = new int[n + 1];
        fibArray[1] = fibArray[2] = 1;
        return fib_v1(n, fibArray);
    }

    // 对 fib_v0的优化, 利用数组缓存计算的结果
    private static int fib_v1(int n, int[] fibArray) {
        if (fibArray[n] == 0) {
            fibArray[n] = fib_v1(n - 1, fibArray) + fib_v1(n - 2, fibArray);
        }
        return fibArray[n];
    }

    /**
     * 对 fib_v1的优化, 利用循环优化递归调用的栈空间
     * 是"自底向上"的计算过程, 递归创维非递归常用技巧
     *
     * 时间复杂度: O(n)
     * 空间复杂度: O(n)
     */
    private static int fib_v2(int n) {
        if (n <= 1) return n;

        int[] fibArray = new int[n + 1];
        fibArray[1] = fibArray[2] = 1;
        int i = 3;
        while (i <= n) {
            fibArray[i] = fibArray[i - 1] + fibArray[i - 2];
            i++;
        }
        return fibArray[n];
    }

    /**
     * 利用滚动数组, 只使用到数组的连续几个元素
     * 时间复杂度: O(n)
     * 空间复杂度: O(1)
     */
    private static int fib_v3(int n) {
        if (n <= 1) return n;

        int[] fibArray = new int[2];
        fibArray[0] = fibArray[1] = 1;
        int i = 3;
        // 可以把 % 2 操作写为 & 1
        while (i <= n) {
            fibArray[i % 2] = fibArray[(i - 1) % 2] + fibArray[(i - 2) % 2];
            i++;
        }
        return fibArray[n % 2];
    }

    private static int fib_v4(int n) {
        if (n <= 1) return n;

        int first = 1;
        int second = 1;
        int tmp;
        int i = 3;
        while (i <= n) {
            tmp = second;
            second = first + second;
            first = tmp;
            i++;
        }
        return second;
    }


    public static void main(String[] args) {
        int n = 43;

        Times.test("fib_v0", () -> {
            int ret0 = fib_v0(n);
            System.out.println(ret0);
        });

        Times.test("fib_v1", () -> {
            int ret1 = fib_v1(n);
            System.out.println(ret1);
        });

        Times.test("fib_v2", () -> {
            int ret2 = fib_v2(n);
            System.out.println(ret2);
        });

        Times.test("fib_v3", () -> {
            int ret = fib_v3(n);
            System.out.println(ret);
        });

        Times.test("fib_v4", () -> {
            int ret = fib_v4(n);
            System.out.println(ret);
        });
    }
}
