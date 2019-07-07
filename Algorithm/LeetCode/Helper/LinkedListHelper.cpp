//
//  LinkedListHelper.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/7.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "LinkedListHelper.hpp"


namespace Singly {
    
    ListNode *create_singlyLinkedList(vector<int> &nums) {
        ListNode dummy(-1);
        ListNode *tail = &dummy;
        
        for (auto i : nums) {
            ListNode *newNode = new ListNode(i);
            tail->next = newNode;
            tail = newNode;
        }
        
        return dummy.next;
    }
    
    void print_singlyLinkedList(ListNode *list) {
        while (list) {
            cout << list->val << " -> ";
            list = list->next;
        }
        cout << "NULL" << endl;
    }
}


namespace Doubly {
    
    ListNode *create_doublyLinkedList(vector<int> &nums) {
        ListNode dummy(-1);
        ListNode *tail = &dummy;
        
        for (auto i : nums) {
            ListNode *newNode = new ListNode(i);
            tail->next = newNode;
            newNode->pre = tail;
            tail = newNode;
        }
        
        return dummy.next;
    }
    
    void print_doublyLinkedList(ListNode *list) {
        while (list) {
            cout << list->val << " -> ";
            list = list->next;
        }
        cout << "NULL" << endl;
    }
    
}
