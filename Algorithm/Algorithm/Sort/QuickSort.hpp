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

/*
    对arr[l...r]部分数组进行partition操作，
    返回的p使得 arr[l...p-1] < aarr[p] 并且 arr[p] < arr[p+1...r]
 */
template <typename T>
int __partition(T arr[], int l, int r) {
    
    T v = arr[l];
    
    // arr[l+1, p] < v ; arr[p+1...i) > v
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
void __quickSort(T arr[], int l, int r) {
    
    if (l >= r) {
        return;
    }
    
    int p = __partition(arr, l, r);
    __quickSort(arr, l, p-1);
    __quickSort(arr, p+1, r);
}


template <typename T>
void quickSort(T arr[], int length) {
    __quickSort(arr, 0, length-1);
}


/***********************************************

 优化一:当数组的个数比较小时，使用插入排序
 
 
 */



template <typename T>
void __quickSort1(T arr[], int l, int r) {
    
    if (r - l < 16) {
        __insertionSort(arr, l, r);
        return;
    }
    
    int p = __partition(arr, l, r);
    __quickSort1(arr, l, p-1);
    __quickSort1(arr, p+1, r);
}

template <typename T>
void quickSort1(T arr[], int length) {
    __quickSort1(arr, 0, length-1);
}


/***********************************************
 
  1. 当数组有大量的重复值时，退化成O(n^2)级别时间复杂度的算法 (缺点)
 
 
 */

template<typename T>
int __partition_v2(T arr[], int l, int r) {
    
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
        
        while (i <= r && arr[i] < v) {
            i++;
        }
        
        while (j >= l + 1 && arr[j] > v) {
            j--;
        }
        
        if (i > j) break;
        
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    
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
            if (i != ++lt) {
                swap(arr[i], arr[lt]);
            }
            i++;
        } else if (arr[i] > v) {
            swap(arr[i], arr[--gt]);
        } else { // arr[i] == v
            i++;
        }
    }
    
    swap(arr[l], arr[lt]);
    
    __quickSort3Ways(arr, l, lt);
    __quickSort3Ways(arr, gt, r);
}

template<typename T>
void quickSort3Ways(T arr[], int length) {
    srand((unsigned int)time(NULL));
    __quickSort3Ways(arr, 0, length - 1);
}



#endif /* QuickSort_hpp */
