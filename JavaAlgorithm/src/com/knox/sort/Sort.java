package com.knox.sort;

import java.text.DecimalFormat;

import java.util.Arrays;
import java.util.Comparator;

public abstract class Sort<T extends Comparable<T>> implements Comparable<Sort<T>> {

    protected T[] array;
    private Comparator<T> comparator;
    private long cmpCount;
    private long swapCount;
    private long time;
    private DecimalFormat fmt = new DecimalFormat("#.00");

    public void sort(T[] array) {
        sort(array, null);
    }

    public void sort(T[] array, Comparator<T> comparator) {
        if (array == null || array.length < 2) return;
        this.array = array;
        this.comparator = comparator;
        long begin = System.currentTimeMillis();
        sort();
        time = System.currentTimeMillis() - begin;
    }

    @Override
    public int compareTo(Sort<T> o) {
        int result = (int)(time - o.time);
        if (result != 0) return result;

        result = (int)(cmpCount - o.cmpCount);
        if (result != 0) return result;

        return (int)(swapCount - o.swapCount);
    }

    protected abstract void sort();

    /*
     * 返回值等于0，代表 array[idx1] == array[idx2]
     * 返回值小于0，代表 array[idx1] < array[idx2]
     * 返回值大于0，代表 array[idx1] > array[idx2]
     */
    protected int cmp(int idx1, int idx2) {
        cmpCount++;
        if (comparator != null) {
            return comparator.compare(array[idx1], array[idx2]);
        } else  {
            return array[idx1].compareTo(array[idx2]);
        }
    }

    protected int cmp(T v1, T v2) {
        cmpCount++;
        if (comparator != null) {
            return comparator.compare(v1, v2);
        } else  {
            return v1.compareTo(v2);
        }
    }

    protected void swap(int idx1, int idx2) {
        swapCount++;
        T tmp = array[idx1];
        array[idx1] = array[idx2];
        array[idx2] = tmp;
    }

    @Override
    public String toString() {
        String timeStr = "耗时：" + (time / 1000.0) + "s(" + time + "ms)";
        String compareCountStr = "比较：" + numberString(cmpCount);
        String swapCountStr = "交换：" + numberString(swapCount);
        String stableStr = "稳定性：" + isStable();
        return "【" + getClass().getSimpleName() + "】\n"
                + stableStr + " \t"
                + timeStr + " \t"
                + compareCountStr + "\t "
                + swapCountStr + "\n"
                + "------------------------------------------------------------------";

    }

    private String numberString(long number) {
        if (number < 10000) return "" + number;

        if (number < 100000000) return fmt.format(number / 10000.0) + "万";
        return fmt.format(number / 100000000.0) + "亿";
    }

    private boolean isStable() {
        T[] array = this.array;
        Student[] students = new Student[20];
        for (int i = 0; i < students.length; i++) {
            students[i] = new Student(i * 10, 10);
        }
        sort((T[]) students);
        for (int i = 1; i < students.length; i++) {
            int score = students[i].score;
            int prevScore = students[i - 1].score;
            if (score != prevScore + 10) return false;
        }
        this.array = array;
        return true;
    }

}
