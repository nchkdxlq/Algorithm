package com.knox.util;

public class Util {

    public final static boolean safeEqual(Object left, Object right) {
        if (left == null && right == null) return true;

        // 其中一个为空
        if (left == null || right == null) return false;

        // left right 类型相等，且值也相等才为true
        return left.getClass().equals(right.getClass()) && left.equals(right);
    }
}
