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

    public static void testEqual(Object left, Object right) {
        try {
            if (left != right) throw new Exception("testEqual: 测试未通过");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void testNull(Object obj) {
        try {
            if (obj != null) throw new Exception("testNull: 测试未通过");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void testNonNull(Object obj) {
        try {
            if (obj == null) throw new Exception("testNonNull: 测试未通过");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}