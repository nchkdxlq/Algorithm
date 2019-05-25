//
//  MyArray.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/25.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "MyArray.hpp"


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
