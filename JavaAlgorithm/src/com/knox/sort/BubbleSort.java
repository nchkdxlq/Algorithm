package com.knox.sort;

import com.knox.tools.Integers;
import com.knox.tools.Times;

/*
*
* 解析思路:
*
*
* 时间复杂度:
*   最好:
*   最坏:
*   平均:
* 空间复杂度:
*
* */

public class BubbleSort {

    static void bubbleSort(Integer[] array) {
        if (array == null || array.length <= 1) return;

        // begin: 每次扫描的起始下标, end: 每次扫描的结束下标
        for (int end = array.length - 1; end > 0 ; end--) {
            for (int begin = 1; begin <= end; begin++) {
                if (array[begin - 1] > array[begin]) {
                    int tmp = array[begin];
                    array[begin] = array[begin - 1];
                    array[begin - 1] = tmp;
                }
            }
        }
    }

    static void bubbleSort_v1(Integer[] array) {
        if (array == null || array.length <= 1) return;

        for (int end = array.length - 1; end > 0 ; end--) {
            // 当扫描一次结束后没有交换元素, 说明已经有序了, 不需要再扫描了
            boolean sorted = true;
            for (int begin = 1; begin <= end; begin++) {
                if (array[begin - 1] > array[begin]) {
                    int tmp = array[begin];
                    array[begin] = array[begin - 1];
                    array[begin - 1] = tmp;
                    sorted = false;
                }
            }
            if (sorted) {
                break;
            }
        }
    }

    static void bubbleSort_v2(Integer[] array) {
        if (array == null || array.length <= 1) return;

        for (int end = array.length - 1; end > 0 ; end--) {
            // 记录最后一个交换的下标, sortedIndex后面的元素已经有序, sortedIndex后面元素不需要再扫描, 达到优化目的.
            int sortedIndex = 1;
            for (int begin = 1; begin <= end; begin++) {
                if (array[begin - 1] > array[begin]) {
                    int tmp = array[begin];
                    array[begin] = array[begin - 1];
                    array[begin - 1] = tmp;
                    sortedIndex = begin;
                }
            }
            end = sortedIndex;
        }
    }


    public static void main(String[] args) {
        test_random();
        test_ascOrder();
        test_tailAscOrder();
    }

    private static void test_random() {
        Integer[] array = Integers.random(10000, 20, 200000);
        Integer[] array1 = Integers.copy(array);
        Integer[] array2 = Integers.copy(array);

        Times.test("random bubbleSort", () -> bubbleSort(array));

        Times.test("random bubbleSort_v1", () -> bubbleSort_v1(array1));

        Times.test("random bubbleSort_v2", () -> bubbleSort_v2(array2));
    }

    private static void test_ascOrder() {
        Integer[] array = Integers.ascOrder(10, 10000);
        Integer[] array1 = Integers.copy(array);
        Integer[] array2 = Integers.copy(array);

        Times.test("ascOrder bubbleSort", () -> bubbleSort(array));

        Times.test("ascOrder bubbleSort_v1", () -> bubbleSort_v1(array1));

        Times.test("ascOrder bubbleSort_v2", () -> bubbleSort_v2(array2));
    }

    private static void test_tailAscOrder() {
        // 前2000个元素无序
        Integer[] array = Integers.tailAscOrder(1, 10000, 2000);
        Integer[] array1 = Integers.copy(array);
        Integer[] array2 = Integers.copy(array);

        Times.test("tailAscOrder bubbleSort", () -> bubbleSort(array));

        Times.test("tailAscOrder bubbleSort_v1", () -> bubbleSort_v1(array1));

        Times.test("tailAscOrder bubbleSort_v2", () -> bubbleSort_v2(array2));
    }

}
