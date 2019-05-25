//
//  MyArray.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/25.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "MyArray.hpp"
#include <iostream>


using namespace std;

void myArray_test();
void mergeTowSortedArray();



void array_entry() {
    
    myArray_test();
    
    mergeTowSortedArray();
}

void myArray_test() {
    
    int capacity = 10;
    
    MyArray<int> array = MyArray<int>(capacity);
    assert(array.capacity() == capacity);
    assert(array.count() == 0);
    
    for (int i = 0; i < capacity; i++) {
        array.add( i*2 );
    }

    assert(array.count() == capacity);
    assert(array.elementAtIndex(1) == 2);
    
    assert(array.removeAtIndex(0) == 0);
    assert(array.count() == capacity -1);
}



#pragma mark - megerTowSortedArray


int *__mergeTowSortedArray(int *arr1, int length1, int *arr2, int length2) {
    int *newArray = new int[length1 + length2];
    int index = 0;
    int idx1 = 0;
    int idx2 = 0;
    
    while (idx1 < length1 && idx2 < length2) {
        if (arr1[idx1] < arr2[idx2]) {
            newArray[index++] = arr1[idx1++];
        } else {
            newArray[index++] = arr2[idx2++];
        }
    }
    
    while (idx1 < length1) {
        newArray[index++] = arr1[idx1++];
    }
    
    while (idx2 < length2) {
        newArray[index++] = arr2[idx2++];
    }
    
    return newArray;
}


void mergeTowSortedArray() {
 
    int array1[] = {1, 11, 21, 31, 41};
    int array2[] = {2, 12, 22, 32, 42, 52, 62, 72, 82, 92};
    
    int *mergeArray = __mergeTowSortedArray(array1, 5, array2, 10);
    
    for (int i = 0; i < 15; i++) {
        cout << mergeArray[i] << " ";
    }
    cout << endl;
    
    delete [] mergeArray;
}

