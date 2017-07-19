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

using std::cout;
using std::endl;



namespace SortTestHelper {
    
    
    // declaration
    int *generateRandomArr(int length, int rangL, int rangR);
    
    template<typename T>
    void printArr(T arr[], int length);
    
    template<typename T>
    void testSort(string name, void(*sort)(T[], int), T arr[], int length);
    
    
    template<typename T>
    bool isSorted(T arr[], int length);
    
    
    
    // implemation
    int *generateRandomArr(int length, int rangL, int rangR) {
        assert(rangL <= rangR);
    
        srand((unsigned)time(NULL));
        int *arr = new int[length];
        for (int i = 0; i < length; i++) {
            arr[i] = rand() % (rangR - rangL + 1) + rangL;
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
        
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        cout << name << ": " << time << "s" << endl;
    }
    
    template<typename T>
    bool isSorted(T arr[], int length)
    {
        for (int i = 0; i < length - 1; i++) {
            if (arr[i] > arr[i+1])
                return false;
        }
        
        return true;
    }
    
}


#endif /* SortTestHelper_hpp */
