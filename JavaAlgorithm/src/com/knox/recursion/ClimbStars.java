package com.knox.recursion;

public class ClimbStars {

    /**
     *  思路: 与斐波那契数列求解思路一致
     *  f(n) = f(n - 1) + f(n - 2)
     */
    static int climbStars(int n) {
        if (n <= 2) return n;
        int first = 1;
        int second = 2;

        for (int i = 3; i <= n; i++) {
            second = first + second;
            first = second - first;
        }
        return second;
    }

    public static void main(String[] args) {
        int ret = climbStars(10);
        System.out.println(ret);
    }
}
