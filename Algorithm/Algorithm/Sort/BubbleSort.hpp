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
 遍历n-1遍数组，每次遍历比较相邻元素的大小, 如果arr[j] > arr[j+1], 则交换元素的位置，
 当 j < n-1-i 条件不成立时停止遍历。
 */
template<typename T>
void bubbleSort(T arr[], int length) {
    
    // i 为扫描数组的次数
    // 遍历i次后，[n-1-i...n-1]为有序区间
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

#endif /* BubbleSort_hpp */
