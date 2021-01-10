package com.knox.sort;


import com.knox.tools.Asserts;
import com.knox.tools.Integers;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * 思路:
 * 希尔排序把序列看做一个矩阵, 分为m列, 逐列进行排序
 *  1. m从某个数逐渐减为1
 *  2. 当m为1时, 整个序列将完全有序
 *
 * 矩阵的列取决于步长序列(step sequence)
 *  1. 比如, 步长序列为{1, 5, 19, 41, 109, ...}, 就代表依次分为109列、41列、19列、5列、1列进行排序
 *  2. 不同的步长序列, 执行效率也不同
 *  3. 希尔本人给出的步长序列是n/2^k, 比如n为16时, 步长序列是{1, 2, 4, 8}
 *
 * 希尔排序可以看做是对插入排序的改进.
 *
 * 时间复杂度:
 * 最好: O(n)
 * 最坏: O(log(n^4/3)~log(n^2))
 * 平均: 取决于步长
 *
 * 空间复杂度: O(1)
 *
 * 不稳定排序
 *
 */
public class ShellSort<T extends Comparable<T>> extends Sort<T> {

    @Override
    protected void sort() {
        List<Integer> stepSequence = shellStepSequence();
        for (Integer step : stepSequence) {
            sort(step);
        }
    }

    /**
     * 分成step列进行排序
     */
    private void sort(int step) {
        for (int col = 0; col < step; col++) {
            // 对其中的一列进行插入排序
            for (int begin = col + step; begin < array.length; begin += step) {
                T v = array[begin];
                int index = begin;
                while (index > col && cmp(array[index - 1], v) > 0) {
                    // 元素往后移动一位
                    array[index] = array[index - step];
                    index -= step;
                }
                array[index] = v;
            }
        }
    }

    private List<Integer> shellStepSequence() {
        List<Integer> sequence = new ArrayList<>();
        int step = array.length;
        while ((step = (step >> 1)) > 0) {
            sequence.add(step);
        }
        return sequence;
    }

    private List<Integer> sedgewickStepSequence() {
        List<Integer> stepSequence = new LinkedList();
        int k = 0, step = 0;
        while (true) {
            if (k % 2 == 0) {
                int pow = (int) Math.pow(2, k >> 1);
                step = 1 + 9 * (pow * pow - pow);
            } else {
                int pow1 = (int) Math.pow(2, (k - 1) >> 1);
                int pow2 = (int) Math.pow(2, (k + 1) >> 1);
                step = 1 + 8 * pow1 * pow2 - 6 * pow2;
            }
            if (step >= array.length) break;
            stepSequence.add(0, step);
            k++;
        }
        return stepSequence;
    }


    public static void main(String[] args) {
        Sort<Integer> sort = new ShellSort();
        Integer[] array = Integers.random(10000, 20, 20000);
        sort.sort(array);
        Asserts.testTrue(Integers.isAscOrder(array));
    }
}
