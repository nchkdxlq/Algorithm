//
//  23-mergeKLists.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/6/12.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "23-mergeKLists.hpp"
#include <vector>
#include <iostream>
#include "LinkedListHelper.hpp"

using namespace std;
using namespace Singly;



void siftDown(vector<ListNode*>& lists, int i) {
    int size = (int)lists.size();
    
    while (2*i+1 < size) {
        int j = 2*i+1;
        if (j+1 < size && lists[j+1]->val < lists[j]->val) {
            j = j + 1;
        }
        
        if (lists[i]->val > lists[j]->val) {
            swap(lists[i], lists[j]);
            i = j;
        } else {
            break;
        }
    }
}

ListNode* mergeKLists(vector<ListNode *> &lists) {
    // 预处理，过滤掉空链表
    for (auto iterator = lists.begin(); iterator != lists.end(); ) {
        ListNode *node = *iterator;
        if (node) {
            iterator++;
        } else {
            iterator = lists.erase(iterator);
        }
    }
    
    // 根据链表的首结点的值，建立小顶堆
    for (int i = (int)lists.size()/2 - 1; i >= 0; i--) {
        siftDown(lists, i);
    }
    
    ListNode dummy(-1);
    ListNode *tail = &dummy;
    
    while (lists.empty() == false) {
        ListNode *top = lists[0];
        tail->next = top;
        tail = top;
        top = top->next;
        lists[0] = top;
        
        int size = (int)lists.size();
        ListNode *min = nullptr;
        if (size > 1) {
            min = lists[1];
        }
        if (size > 2 && lists[2]->val < min->val) {
            min = lists[2];
        }
        
        if (min) {
            // 遍历堆顶链表，把比min结点更新的结点都添加到新的链表中
            while (top && min && top->val <= min->val) {
                tail->next = top;
                tail = top;
                top = top->next;
            }
            
            if (top) {
                lists[0] = top;
                siftDown(lists, 0);
            } else {
                if (size == 1) {
                    break;
                } else {
                    swap(lists.front(), lists.back());
                    lists.pop_back();
                    siftDown(lists, 0);
                }
            }
        } else { // 只有一个链表了，直接把整改链表添加到新链表中
            tail->next = top;
            break;
        }
    }
    
    return dummy.next;
}


ListNode *create_list(vector<int> &nums) {
    ListNode dummy(-1);
    ListNode *tail = &dummy;
    
    for (auto i : nums) {
        ListNode *newNode = new ListNode(i);
        tail->next = newNode;
        tail = newNode;
    }
    
    return dummy.next;
}

void __23_entry() {
    vector<int> v1;
    vector<int> v2{-1,5,11};
    vector<int> v3{6,10};
    
    ListNode *l1 = create_singlyLinkedList(v1);
    ListNode *l2 = create_singlyLinkedList(v2);
    ListNode *l3 = create_singlyLinkedList(v3);
    
    vector<ListNode *> lists{l1, l2, l3};
    
    
    ListNode *head = mergeKLists(lists);
    print_singlyLinkedList(head);
}
