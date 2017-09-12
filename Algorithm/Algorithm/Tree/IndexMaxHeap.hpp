//
//  IndexMaxHeap.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/8/20.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef IndexMaxHeap_hpp
#define IndexMaxHeap_hpp

#include <stdio.h>
#include <assert.h>

/*
 
 堆的索引从0开始
 
 left = 2 * parent + 1
 right = 2 * parent + 2
 parent = (child - 1) / 2

 */

template<typename Item>
class IndexMaxHeap {
    
private:
    Item *m_data;
    int *m_indexes;
    int *m_map;
    int m_capacity;
    int m_count;
    
    
    void shiftUp(int k) {
        
        // 非根节点 && 父节点 < 子节点
        while (k > 0 && m_data[m_indexes[(k-1)/2]] < m_data[m_indexes[k]]) {
            swap(m_indexes[k], m_indexes[(k-1)/2]);
            m_map[m_indexes[k]] = k;
            m_map[m_indexes[(k-1)/2]] = (k-1)/2;
            
            k = (k-1)/2;
        }
    }
    
    void shiftDown(int k) {
        
        // 有效节点 && 存在子节点
        while (k >= 0 && (2*k + 1) < m_count) {
            
            // 找出值更大的子节点
            int child = 2*k + 1;
            if ((child + 1) < m_count &&
                m_data[m_indexes[child + 1]] > m_data[m_indexes[child]]) {
                child = child + 1;
            }
            
            // 更大的子节点 <= k节点， 已满足最大堆性质，直接break
            if (m_data[m_indexes[child]] <= m_data[m_indexes[k]]) {
                break;
            } else {
                swap(m_indexes[k], m_indexes[child]);
                m_map[m_indexes[k]] = k;
                m_map[m_indexes[child]] = child;
                k = child;
            }
        }
    }
    
public:
    IndexMaxHeap(int capacity)
    {
        m_data = new Item[capacity];
        m_indexes = new int[capacity];
        m_map = new int[capacity];
        m_capacity = capacity;
        m_count = 0;
        
        for (int i = 0; i < capacity; i++) {
            m_indexes[i] = -1;
            m_map[i] = -1;
        }
    }
    
    ~IndexMaxHeap()
    {
        delete [] m_data;
        delete [] m_indexes;
        delete [] m_map;
    }
    
    int size() {
        return m_count;
    }
    
    bool isEmpty() {
        return m_count == 0;
    }
    
    bool isFull() {
        return m_count == m_capacity;
    }
    
    void append(Item item) {
        assert(!isFull());
        
        m_data[m_count] = item;
        m_indexes[m_count] = m_count;
        m_map[m_count] = m_count;
        shiftUp(m_count);
        m_count++;
    }
    
    void change(int i, Item item) {
        assert(i >= 0 && i < m_capacity);
        
        m_data[i] = item;
        
        int j = m_map[i];
        shiftUp(j);
        shiftDown(j);
    }
    
    
    Item extractMax() {
        assert(!isEmpty());
        
        Item item = m_data[m_indexes[0]];
        m_indexes[0] = m_indexes[m_count-1];
        m_indexes[m_count-1] = -1;
        m_map[m_count-1] = -1;
        m_count--;
        shiftDown(0);
        
        return item;
    }
    
    int extractMaxIndex() {
        assert(!isEmpty());
        
        int max = m_indexes[0];
        
        m_indexes[0] = m_indexes[m_count-1];
        m_indexes[m_count-1] = -1;
        m_map[m_count-1] = -1;
        m_count--;
        shiftDown(0);
        
        return max;
    }
};




#endif /* IndexMaxHeap_hpp */
