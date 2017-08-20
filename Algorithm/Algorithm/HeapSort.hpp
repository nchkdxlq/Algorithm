//
//  HeapSort.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/8/6.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef HeapSort_hpp
#define HeapSort_hpp

#include <stdio.h>
#include "MaxHeap.hpp"


template<typename T>
void heapSort_v1(T arr[], int n) {
    
    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for (int i = 0; i < n; i++) {
        maxheap.insert(arr[i]);
    }
    
    for (int i = n-1; i >=0; i--) {
        arr[i] = maxheap.extractMax();
    }
}


template<typename T>
void heapSort_v2(T arr[], int n)
{
    MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
    for (int i = n-1; i >=0; i--) {
        arr[i] = maxheap.extractMax();
    }
}


/*
 当堆的索引从0开始时，
 parent = (child-1)/2
 left = parent*2 + 1
 right = parent*2 + 2
 
 最后一个非叶子节点索引 index = (count - 2) / 2;
 
 */

template<typename T>
void __shiftDown(T arr[], int n, int k)
{
    while ((2*k+1) < n) {
        
        int j = 2*k + 1;
        if (j+1 < n && arr[j+1] > arr[j]) {
            j = j+1;
        }
        
        if (arr[k] >= arr[j])
            break;
        
        swap(arr[k], arr[j]);
        k = j;
    }
}

template<typename T>
void heapSort(T arr[], int n)
{
    for (int i = (n-2)/2; i >= 0; i--) {
        __shiftDown(arr, n, i);
    }
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0);
    }
}




#endif /* HeapSort_hpp */
