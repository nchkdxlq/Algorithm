package com.knox.sort;

import com.knox.tools.Asserts;
import com.knox.tools.Integers;


/*
 *
 * 思路：
 * 可以看做是对选择排序的一种优化
 * 1. 对数组原地建堆
 * 2. 堆顶元素与堆尾元素交换
 * 3. 堆size - 1
 * 4. 从index == 0 开始下滤, 恢复堆性质
 * 5. 循环执行2、3、4直到堆size == 0 循环结束
 * 时间复杂度:
 *   最好: O(nlogn)
 *   最坏: O(nlogn)
 *   平均: O(nlogn)
 *
 * */
public class HeapSort<T extends Comparable<T>> extends Sort<T> {
    private int heapSize;

    @Override
    protected void sort() {
        heapify();
        while (heapSize > 0) {
            // heapify之后, 第一个元素为最大值
            swap(0, --heapSize);

            shiftDown(0);
        }
    }

    private void heapify() {
        heapSize = array.length;
        // 自下而上的下滤, 从最后一个非叶子节点开始下滤
        int index = (heapSize >> 1) - 1;
        for (int i = index; i >=0 ; i--) {
            shiftDown(i);
        }
    }

    private void shiftDown(int index) {
        int half = heapSize >> 1; // half等与第一个叶子节点的索引
        T element = array[index];
        while (index < half) {
            int maxIndex = (index << 1) + 1;
            T max = array[maxIndex];
            int rightIndex = maxIndex + 1;
            if (rightIndex < heapSize && cmp(array[rightIndex], max) > 0) {
                maxIndex = rightIndex;
                max = array[rightIndex];
            }
            if (cmp(max, element) > 0) {
                array[index] = max;
                index = maxIndex;
            } else {
                break;
            }
        }
        array[index] = element;
    }

    public static void main(String[] args) {
        Sort<Integer> sort = new HeapSort();
        Integer[] array = Integers.random(10000, 20, 20000);
        sort.sort(array);
        Asserts.testTrue(Integers.isAscOrder(array));
    }
}
