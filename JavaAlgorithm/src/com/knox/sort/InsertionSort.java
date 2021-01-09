package com.knox.sort;

import com.knox.tools.Asserts;
import com.knox.tools.Integers;

public class InsertionSort<T extends Comparable<T>> extends Sort<T> {

    @Override
    protected void sort() {
        sort_v3();
    }

    private void sort_v1() {
        for (int begin = 1; begin < array.length; begin++) {
            int cur = begin;
            while (cur > 0 && cmp(cur - 1, cur) > 0) {
                swap(cur - 1, cur);
                cur--;
            }
        }
    }

    private void sort_v2() {
        for (int begin = 1; begin < array.length; begin++) {
            T v = array[begin];
            int index = begin;
            while (index > 0 && cmp(array[index - 1], v) > 0) {
                array[index] = array[index - 1];
                index--;
            }
            array[index] = v;
        }
    }

    private void sort_v3() {
        for (int begin = 1; begin < array.length; begin++) {
            T v = array[begin];
            // 找到元素的插入位置
            int index = insertIndex(begin);
            // 把[index, begin)区间的元素往后移动一个位置
            for (int i = begin; i > index ; i--) {
                array[i] = array[i - 1];
            }
            array[index] = v;
        }
    }

    private int insertIndex(int index) {
        T v = array[index];
        int begin = 0;
        int end = index;
        while (begin < end) {
            int mid = (begin + end) >> 1;
            if (cmp(v, array[mid]) < 0) {
                end = mid;
            } else { // v >= array[mid]
                begin = mid + 1;
            }
        }

        return begin;
    }

    public static void main(String[] args) {
        Sort<Integer> sort = new InsertionSort<>();
        Integer[] array = Integers.random(10000, 20, 20000);
        // Integer[] array = Integers.random(10, 20, 100);
        sort.sort(array);
        Asserts.testTrue(Integers.isAscOrder(array));
    }
}
