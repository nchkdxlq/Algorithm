//
//  main.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/17.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include <iostream>
#include "SortTestHelper.hpp"
#include "SelectionSort.hpp"
#include "InsertionSort.hpp"
#include "BubbleSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "MaxHeap.hpp"
#include "HeapSort.hpp"


#include "BinarySearch.hpp"

// https://www.toptal.com/developers/sorting-algorithms


using namespace SortTestHelper;

void selectionSort_run();
void insertionSort_run();
void compare_insertionSort_selectionSort();
void bubbleSort_run();
void mergeSort_run();
void quickSort_run();
void maxheap_run();
void sortCompare();

void binarySearch_run();

int main(int argc, const char * argv[]) {
    
//    selectionSort_run();
//    insertionSort_run();
//    compare_insertionSort_selectionSort();
//    bubbleSort_run();
//    mergeSort_run();
//    quickSort_run();
//    maxheap_run();
//    sortCompare();
    
    binarySearch_run();
    
    return 0;
}


void selectionSort_run()
{
    int length = 10000;
    int *arr = generateRandomArray(length, 10, length * 2);
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


void insertionSort_run()
{
    int length = 10000;
    int *arr = generateRandomArray(length, 10, length * 2);
    testSort("InsertionSort", insertionSort, arr, length);

    delete [] arr;
}

void compare_insertionSort_selectionSort()
{
    int length = 10000;
    int *arr = generateNearlyOrderedRandomArray(length, 10);
    testSort("SelectionSort", selectionSort, arr, length);
    testSort("InsertionSort", insertionSort, arr, length);
    
    delete [] arr;
}

void bubbleSort_run()
{
    int length = 10000;
    int *arr = generateNearlyOrderedRandomArray(length, 10);
    testSort("BubbleSort", bubbleSort, arr, length);
    
    delete [] arr;
}

void mergeSort_run()
{
    int length = 50000;
    
    int *arr = generateRandomArray(length, 0, length);
    int *arr1 = copyIntArray(arr, length);
    int *arr2 = copyIntArray(arr, length);
    int *arr3 = copyIntArray(arr, length);
    
    testSort("MergeSort", mergeSort, arr, length);
    testSort("MergeSort_v1", mergeSort_v1, arr1, length);
    testSort("MergeSortBU", mergeSortBU, arr2, length);
    testSort("MergeSortBU_v1", mergeSort_v1, arr3, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
}


void quickSort_run()
{
    int length = 1000000;
    
    cout << ">>>>>>> randomArray <<<<<<<" << endl;
    
    int *arr = generateRandomArray(length, 0, length);
    int *arr1 = copyIntArray(arr, length);
    int *arr2 = copyIntArray(arr, length);
    int *arr3 = copyIntArray(arr, length);
    int *arr4 = copyIntArray(arr, length);
    
    testSort("mergeSort_v1", mergeSort_v1, arr, length);
    testSort("quickSort_v2", quickSort_v2, arr1, length);
    testSort("quickSort2Ways", quickSort2Ways, arr2, length);
    testSort("quickSort3Ways", quickSort3Ways, arr3, length);
    testSort("heapSort_v1", heapSort_v1, arr4, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
    
    cout << endl;
    cout << ">>>>>>> nearlyOrderlyArray <<<<<<<" << endl;
    
    arr = generateNearlyOrderedRandomArray(length, 100);
    arr1 = copyIntArray(arr, length);
    arr2 = copyIntArray(arr, length);
    arr3 = copyIntArray(arr, length);
    arr4 = copyIntArray(arr, length);
    
    testSort("mergeSort_v1", mergeSort_v1, arr, length);
    testSort("quickSort_v2", quickSort_v2, arr1, length);
    testSort("quickSort2Ways", quickSort2Ways, arr2, length);
    testSort("quickSort3Ways", quickSort3Ways, arr3, length);
    testSort("heapSort_v1", heapSort_v1, arr4, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
    
    cout << endl;
    cout << ">>>>>>> randomArray, range [0, 10] <<<<<<<" << endl;
    
    arr = generateRandomArray(length, 0, 10);
    arr1 = copyIntArray(arr, length);
    arr2 = copyIntArray(arr, length);
    arr3 = copyIntArray(arr, length);
    arr4 = copyIntArray(arr, length);
    
    testSort("mergeSort_v1", mergeSort_v1, arr, length);
//    testSort("quickSort_v2", quickSort_v2, arr1, length);
    testSort("quickSort2Ways", quickSort2Ways, arr2, length);
    testSort("quickSort3Ways", quickSort3Ways, arr3, length);
    testSort("heapSort_v1", heapSort_v1, arr4, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
}

void maxheap_run()
{
    MaxHeap<int> maxheap = MaxHeap<int>(50);
    
    cout << "maxheap size : " << maxheap.size() << endl;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 50; i++) {
        maxheap.insert(rand() % 100);
    }
    maxheap.testPrint();
    
    
    for (int i = 0; i < 50; i++) {
        cout << maxheap.extractMax() << " ";
    }
    cout << endl;
    
}



void sortCompare() {
    int length = 1000000;
    
    cout << ">>>>>>>>>>>>>>>>>>>>> randomArray <<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << endl;
    
    int *arr = generateRandomArray(length, 0, length);
    int *arr1 = copyIntArray(arr, length);
    int *arr2 = copyIntArray(arr, length);
    int *arr3 = copyIntArray(arr, length);
    int *arr4 = copyIntArray(arr, length);
    int *arr5 = copyIntArray(arr, length);
    int *arr6 = copyIntArray(arr, length);
    
    testSort("mergeSort_v1", mergeSort_v1, arr, length);
    testSort("quickSort_v2", quickSort_v2, arr1, length);
    testSort("quickSort2Ways", quickSort2Ways, arr2, length);
    testSort("quickSort3Ways", quickSort3Ways, arr3, length);
    testSort("heapSort_v1", heapSort_v1, arr4, length);
    testSort("heapSort_v2", heapSort_v2, arr5, length);
    testSort("heapSort", heapSort, arr6, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
    delete [] arr5;
    delete [] arr6;
    
    cout << endl;
    cout << endl;
    cout << ">>>>>>>>>>>>>>>>>>>>> nearlyOrderArray <<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << endl;
    
    arr = generateNearlyOrderedRandomArray(length, 100);
    arr1 = copyIntArray(arr, length);
    arr2 = copyIntArray(arr, length);
    arr3 = copyIntArray(arr, length);
    arr4 = copyIntArray(arr, length);
    arr5 = copyIntArray(arr, length);
    arr6 = copyIntArray(arr, length);
    
    testSort("mergeSort_v1", mergeSort_v1, arr, length);
    testSort("quickSort_v2", quickSort_v2, arr1, length);
    testSort("quickSort2Ways", quickSort2Ways, arr2, length);
    testSort("quickSort3Ways", quickSort3Ways, arr3, length);
    testSort("heapSort_v1", heapSort_v1, arr4, length);
    testSort("heapSort_v2", heapSort_v2, arr5, length);
    testSort("heapSort", heapSort, arr6, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
    delete [] arr5;
    delete [] arr6;
    
    cout << endl;
    cout << endl;
    cout << ">>>>>>>>>>>>>>>>>>>>> randomArray, range [0, 10] <<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << endl;
    
    arr = generateRandomArray(length, 0, 10);
    arr1 = copyIntArray(arr, length);
    arr2 = copyIntArray(arr, length);
    arr3 = copyIntArray(arr, length);
    arr4 = copyIntArray(arr, length);
    arr5 = copyIntArray(arr, length);
    arr6 = copyIntArray(arr, length);
    
    testSort("mergeSort_v1", mergeSort_v1, arr, length);
    //    testSort("quickSort_v2", quickSort_v2, arr1, length);
    testSort("quickSort2Ways", quickSort2Ways, arr2, length);
    testSort("quickSort3Ways", quickSort3Ways, arr3, length);
    testSort("heapSort_v1", heapSort_v1, arr4, length);
    testSort("heapSort_v2", heapSort_v2, arr5, length);
    testSort("heapSort", heapSort, arr6, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
    delete [] arr5;
    delete [] arr6;
    
    cout << endl;
    cout << endl;
}



void binarySearch_run()
{
    int n = 100000;
    int *arr = new int[n];
    
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    
    
    // 普通二分查找
    clock_t start = clock();
    int max = 2 * n;
    for (int i = 0; i < max; i++) {
        int index = binarySearch(arr, n, i);
        if (i < n) {
            assert(index == i);
        } else {
            assert(index == -1);
        }
    }
    clock_t end = clock();
    
    double timeCost = double(end - start) / CLOCKS_PER_SEC;
    cout << "Binary Search (Without Recursion) : " << timeCost << " s" << endl;
    
    
    // 递归二分查找
    start = clock();
    for (int i = 0; i < max; i++) {
        int index = binarySearch_v2(arr, n, i);
        if (i < n) {
            assert(index == i);
        } else {
            assert(index == -1);
        }
    }
    end = clock();
    
    timeCost = double(end - start) / CLOCKS_PER_SEC;
    cout << "Binary Search (Recursion) : " << timeCost << " s" << endl;
    
    delete [] arr;
}


