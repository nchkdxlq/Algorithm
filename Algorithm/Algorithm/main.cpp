//
//  main.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/17.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

#include "SortTestHelper.hpp"
#include "SelectionSort.hpp"
#include "InsertionSort.hpp"
#include "BubbleSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "MaxHeap.hpp"
#include "HeapSort.hpp"


#include "BinarySearch.hpp"
#include "BST.hpp"
#include "SequenceST.hpp"
#include "FileOps.hpp"
#include "UnionTestHelper.hpp"
#include "GraphTest.hpp"


#include "MyArray.hpp"


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
void bst_run();
void bst_traverse();


int main(int argc, const char * argv[]) {
    
//    selectionSort_run();
//    insertionSort_run();
//    compare_insertionSort_selectionSort();
//    bubbleSort_run();
//    mergeSort_run();
//    quickSort_run();
//    maxheap_run();
//    sortCompare();
    
//    binarySearch_run();
//    bst_run();
//    bst_traverse();
    
//    UnionFindTestHelper::run();
    
//    graphTest();
    
    array_entry();
    
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
    testSort("MergeSortBU_v1", mergeSortBU_v1, arr3, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
}


void quickSort_run()
{
    int length = 1000000;
    int *arr, *arr1, *arr2, *arr3, *arr4;
    
#if 0
    cout << ">>>>>>> randomArray <<<<<<<" << endl;
    arr = generateRandomArray(length, 0, length);
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

#if 1
    
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
//    testSort("heapSort_v1", heapSort_v1, arr4, length);
    
    delete [] arr;
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
#endif
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


/////////////////////////////



/**
 二分查找树
 */
void bst_run() {
    
    string filename = "/Users/nchkdxlq/learn/iOS/summary/Algorithm/Algorithm/Algorithm/resources/bible.rtf";
    
    vector<string> words;
    if( FileOps::readFile(filename, words) ) {
        
        cout << "There are totally " << words.size() << " words in " << filename << endl;
        
        cout << endl;
        
        
        // test BST
        time_t startTime = clock();
        BST<string, int> bst = BST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = bst.search(*iter);
            if (res == NULL)
                bst.insert(*iter, 1);
            else
                (*res)++;
        }
        
        cout << "'god' : " << *bst.search("god") << endl;
        time_t endTime = clock();
        cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        
        cout << endl;
        
        
        // test SST
        startTime = clock();
        SequenceST<string, int> sst = SequenceST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = sst.search(*iter);
            if (res == NULL)
                sst.insert(*iter, 1);
            else
                (*res)++;
        }
        
        cout << "'god' : " << *sst.search("god") << endl;
        
        endTime = clock();
        cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        
    }
}


void bst_traverse() {
    
    BST<int, int> bst = BST<int, int>();
    
    srand((unsigned int)(time(NULL)));
    int n = 30;
    for (int i = 0; i < n; i++) {
        if (i == 10) {
            bst.insert(i, i);
        } else {
            bst.insert(rand()%n, i);
        }
    }
    
    cout << "preTraverse: ";
    bst.preTraverse();
    
    cout << "midTraverse: ";
    bst.midTraverse();
    
    cout << "postTraverse: ";
    bst.postTraverse();
    
    cout << "levelTraverse: ";
    bst.levelTraverse();
    
    bst.remove_v2(10);
    cout << "remove( 10 ): ";
    bst.midTraverse();
    
    bst.removeMax_v2();
    cout << "   removeMax: ";
    bst.midTraverse();
    
    bst.removeMin_v2();
    cout << "   removeMin: ";
    bst.midTraverse();
}


