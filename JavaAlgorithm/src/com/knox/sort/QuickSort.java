package com.knox.sort;

import com.knox.tools.Asserts;
import com.knox.tools.Integers;

/**
 * 思路:
 *  ① 在序列中选择一个轴点元素(pivot), 假设每次选择0位置元素为轴点元素
 *  ② 利用pivot将序列分为两个子序列
 *     2.1 将小于pivot的元素放在pivot的前后(左侧)
 *     2.2 将大于pivot的元素放在pivot的后面(右侧)
 *     2.3 等于pivot的元素放在左右任意一侧都可以
 *  ③ 对子序列进行①②操作, 把子序列分为更小的子序列, 直到子序列中只剩下一个元素。
 *
 * 快速排序的本质: 逐渐将每一个元素都转换位轴点元素.
 *
 * 时间复杂度:
 *  最好: O(nlog(n))
 *  最坏: O(n^2)
 *  平均: O(nlog(n))
 *
 * 空间复杂度: O(log(n)) 递归调用的层数
 *
 * 不稳定排序
 * */
public class QuickSort<T extends Comparable<T>> extends Sort<T> {

    @Override
    protected void sort() {
        sort(0, array.length);
    }

    /**
     * 对[begin, end) 区间的元素进行快速排序
     * @param begin
     * @param end
     */
    private void sort(int begin, int end) {
        if (end - begin < 2) return;

        int pivot = pivotIndex(begin, end);
        sort(begin, pivot);
        sort(pivot + 1, end);
    }

    /**
     * 构造出 [begin, end) 区间元素的轴点元素下标
     * @param begin
     * @param end
     * @return 轴点元素的下标
     */
    private int pivotIndex(int begin, int end) {
        // 在[begin, end)区间随机选着一个轴点元素
        int randomIndex = begin + (int)(Math.random() * (end - begin));
        swap(begin, randomIndex);
        T pivot = array[begin];
        end--; // end指向最后一个元素

        // 如果 cmp(array[end], pivot) > 0 / cmp(array[begin], pivot) < 0 包含等于,
        // 会使得pivot把左右子序列划分的极度不均匀, 增加时间复杂度，最坏情况为O(n^2).
        while (begin < end) {
            // 从右边扫描
            while (begin < end) {
                if (cmp(array[end], pivot) > 0) { // 把 > pivot的元素放右边
                    end--;
                } else { // <= pivot的元素放左边
                    array[begin++] = array[end];
                    break;
                }
            }
            // 从左边扫描
            while (begin < end) {
                if (cmp(array[begin], pivot) < 0) { // 把 < pivot的元素放左边
                    begin++;
                } else { // >= pivot的元素放右边
                    array[end--] = array[begin];
                    break;
                }
            }
        }
        // 将轴点元素放入最终位置
        array[begin] = pivot;
        return begin;
    }

    public static void main(String[] args) {
        Sort<Integer> sort = new QuickSort();
        Integer[] array = Integers.random(10000, 20, 20000);
        // Integer[] array = Integers.random(10, 20, 100);
        sort.sort(array);
        Asserts.testTrue(Integers.isAscOrder(array));
    }
}
