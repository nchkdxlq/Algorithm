package com.knox.sort;

import com.knox.tools.Asserts;
import com.knox.tools.Integers;
import com.knox.tools.Times;

/**
*
* 解析思路:
*
*
* 时间复杂度:
*   最好: O(n)
*   最坏: O(n^2)
*   平均: O(n^2)
*
* 空间复杂度: O(1)
*
* */

public class BubbleSort<T extends Comparable<T>> extends Sort<T> {

    @Override
    protected void sort() {
        bubbleSort_v2(array);
    }

    void bubbleSort(T[] array) {
        if (array == null || array.length <= 1) return;
        this.array = array;

        // begin: 每次扫描的起始下标, end: 每次扫描的结束下标
        for (int end = array.length - 1; end > 0 ; end--) {
            for (int begin = 1; begin <= end; begin++) {
                if (cmp(begin - 1, begin) > 0) {
                    swap(begin - 1, begin);
                }
            }
        }
    }

    void bubbleSort_v1(T[] array) {
        if (array == null || array.length <= 1) return;
        this.array = array;

        for (int end = array.length - 1; end > 0 ; end--) {
            // 当扫描一次结束后没有交换元素, 说明已经有序了, 不需要再扫描了
            boolean sorted = true;
            for (int begin = 1; begin <= end; begin++) {
                if (cmp(begin - 1, begin) > 0) {
                    swap(begin - 1, begin);
                    sorted = false;
                }
            }
            if (sorted) {
                break;
            }
        }
    }

    void bubbleSort_v2(T[] array) {
        if (array == null || array.length <= 1) return;
        this.array = array;

        for (int end = array.length - 1; end > 0 ; end--) {
            // 记录最后一个交换的下标, sortedIndex后面的元素已经有序, sortedIndex后面元素不需要再扫描, 达到优化目的.
            int sortedIndex = 1;
            for (int begin = 1; begin <= end; begin++) {
                if (cmp(begin - 1, begin) > 0) {
                    swap(begin - 1, begin);
                    sortedIndex = begin;
                }
            }
            end = sortedIndex;
        }
    }

    public static void main(String[] args) {
        BubbleSort<Integer> sort = new BubbleSort();
        test_random(sort);
        test_ascOrder(sort);
        test_tailAscOrder(sort);
    }

    private static void test_random(BubbleSort sort) {
        Integer[] array = Integers.random(10000, 20, 200000);
        Integer[] array1 = Integers.copy(array);
        Integer[] array2 = Integers.copy(array);

        Times.test("random bubbleSort", () -> sort.bubbleSort(array));
        Times.test("random bubbleSort_v1", () -> sort.bubbleSort_v1(array1));
        Times.test("random bubbleSort_v2", () -> sort.bubbleSort_v2(array2));

        Asserts.testTrue(Integers.isAscOrder(array));
        Asserts.testTrue(Integers.isAscOrder(array1));
        Asserts.testTrue(Integers.isAscOrder(array2));
    }

    private static void test_ascOrder(BubbleSort sort) {
        Integer[] array = Integers.ascOrder(10, 10000);
        Integer[] array1 = Integers.copy(array);
        Integer[] array2 = Integers.copy(array);

        Times.test("ascOrder bubbleSort", () -> sort.bubbleSort(array));
        Times.test("ascOrder bubbleSort_v1", () -> sort.bubbleSort_v1(array1));
        Times.test("ascOrder bubbleSort_v2", () -> sort.bubbleSort_v2(array2));
        Asserts.testTrue(Integers.isAscOrder(array));
        Asserts.testTrue(Integers.isAscOrder(array1));
        Asserts.testTrue(Integers.isAscOrder(array2));
    }

    private static void test_tailAscOrder(BubbleSort sort) {
        // 前2000个元素无序
        Integer[] array = Integers.tailAscOrder(1, 10000, 2000);
        Integer[] array1 = Integers.copy(array);
        Integer[] array2 = Integers.copy(array);

        Times.test("tailAscOrder bubbleSort", () -> sort.bubbleSort(array));
        Times.test("tailAscOrder bubbleSort_v1", () -> sort.bubbleSort_v1(array1));
        Times.test("tailAscOrder bubbleSort_v2", () -> sort.bubbleSort_v2(array2));
        Asserts.testTrue(Integers.isAscOrder(array));
        Asserts.testTrue(Integers.isAscOrder(array1));
        Asserts.testTrue(Integers.isAscOrder(array2));
    }
}
