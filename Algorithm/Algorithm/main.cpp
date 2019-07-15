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

#include "SortEntry.hpp"
#include "MaxHeap.hpp"


#include "BinarySearch.hpp"
#include "BST.hpp"
#include "SequenceST.hpp"
#include "FileOps.hpp"
#include "UnionTestHelper.hpp"
#include "GraphTest.hpp"


#include "MyArray.hpp"
#include "LRUCache.hpp"
#include "SingleLinkedList.hpp"
#include "DoublyLinkedList.hpp"

// https://www.toptal.com/developers/sorting-algorithms

void maxheap_run();

void binarySearch_run();
void bst_run();
void bst_traverse();


int main(int argc, const char * argv[]) {
    
//    sort_entry();
    
//    binarySearch_run();
//    bst_run();
    bst_traverse();
    
//    UnionFindTestHelper::run();
    
//    graphTest();
    
//    array_entry();
//    lruCache_entry();
//    singleLinkedList_entry();
//    doublyLinkedList_entry();
    
    return 0;
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


