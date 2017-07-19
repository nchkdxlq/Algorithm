//
//  SelectionSort.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/17.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include <iostream>
#include <string>
#include "SelectionSort.hpp"
#include "Student.hpp"
#include "SortTestHelper.hpp"

using std::cout;
using std::endl;
using std::string;


using namespace SortTestHelper;


/*
 模板函数
 
 
 */
template<typename T>
void selectionSort(T arr[], int length)
{
    for (int i = 0; i < length; i++) {
        int minIndex = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            std::swap(arr[minIndex], arr[i]);
        }
    }
}


void selectionSort_run()
{
    int length = 10000;
    int *arr = generateRandomArr(length, 10, length * 2);
    testSort("SelectionSort", selectionSort, arr, length);
    
    delete [] arr;
    
    
    float floatArr[5] = {5.5, 4.4, 3.3, 2.2, 1.1};
    selectionSort(floatArr, 5);
    printArr(floatArr, 5);
    
    string strArr[5] = {"E", "D", "C", "B", "A"};
    selectionSort(strArr, 5);
    printArr(strArr, 5);
    
    
    Student stuArr[5] = {{"tom", 98}, {"cookie", 76}, {"tim", 94}, {"ken", 67}, {"eric", 87}};
    selectionSort(stuArr, 5);
    printArr(stuArr, 5);
}

