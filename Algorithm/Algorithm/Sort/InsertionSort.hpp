//
//  InsertionSort.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/21.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef InsertionSort_hpp
#define InsertionSort_hpp

#include <stdio.h>
#include <algorithm>

using namespace std;

/*
 插入排序的特点
 1. 当排序的数组近乎有序时，排序的速度非常快，因为比较的速度远远快于交换和赋值的速度
 2. 可以提前终止内层循环
 
 */
template<typename T>
void insertionSort_v1(T arr[], int length) {
    
    for (int i = 1; i < length; i++) {
        /*
         for (int j = i; j > 0 ; j--) {
             if (arr[j] < arr[j-1]) {
                swap(arr[j], arr[j-1]);
             } else {
                break;
             }
         }
         */
        for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
            swap(arr[j], arr[j-1]);
        }
    }
}


template<typename T>
void __insertionSort(T arr[], int l, int r)
{
    for (int i = l+1; i <= r; i++) {
        T item = arr[i];
        int j = i - 1;
        for (; j >= l && arr[j] > item; j--) {
            arr[j+1] = arr[j];
        }
        if (j+1 != i) {
            arr[j+1] = item;
        }
    }
}


template <typename T>
void insertionSort(T arr[], int length) {
    
    /**
        把数组分成两个部分，有序区间[l, l+1) 和无序区[l+1, r]，开始时有序区只有一个元素.
     */
    for (int i = 1; i < length; i++) {
        T item = arr[i]; // 需要考察的元素
        int j = i - 1; // 有序区间最后一个元素
        
        // 在有序区间从后往前找，比item的大的元素往后移一位，直到找到第一个 <= item的元素下标为止。
        for ( ; j >= 0; j--) {
            if (arr[j] > item) {
                arr[j+1] = arr[j];
            } else {
                break;
            }
        }
        
        // 当上面循环结束后，j为第一小于item的元素的下标，或者 j=-1, 不管哪种情况，j+1都是item应该在的位置。
        
        if (j+1 != i) {
            arr[j+1] = item;
        }
    }
}



#endif /* InsertionSort_hpp */
