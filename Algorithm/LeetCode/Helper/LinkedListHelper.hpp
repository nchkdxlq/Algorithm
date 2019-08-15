//
//  LinkedListHelper.hpp
//  LeetCode
//
//  Created by Knox on 2019/7/7.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#ifndef LinkedListHelper_hpp
#define LinkedListHelper_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

namespace Singly {
    
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    
    ListNode *create_singlyLinkedList(vector<int> &nums);
    
    void print_singlyLinkedList(ListNode *list);
    
    ListNode* getMidNode(ListNode *head, ListNode* tail);
}

namespace Doubly {
    
    struct ListNode {
        int val;
        ListNode *pre;
        ListNode *next;
        ListNode(int x) : val(x), pre(nullptr), next(NULL) {}
    };
    
    ListNode *create_doublyLinkedList(vector<int> &nums);
    
    void print_doublyLinkedList(ListNode *list);
    
}

#endif /* LinkedListHelper_hpp */
