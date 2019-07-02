//
//  BubbleSort.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/22.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef BubbleSort_hpp
#define BubbleSort_hpp

#include <stdio.h>
#include <algorithm>
#include "SortTestHelper.hpp"

using namespace SortTestHelper;

/*
 冒泡排序：
 遍历n-1遍数组，每次遍历比较相邻元素的大小, 如果arr[j] > arr[j+1], 则交换元素的位置，
 当 j < n-1-i 条件不成立时停止遍历。
 */
template<typename T>
void bubbleSort(T arr[], int length) {
    
    // i 为扫描数组的次数
    // 遍历i次后，[n-1-i...n-1]为有序区间
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

/**
 
 冒泡算法思想排序单链表，升序排序
 
 
 */
ListNode *linkedList_bubbleSort(ListNode *list) {
    if (list == nullptr) return list;
    
    ListNode *sortedNode = nullptr;
    ListNode dummy = ListNode(-1);
    dummy.next = list;
    
    while (dummy.next != sortedNode) {
        ListNode *pre = nullptr;
        ListNode *cur = dummy.next;
        ListNode *next = cur->next;
        
        while (cur && next) {
            if (next == sortedNode) break;
            
            ListNode *nextNext = next->next;
            if (cur->val > next->val) { // cur结点大于next结点时，交换两个结点
                
                if (pre) {
                    pre->next = next;
                } else {
                    dummy.next = next;
                }
                pre = next;
                
                cur->next = nextNext;
                next->next = cur;
                
                // cur 不变
                next = nextNext;
            } else {
                if (pre) {
                    pre->next = cur;
                } else {
                    dummy.next = cur;
                }
                pre = cur;
                
                cur = next;
                next = nextNext;
            }
        }
        
        sortedNode = cur;
    }
    
    return dummy.next;
}


/**
    把链表分为两部分，有序区、无序区
    用sortedNode记录有序区的第一个结点
    遍历链表，cur的值大于next时，交换结点；当next等于sortedNode结点时，此次遍历结束，并更新 sortedNode = cur.
    重复上一个步骤，直到当sortedNode结点等于链表的第一个结点时，整个链表排序过程完成
 */
ListNode *v2_linkedList_bubbleSort(ListNode *list) {
    if (list == nullptr) return nullptr;
    if (list->next == nullptr)  return list;
    
    ListNode *sortedNode = nullptr;
    ListNode dummy = ListNode(-1);
    dummy.next = list;
    
    while (sortedNode != dummy.next) {
        
        ListNode *cur = dummy.next;
        ListNode *next = cur->next;
        
        while (cur && next) {
            if (next == sortedNode) break;
            
            ListNode *nextNext = next->next;
            
            if (cur->val > next->val) {
                
                ListNode *pre = cur->pre;
                next->pre = pre;
                if (pre == nullptr) {
                    dummy.next = next;
                } else {
                    pre->next = next;
                }
                pre = next;
                
                next->next = cur;
                cur->pre = next;
                
                cur->next = nextNext;
                if (nextNext) nextNext->pre = cur;
                
                next = nextNext;
            } else {
                if (cur->pre == nullptr) {
                    dummy.next = cur;
                }
                cur = next;
                next = nextNext;
            }
        }
        
        sortedNode = cur;
    }
    
    return dummy.next;
}


#endif /* BubbleSort_hpp */
