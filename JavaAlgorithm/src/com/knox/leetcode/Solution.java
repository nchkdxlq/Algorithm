package com.knox.leetcode;

import java.util.*;

class Solution {
    private int[] getLeastNumbers(int[] arr, int k) {
        if (k == 0) return new int[0];
        quickSelect(arr, 0, arr.length-1, k-1);
        return Arrays.copyOf(arr, k);
    }

    private void quickSelect(int[] arr, int left, int right, int index) {
        if (left >= right || left > index) return;

        int p = partition(arr, left, right);
        if (index < p) {
            quickSelect(arr, 0, p-1, index);
        }
    }

    private int partition(int[] arr, int left, int right) {
//        int randomIndex = left + (int)(Math.random()*(right - left));
//        swap(arr, left, randomIndex);
        int v = arr[left];
        int i = left + 1;
        int j = right;
        while (true) {
            while (i <= j && arr[i] < v) i++;
            while (i <= j && arr[j] > v) j--;
            if (i > j) break;

            swap(arr, i++, j--);
        }
        swap(arr, left, j);

        return j;
    }

    private void swap(int[] arr, int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    public static void main(String[] args) {
        Deque<Integer> queue = new LinkedList<>();
        queue.peekLast();
        String str = "";


        PriorityQueue<Integer> minHeap = new PriorityQueue<>((x, y) -> x - y);
        minHeap.offer(10);
        minHeap.poll();
    }
}