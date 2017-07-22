//
//  SelectionSort.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/17.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef SelectionSort_hpp
#define SelectionSort_hpp

#include <stdio.h>
#include <algorithm>
#include "Student.hpp"


/*
 选择排序
 时间复杂度：n方级别算法
 最好情况（已升序）：0，
 最坏情况（已降序）：(n * (n-1)) / 2 = n*n/2 - n/2
 */

template<typename T>
void selectionSort(T arr[], int length)
{
    for (int i = 0; i < length; i++) {
        int minIndex = i;
        for (int j = i + 1; j < length ; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            std::swap(arr[minIndex], arr[i]);
        }
    }
}

#endif /* SelectionSort_hpp */
