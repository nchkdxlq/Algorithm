//
//  SortTestHelper.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/19.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef SortTestHelper_hpp
#define SortTestHelper_hpp

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;


namespace SortTestHelper {
    
    template<typename T>
    bool isSorted(T arr[], int length)
    {
        for (int i = 0; i < length - 1; i++) {
            if (arr[i] > arr[i+1])
                return false;
        }
        
        return true;
    }
    
    int *generateRandomArr(int length, int rangL, int rangR) {
        assert(rangL <= rangR);
        
        srand((unsigned)time(NULL));
        int *arr = new int[length];
        for (int i = 0; i < length; i++) {
            arr[i] = rand() % (rangR - rangL + 1) + rangL;
        }
        
        return arr;
    }
    
    int *generateNearlyOrderedRandomArr(int length, int swapTimes) {
        
        int *arr = new int[length];
        
        for (int i = 0; i < length; i++) {
            arr[i] = i;
        }
        
        srand((unsigned)time(NULL));
        for (int i = 0; i < swapTimes; i++) {
            int posX = rand() % length;
            int posY = rand() % length;
            std::swap(arr[posX], arr[posY]);
        }
        
        return arr;
    }
    
    template<typename T>
    void printArr(T arr[], int length)
    {
        for (int i = 0; i < length; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    template<typename T>
    void testSort(string name, void(*sort)(T[], int), T arr[], int length) {
        
        clock_t start = clock();
        sort(arr, length);
        clock_t end = clock();
        
        assert(isSorted(arr, length));
        
        double time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        cout << name << ": " << time << " ms" << endl;
    }
}

#endif /* SortTestHelper_hpp */
