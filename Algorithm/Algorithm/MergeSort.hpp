//
//  MergeSort.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/22.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef MergeSort_hpp
#define MergeSort_hpp

#include <stdio.h>
#include "InsertionSort.hpp"


// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template <typename T>
void __merge(T arr[], int l, int mid, int r) {
    
    T aux[r-l+1];
    for (int i = l; i <= r; i++) {
        aux[i-l] = arr[i];
    }
    
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = aux[j-l];
            j++;
        } else if (j > r) {
            arr[k] = aux[i-l];
            i++;
        } else if (aux[i-l] < aux[j-l]) {
            arr[k] = aux[i-l];
            i++;
        } else {
            arr[k] = aux[j-l];
            j++;
        }
    }
}


////////////////////////////////////////////////////

/**
 
 自顶向下的归并排序
 
 */


// 递归使用归并排序，对arr[l...r]的范围进行排序
template <typename T>
void __mergeSort(T arr[], int l, int r) {
    
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    __merge(arr, l, mid, r);
}

template <typename T>
void mergeSort(T arr[], int length) {
    __mergeSort(arr, 0, length-1);
}


////////////////////////////////////////////////////


/*
 优化方案一：
 优化思路
 1. 当数组的元素的比较少时，数据近乎有序的可能性, 利用InsertionSort对近乎有序的数组排序的时间复杂度为 O(n) .
 2. 当 arr[mid] < arr[mid+1] 时， arr[l...r]区间的元素已经有序，不需要再进行merge .
 基于上面两点考虑，对归并排序就行优化。
 */

template<typename T>
void __mergeSort_v1(T arr[], int l, int r)
{
    if (r - l < 15) {
        // 优化点一
        __insertionSort(arr, l, r);
        return;
    }
    
    int mid = (l + r) / 2;
    __mergeSort_v1(arr, l, mid);
    __mergeSort_v1(arr, mid+1, r);
    // 优化点二
    if (arr[mid] > arr[mid+1]) {
        __merge(arr, l, mid, r);
    }
}


template <typename T>
void mergeSort_v1(T arr[], int length) {
    __mergeSort_v1(arr, 0, length-1);
}


////////////////////////////////////////////////////
/*
 自底向上的归并排序
 取下标连续的数组元素个数为size的两个子数组，对这两个子数组进行归并。
 size的初始值和增量为：size = 1, size = size + size;
 
 */

template <typename T>
void mergeSortBU(T arr[], int length) {
    
    for (int size = 1; size < length; size += size) {
        for (int i = 0; i+size < length; i += 2*size) {
            __merge(arr, i, (i+size-1), min((i+size+size-1), length-1));
        }
    }
}


/*
 优化方案一：
 优化思路
 1. 当数组的元素的比较少时，数据近乎有序的可能性, 利用InsertionSort对近乎有序的数组排序的时间复杂度为 O(n) .
 2. 当 arr[mid] < arr[mid+1] 时， arr[l...r]区间的元素已经有序，不需要再进行merge .
 基于上面两点考虑，对归并排序就行优化。
 */
template <typename T>
void mergeSortBU_v1(T arr[], int length) {
    
    for (int size = 1; size < length; size += size) {
        for (int i = 0; i+size < length; i += 2*size) {
            
            if (size < 8) {
                __insertionSort(arr, i, min((i+size+size-1), length-1));
            } else {
                if (arr[i+size-1] > arr[i+size]) {
                    __merge(arr, i, (i+size-1), min((i+size+size-1), length-1));
                }
            }
        }
    }
}


#endif /* MergeSort_hpp */
