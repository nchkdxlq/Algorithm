package com.knox;

public class Asserts {

    public static void testTrue(boolean value) {
        try {
            if (!value) throw new Exception("testTrue: 测试未通过");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void testFalse(boolean value) {
        try {
            if (value) throw new Exception("testFalse: 测试未通过");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static <T> void testEqual(T left, T right) {
        try {
            if (left != right) throw new Exception("testEqual: 测试未通过");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}