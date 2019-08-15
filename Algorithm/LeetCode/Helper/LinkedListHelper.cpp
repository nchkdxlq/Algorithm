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
    
    
    /**
     寻找以head为头结点，tail为尾结点但不包含tail链表的中间结点,
     当tail为空结点或者不是以head为头的链表中的结点时，返回以head为头结点链表的中间结点

     @param head 链表的头结点
     @param tail 链表的尾结点
     @return 链表的中间结点
     */
    ListNode* getMidNode(ListNode *head, ListNode* tail) {
        if (head == tail) return nullptr;
        if (head == nullptr || head->next == nullptr) return head;
        
        auto slow = head;
        auto fast = head;
        
        while (fast && fast->next != tail && fast->next && fast->next->next != tail) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
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
