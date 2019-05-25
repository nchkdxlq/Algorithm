//
//  MyArray.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/5/25.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#ifndef MyArray_hpp
#define MyArray_hpp

#include <stdio.h>
#include <cassert>


void myArray_test();


/*
 
 动态扩容的数组
 
 */

template<typename T>
class MyArray {
    
private:
    T *m_elements;
    int m_capacity; // 数组的容量
    int m_count; // 数组元素的个数
    
    void resize() {
        T *newElements = new T[m_capacity * 2];
        for (int i = 0; i < m_count; i++) {
            newElements[i] = m_elements[i];
        }
        delete [] m_elements;
        m_elements = newElements;
        m_capacity *= 2;
    }
    
public:
    
    MyArray(int capacity) {
        assert(capacity > 0);
        m_elements = new T[capacity];
        m_capacity = capacity;
        m_count = 0;
    }
    
    
    int capacity() {
        return m_capacity;
    }
    
    int count() {
        return m_count;
    }
    
    void add(T element) {
        if (m_count == m_capacity) {
            resize();
        }
        m_elements[m_count] = element;
        m_count++;
    }
    
    
    void insertAtIndex(T element, int index) {
        assert(index >= 0 && index <= m_count);
        
        if (m_count == m_capacity) {
            resize();
        }
        
        // i是需要往后挪动元素的下标，下标为index的元素也需要挪动
        for (int i = m_count - 1; i >= index; i--) {
            m_elements[i+1] = m_elements[i];
        }
        m_elements[index] = element;
        m_count++;
    }
    
    
    T removeAtIndex(int index) {
        assert(index >= 0 && index < m_count);
        T element = m_elements[index];
        for (int i = index; i < m_count; i++) {
            m_elements[i] = m_elements[i+1]; // 把后一个元素往前挪一个位置
        }
        m_count--;
        
        return element;
    }
    
    T elementAtIndex(int index) {
        assert(index >= 0 && index < m_count);
        return m_elements[index];
    }
    
    bool isEmpty() {
        return m_count == 0;
    }
    
    bool isFull() {
        return m_count == m_capacity;
    }
    
    
    ~MyArray() {
        delete [] m_elements;
        m_elements = NULL;
    }
};


#endif /* MyArray_hpp */
