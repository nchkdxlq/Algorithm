//
//  BubbleSort.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/22.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef BubbleSort_hpp
#define BubbleSort_hpp

#include <stdio.h>
#include <algorithm>

/*
 冒泡排序：
 
 */
template<typename T>
void bubbleSort(T arr[], int length) {
    
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


#endif /* BubbleSort_hpp */
