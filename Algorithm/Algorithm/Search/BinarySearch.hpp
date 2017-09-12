//
//  BinarySearch.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/2.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef BinarySearch_hpp
#define BinarySearch_hpp

#include <stdio.h>

/**
 二分查找

 @param arr 有序数组
 @param n 数组的长度
 @param target 目标元素
 @return 目标元素在数组中的下标（如果不在数组中， 返回-1）
 */
template<typename T>
int binarySearch(T arr[], int n, T target) {
    
    // 在arr[l...r]中查找target元素
    int l = 0, r = n-1;
    
    while (l <= r) {
        
//        int mid = (l+r) / 2;
        int mid = l + (r-l) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        
        if (target < arr[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    return -1;
}





/**
 递归二分查找

 @param arr 有序数组
 @param l 查找范围的左下标
 @param r 查找范围的有下标
 @param target 目标元素
 @return 目标元素在数组中的下标（如果不在数组中， 返回-1）
 */
template<typename T>
int __binarySearch_v2(T arr[], int l, int r, T target) {
    int mid = l + (r-l) / 2;
    
    if (l > r) {
        return -1;
    }
    
    if (arr[mid] == target) {
        return mid;
    }
    
    if (target < arr[mid]) {
        return __binarySearch_v2(arr, l, mid-1, target);
    } else {
        return __binarySearch_v2(arr, mid+1, r, target);
    }
}


template<typename T>
int binarySearch_v2(T arr[], int n, T target) {
    return __binarySearch_v2(arr, 0, n-1, target);
}


#endif /* BinarySearch_hpp */
