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
namespace InsertionSort {
    
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
    
    template <typename T>
    void insertionSort(T arr[], int length) {
        
        for (int i = 1; i < length; i++) {
            
            T item = arr[i];
            int j = i;
            /*
             要考察的元素item与下标为j-1的元素比较，比item大的元素都往后移动一个下标,
             直到遇到小与item的元素或者j==0时，则位置j就是元素item插入的位置
             */
            for (; j > 0 && arr[j-1] > item; j--) {
                arr[j] = arr[j-1];
            }
            if (j != i) {
                arr[j] = item;
            }
        }
    }
}


#endif /* InsertionSort_hpp */
