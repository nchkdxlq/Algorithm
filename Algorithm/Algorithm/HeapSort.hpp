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







#endif /* HeapSort_hpp */
