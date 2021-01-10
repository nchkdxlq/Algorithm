package com.knox.sort;


import com.knox.tools.Asserts;
import com.knox.tools.Integers;


public class MergeSort<T extends Comparable<T>> extends Sort<T> {

    // 用于在合并时存储左边的元素
    private T[] leftArray;

    @Override
    protected void sort() {
        leftArray = (T[]) new Comparable[array.length >> 1];
        sort(0, array.length);
    }

    /*
    * 对数组区间为[begin, end)的元素进行排序
    * */
    private void sort(int begin, int end) {
        // 小于2个元素递归结束
        if (end - begin < 2) return;

        int mid = (begin + end) >> 1;
        sort(begin, mid);
        sort(mid, end);
        merge(begin, mid, end);
    }

    /*
    * 对区间[begin, mid)、 [mid, end)元素合并
    * */
    private void merge(int begin, int mid, int end) {
        // 先copy左侧元素
        int leftLength = mid - begin;
        for (int i = 0; i < leftLength; i++) {
            leftArray[i] = array[begin + i];
        }

        int leftIndex = 0; // 左侧元素在leftArray数组中的下标
        int rightIndex = mid; // 右侧元素在array中的下标
        int arrayIndex = begin; //

        while (leftIndex < leftLength) {
            if (rightIndex < end && cmp(array[rightIndex], leftArray[leftIndex]) < 0) {
                array[arrayIndex++] = array[rightIndex++];
            } else {
                array[arrayIndex++] = leftArray[leftIndex++];
            }
        }
    }


    public static void main(String[] args) {
        Sort<Integer> sort = new MergeSort();
        Integer[] array = Integers.random(10000, 20, 20000);
        // Integer[] array = Integers.random(10, 20, 100);
        sort.sort(array);
        Asserts.testTrue(Integers.isAscOrder(array));
    }
}
