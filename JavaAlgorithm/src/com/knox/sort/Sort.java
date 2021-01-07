package com.knox.sort;

public abstract class Sort {

    protected Integer[] arrary;
    private int cmpCount;
    private int swapCount;

    public void sort(Integer[] array) {
        if (array == null || array.length < 2) return;
        this.arrary = array;
        sort();
    }

    protected abstract void sort();

    protected int cmp(Integer v1, Integer v2) {
        cmpCount++;
        return v1 - v2;
    }

    protected void swap(int idx1, int idx2) {
        cmpCount++;
        Integer tmp = arrary[idx1];
        arrary[idx1] =arrary[idx2];
        arrary[idx2] = tmp;
    }
}
