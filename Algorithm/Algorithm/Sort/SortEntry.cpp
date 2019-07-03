//
//  SortEntry.cpp
//  Algorithm
//
//  Created by Knox on 2019/7/1.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "SortEntry.hpp"
#include "SortTestHelper.hpp"

#include "BubbleSort.hpp"
#include "InsertionSort.hpp"
#include "SelectionSort.hpp"

#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"

using namespace SortTestHelper;


void __bubbleSort()
{
    int length = 10000;
    int *arr = generateNearlyOrderedRandomArray(length, 10);
    testSort("BubbleSort", bubbleSort, arr, length);
    delete [] arr;
}


void __linkedList_bubbleSort() {
    
    int length = 10;
    int *arr = generateRandomArray(length, 10, length * 2);
    
    ListNode *list = generateLinkedListFromArray(arr, length);
    printLinkedList(list);
    
//    ListNode *sortedList = linkedList_bubbleSort(list);
    ListNode *sortedList = v2_linkedList_bubbleSort(list);
    printLinkedList(sortedList);
}


void __insertionSort()
{
    int length = 10000;
    int *arr = generateRandomArray(length, 10, length * 2);
    testSort("InsertionSort", insertionSort, arr, length);
    
    delete [] arr;
}

void __selectionSort()
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


void __compare_insertionSort_selectionSort()
{
    // 1. 随机数组
#if 0
    int length = 10000;
    int *arr =generateRandomArray(length, 10, length * 2);
    int *arr1 = copyIntArray(arr, length);
    int *arr2 = copyIntArray(arr, length);
    testSort("SelectionSort", selectionSort, arr1, length);
    testSort("InsertionSort", insertionSort, arr2, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    /*
     arraySize: 10000  SelectionSort: 130.617 ms
     arraySize: 10000  InsertionSort: 112.577 ms
     */
#endif
    // 2. 近乎有序数组
#if 0
    int length = 10000;
    int *arr = generateNearlyOrderedRandomArray(length, 10);
    int *arr1 = copyIntArray(arr, length);
    int *arr2 = copyIntArray(arr, length);
    testSort("SelectionSort", selectionSort, arr1, length);
    testSort("InsertionSort", insertionSort, arr2, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    /*
     arraySize: 10000  SelectionSort: 124.516 ms
     arraySize: 10000  InsertionSort: 0.352 ms
     */
#endif
    // 3. 近乎逆序数组
#if 1
    int length = 10000;
    int *arr = generateNearlyOrderedRandomArray(length, 10);
    arr = reverseIntAarray(arr, length);
    int *arr1 = copyIntArray(arr, length);
    int *arr2 = copyIntArray(arr, length);
    testSort("SelectionSort", selectionSort, arr1, length);
    testSort("InsertionSort", insertionSort, arr2, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    /*
     arraySize: 10000  SelectionSort: 155.929 ms
     arraySize: 10000  InsertionSort: 240.214 ms
     */
#endif
}


void __mergeSort()
{
    int length = 50000;
    
    int *arr = generateRandomArray(length, 0, length);
    int *arr1 = copyIntArray(arr, length);
    int *arr2 = copyIntArray(arr, length);
    int *arr3 = copyIntArray(arr, length);
    
    testSort("MergeSort", test_mergeSort, arr, length);
//    testSort("MergeSort_v1", mergeSort_v1, arr1, length);
//    testSort("MergeSortBU", mergeSortBU, arr2, length);
//    testSort("MergeSortBU_v1", mergeSortBU_v1, arr3, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
}


void __quickSort()
{
    int length = 1000000;
    int *arr, *arr1, *arr2, *arr3, *arr4;
    
    
#if 1
    cout << ">>>>>>> randomArray <<<<<<<" << endl;
    arr = generateRandomArray(length, 0, length);
    testSort("test_quicksort", test_quickSort, arr, length);
    
    return;
    
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
#endif
    
#if 0
    cout << endl;
    cout << ">>>>>>> nearlyOrderlyArray <<<<<<<" << endl;
    
    arr = generateNearlyOrderedRandomArray(length, 100);
    arr1 = copyIntArray(arr, length);
    arr2 = copyIntArray(arr, length);
    arr3 = copyIntArray(arr, length);
    arr4 = copyIntArray(arr, length);
    
    testSort("mergeSort_v1", mergeSort_v1, arr, length);
    testSort("quickSort_v1", quickSort_v1, arr1, length);
    testSort("quickSort2Ways", quickSort2Ways, arr2, length);
    testSort("quickSort3Ways", quickSort3Ways, arr3, length);
    testSort("heapSort_v1", heapSort_v1, arr4, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
#endif
    
#if 0
    
    cout << endl;
    cout << ">>>>>>> randomArray, range [0, 10] <<<<<<<" << endl;
    arr = generateRandomArray(length, 0, 10);
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
#endif
}


void __sortCompare() {
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




void sort_entry() {
//    __bubbleSort();
//    __linkedList_bubbleSort();
    
//    __insertionSort();
//
//    __selectionSort();
    
//    __mergeSort();
    __quickSort();
}
