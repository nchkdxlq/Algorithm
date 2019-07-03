//
//  QuickSort.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/24.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef QuickSort_hpp
#define QuickSort_hpp

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "InsertionSort.hpp"


int __test_partition(int arr[], int l, int r) {

#if 1
    int item = arr[r];
    int p = r;

    for (int i = p-1; i >= l; i--) {
        if (arr[i] > item) {
            swap(arr[i], arr[p-1]);
            p--;
        }
    }

    swap(arr[p], arr[r]);

    return p;
    
#else
    int v = arr[l];
    
    // arr[l+1, p] < v ; arr[p+1...i) >= v
    int p = l;
    for (int i = p + 1; i <= r; i++) {
        if (arr[i] < v) {
            swap(arr[i], arr[p+1]);
            p++;
        }
    }
    
    swap(arr[l], arr[p]);
    
    return p;
#endif
}

void __test_quickSort(int arr[], int l, int r) {
    if (l >= r) return;
    
    int p = __test_partition(arr, l, r);
    __test_quickSort(arr, l, p-1);
    __test_quickSort(arr, p+1, r);
}



void test_quickSort(int arr[], int n) {
    __test_quickSort(arr, 0, n-1);
}








#pragma mark - 第一版快速排序

/*
    对arr[l...r]部分数组进行partition操作，
    返回的p使得 arr[l...p-1] < aarr[p] 并且 arr[p] < arr[p+1...r]
 */
template <typename T>
int __partition(T arr[], int l, int r) {
    
    T v = arr[l];
    
    // arr[l+1, p] < v ; arr[p+1...i) >= v
    int p = l;
    for (int i = p + 1; i <= r; i++) {
        if (arr[i] < v) {
            swap(arr[i], arr[p+1]);
            p++;
        }
    }
    
    swap(arr[l], arr[p]);
    
    return p;
}


template <typename T>
void __quickSort_v0(T arr[], int l, int r) {
    
    if (l >= r) {
        return;
    }
    
    int p = __partition(arr, l, r);
    __quickSort_v0(arr, l, p-1);
    __quickSort_v0(arr, p+1, r);
}


template <typename T>
void quickSort_v0(T arr[], int length) {
    __quickSort_v0(arr, 0, length-1);
}



#pragma mark - 第一版快速排序优化一

/***********************************************

 优化一:当数组的个数比较小时，使用插入排序
 
 */
template <typename T>
void __quickSort1_v1(T arr[], int l, int r) {
    
    if (r - l < 16) {
        __insertionSort(arr, l, r);
        return;
    }
    
    int p = __partition(arr, l, r);
    __quickSort1_v1(arr, l, p-1);
    __quickSort1_v1(arr, p+1, r);
}

template <typename T>
void quickSort_v1(T arr[], int length) {
    __quickSort1_v1(arr, 0, length-1);
}

/***********************************************
 
 1. v0问题分析：
 在v0版本中，当数组近乎有序时，在partition过程中，通过标定点分成的两个子数组长度相差很大，
 这会导致递归的层数很深，最坏的情况层数为n，此时就退化成 O(n) 级别时间复杂度的算法。
 
 1.1 结论：v0版本，当数组有大量的重复值时，退化成O(n^2)级别时间复杂度的算法
 
 2.v0版本优化：
 
 在arr[l...r]中随机选择一个元素作为标定点，具体的的做法是随机选择一个元素与第一个元素交换位置。
 这样做能够大大减少partition过程中分成的两个子数组长度相差很大情况的概率，这样能够减少递归的层数，
 退化为 O(n^2)时间复杂度概率几乎为零。【1/n * 1/(n-1) ...】 == 0

 
 3. v1版本问题分析
 缺点：1. 当数组有大量的重复值时，退化成O(n^2)级别时间复杂度的算法
 
 原因分析：
 当数组中有大量重复元素时， 在partition过程中，不管把等于v的元素放在小于v的那边还是放在大于v的那边，
 都会使得两个子数组的长度相差特别大，这就会增加递归的层数，最终退化为 O(n^2)级别的算法。

 */

template<typename T>
int __partition_v2(T arr[], int l, int r) {
    
    // 在arr[l...r]中随机选择一个元素作为标定点，
    
    swap(arr[l], arr[rand() % (r-l+1) + l]);
    
    T v = arr[l];
    int p = l;
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < v) {
            swap(arr[i], arr[p+1]);
            p++;
        }
    }
    
    if (p != l) {
        swap(arr[l], arr[p]);
    }
    
    return p;
}

template<typename T>
void __quickSort_v2(T arr[], int l, int r) {
    
    if (r - l < 16) {
        __insertionSort(arr, l, r);
        return;
    }
    
    int p = __partition_v2(arr, l, r);
    __quickSort_v2(arr, l, p-1);
    __quickSort_v2(arr, p+1, r);
}

template<typename T>
void quickSort_v2(T arr[], int lenght) {
    srand((unsigned int)time(NULL));
    __quickSort_v2(arr, 0, lenght-1);
}

#pragma mark - 双路快速排序


/***********************************************
 
 特点：
 1. 当数组几乎有序时，排序效率非常高，比归并排序还要快 (优点)
 
 */


template<typename T>
int __partition2Ways(T arr[], int l, int r) {
    
    swap(arr[l], arr[rand()%(r-l+1)+l]);
    T v = arr[l];
    
    // arr[l+1...i) <= v , arr(j...r] => v
    int i = l + 1, j = r;
    
    while (true) {
        // arr[i] < v 时，i 往后移
        while (i <= r && arr[i] < v) i++;
        // arr[j] > v 时，j 往前移
        while (j >= l + 1 && arr[j] > v) j--;
        
        if (i > j) break;
        
        /*
         这种情况是 arr[i] >= v，  arr[j] <= v， 交互位置,
         == v 的情况也交互位置，可以保证相同元素不会大量的在同一侧，
         保证两个子数组相对平衡。
         */
        swap(arr[i++], arr[j--]);
    }
    
    /* 循环结束后，i 在 >= v 的第一个位置，后半部分的第一个位置，j在前半部分的最后一个位置,
     此时 arr[j] 可能等于v， 也可能小于v，所以 arr[l], arr[j]交互位置。
     */
    swap(arr[l], arr[j]);
    
    return j;
}

template<typename T>
void __quickSort2Ways(T arr, int l, int r) {
    
    if (r - l < 16) {
        __insertionSort(arr, l, r);
        return;
    }
    
    int p = __partition2Ways(arr, l, r);
    __quickSort2Ways(arr, l, p-1);
    __quickSort2Ways(arr, p+1, r);
}


template<typename T>
void quickSort2Ways(T arr[], int length) {
    
    srand((unsigned int)time(NULL));
    __quickSort2Ways(arr, 0, length - 1);
}


#pragma mark - 三路快速排序

/***********************************************
 
 1. 当数组有大量的重复值时，排序效率很高
 
 */


template<typename T>
void __quickSort3Ways(T arr[], int l, int r) {
    
    if (r - l < 16) {
        __insertionSort(arr, l, r);
        return;
    }
    
    // partition
    swap(arr[l], arr[rand()%(r-l+1)+l]);
    
    T v = arr[l];
    
    int lt = l;  // arr[lt...i] < v
    int gt = r + 1; // arr[gt...r] > v
    int i = l + 1; // arr[lt+1...i] == v
    
    while (i < gt) {
        if (arr[i] < v) {
            swap(arr[i], arr[lt+1]);
            i++;
            lt++;
        } else if (arr[i] > v) {
            swap(arr[i], arr[gt-1]);
            gt--;
        } else { // arr[i] == v
            i++;
        }
    }
    
    swap(arr[l], arr[lt]);
    lt--;
    
    __quickSort3Ways(arr, l, lt);
    __quickSort3Ways(arr, gt, r);
}

template<typename T>
void quickSort3Ways(T arr[], int length) {
    srand((unsigned int)time(NULL));
    __quickSort3Ways(arr, 0, length - 1);
}



#endif /* QuickSort_hpp */
