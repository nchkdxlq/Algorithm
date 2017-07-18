//
//  SelectionSort.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/17.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "SelectionSort.hpp"
#include <iostream>
#include <string>
#include "Student.hpp"

using std::cout;
using std::endl;
using std::string;


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

template<typename T>
void selectionSort_printArr(T arr[], int length)
{
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void selectionSort_run()
{
    int arr[10] = {1, 8, 7, 19, 14, 65, 60, 38, 35, 10};
    selectionSort(arr, 10);
    selectionSort_printArr(arr, 10);
    
    
    float floatArr[5] = {5.5, 4.4, 3.3, 2.2, 1.1};
    selectionSort(floatArr, 5);
    selectionSort_printArr(floatArr, 5);
    
    string strArr[5] = {"E", "D", "C", "B", "A"};
    selectionSort(strArr, 5);
    selectionSort_printArr(strArr, 5);
    
    
    Student stuArr[5] = {{"tom", 98}, {"cookie", 76}, {"tim", 94}, {"ken", 67}, {"eric", 87}};
    selectionSort(stuArr, 5);
    selectionSort_printArr(stuArr, 5);
}

