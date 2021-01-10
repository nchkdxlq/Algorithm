package com.knox.sort;

import com.knox.tools.Asserts;
import com.knox.tools.Integers;

public class CountingSort extends Sort<Integer> {

    @Override
    protected void sort() {
        sort_v2();
    }

    /**
     * 缺点：
     *  1. 极其浪费内存空间, 需要分配元素最大值max+1的内存空间, 比如数组之后10个元素, 但最大值为1000.
     *  2. 不能排序负数, 因为数组的下标不能为负数
     *  3. 不稳定排序
     */
    private void sort_v1() {
        int length = array.length;
        // 找出最大值
        Integer max = array[0];
        for (int i = 1; i < length; i++) {
            if (cmp(array[i], max) > 0) {
                max = array[i];
            }
        }

        // 分配内存空间,存储元素出现的次数, 默认数组中的元素为0
        int[] counts = new int[max + 1];
        // 记录每个元素出现的次数
        for (Integer v : array) {
            counts[v]++;
        }

        // 根据计数排序数组
        int index = 0;
        for (int i = 0; i <= max; i++) {
            int count = counts[i]; // count表示元素出现的次数
            while (count > 0) {
                array[index++] = i;
                count--;
            }
        }
    }

    private void sort_v2() {
        int length = array.length;
        // 找出最小、大值
        Integer min = array[0];
        Integer max = array[0];
        for (int i = 1; i < length; i++) {
            if (array[i] > max) {
                max = array[i];
            }
            if (array[i] < min) {
                min = array[i];
            }
        }

        // 分配内存空间,存储元素出现的次数, 默认数组中的元素为0
        int countLength = max - min + 1;
        int[] counts = new int[countLength];
        // 记录每个元素出现的次数
        for (Integer v : array) {
            counts[v-min]++;
        }

        // 累加次数
        for (int i = 1; i < countLength; i++) {
            counts[i] += counts[i - 1];
        }

        // 从后往前遍历, 把元素放到合适的位置
        Integer[] newArray = new Integer[array.length];
        for (int i = array.length - 1; i >= 0 ; i--) {
            Integer v = array[i];
            int count = counts[v-min] - 1;
            counts[v-min] = count;
            newArray[count] = v;
        }

        // 有序数组覆盖原数组
        for (int i = 0; i < length; i++) {
            array[i] = newArray[i];
        }
    }

    public static void main(String[] args) {
        Sort<Integer> sort = new CountingSort();
        Integer[] array = Integers.random(10, 20, 100);
        sort.sort(array);
        Asserts.testTrue(Integers.isAscOrder(array));
    }
}
