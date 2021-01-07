package com.knox.sort;

import com.knox.tools.Asserts;
import com.knox.tools.Integers;

/*
*
* 思路：
* 从无序区间选出最大的元素，放到无序区间的最后一个位置, 无序区间索引index - 1
* 时间复杂度:
*   最好: O(n^2)
*   最坏: O(n^2)
*   平均: O(n^2)
*
* */
public class SelectionSort extends Sort {

    @Override
    protected void sort() {
        for (int end = arrary.length - 1; end > 0; end--) {
            int maxIndex = 0;
            for (int begin = 1; begin <= end; begin++) {
                if (cmp(arrary[begin], arrary[maxIndex]) > 0) {
                    maxIndex = begin;
                }
            }
            swap(maxIndex, end);
        }
    }


    public static void main(String[] args) {
        Sort sort = new SelectionSort();
        Integer[] array = Integers.random(10000, 20, 20000);
        sort.sort(array);
        Asserts.testTrue(Integers.isAscOrder(array));
    }
}
