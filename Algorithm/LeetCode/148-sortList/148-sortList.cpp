//
//  148-sortList.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/7.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "148-sortList.hpp"
#include "stlheaders.h"
#include "LinkedListHelper.hpp"

using namespace Singly;

/**
 在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。
 
 示例 1:
 输入: 4->2->1->3
 输出: 1->2->3->4
 
 示例 2:
 输入: -1->5->3->4->0
 输出: -1->0->3->4->5
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/sort-list
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */


namespace sortList_148 {
    
    class Solution {
    private:
        
        // 自底向上归并迭代解法
        ListNode* v1_sortList(ListNode* head) {
            
            ListNode dummy = ListNode(-1);
            dummy.next = head;
            
            int count = 0;
            while (head) {
                count++;
                head = head->next;
            }
            
            for (int size = 1; size < count; size += size) {
                ListNode *pre = &dummy;
                bool isFirst = true;
                
                ListNode *cur = pre->next;
                while (cur) {
                    ListNode *l1_head = nullptr;
                    ListNode *l1_tail = nullptr;
                    
                    ListNode *l2_head = nullptr;
                    ListNode *l2_tail = nullptr;
                    
                    ListNode *next = nullptr;
                    
                    // 找到左边链表首尾结点
                    int i = 0;
                    while (i < size && cur) {
                        if (l1_head == nullptr) l1_head = cur;
                        l1_tail = cur;
                        cur = cur->next;
                        i++;
                    }
                    
                    // 找到右边链表首尾结点
                    i = 0;
                    while (i < size && cur) {
                        if (l2_head == nullptr) l2_head = cur;
                        l2_tail = cur;
                        cur = cur->next;
                        i++;
                    }
                    
                    next = cur;
                    
                    // 清空next指针，方便判断遍历到最后一个结点
                    if (l1_tail) l1_tail->next = nullptr;
                    if (l2_tail) l2_tail->next = nullptr;
                    
                    // 合并两个链表
                    ListNode tmp_dummy = ListNode(-1);
                    ListNode *tmp_tail = &tmp_dummy;
                    
                    while (l1_head && l2_head) {
                        if (l1_head->val < l2_head->val) {
                            tmp_tail->next = l1_head;
                            tmp_tail = l1_head;
                            l1_head = l1_head->next;
                        } else {
                            tmp_tail->next = l2_head;
                            tmp_tail = l2_head;
                            l2_head = l2_head->next;
                        }
                    }
                    
                    // 遍历剩余未合并的部分
                    ListNode *l = l1_head ? l1_head : l2_head;
                    while (l) {
                        tmp_tail->next = l;
                        tmp_tail = l;
                        l = l->next;
                    }
                    
                    // 保证链表不断
                    tmp_tail->next = next;
                    
                    // 与上一部分连接
                    if (isFirst) {
                        dummy.next = tmp_dummy.next;
                        isFirst = false;
                    } else {
                        pre->next = tmp_dummy.next;
                    }
                    
                    pre = tmp_tail;
                    cur = next;
                }
            }
            
            return dummy.next;
        }
        
        // 递归解法
        ListNode* v2_sortList(ListNode* head) {
            
            if (head == nullptr) return nullptr;
            if (head->next == nullptr) return head;
            
            ListNode *mid = _getMid(head);
            ListNode *right = mid->next;
            mid->next = nullptr; // 分割成两个链表
            return _merge(v2_sortList(head), v2_sortList(right));
        }
        
        // 利用快慢指针找到链表的中间结点
        ListNode* _getMid(ListNode *head) {
            ListNode *slow = head; // 慢指针一次前进一步
            ListNode *fast = head; // 快指针一次前进两步
            
            while (fast) {
                // 只有当fast存在下下个结点时，slow才前进一步
                if (fast->next && fast->next->next) {
                    slow = slow->next;
                    fast = fast->next->next;
                } else {
                    break;
                }
            }
            
            return slow;
        }
        
        // 合并顺序列表
        ListNode* _merge(ListNode *l1, ListNode *l2) {
            ListNode dummy = ListNode(-1);
            ListNode *tail = &dummy;
            
            while (l1 && l2) {
                if (l1->val < l2->val) {
                    tail->next = l1;
                    tail = l1;
                    l1 = l1->next;
                } else {
                    tail->next = l2;
                    tail = l2;
                    l2 = l2->next;
                }
            }
            
            tail->next = l1 ? l1 : l2;
            
            return dummy.next;
        }
        
        
    public:
        ListNode* sortList(ListNode* head) {
            return v2_sortList(head);
        }
        
    };
}

/**
 
 ### 解题思路
 自底向上的归并排序
 
 ### 复杂度分析
 #### 时间复杂度
 1. 计算元素个数 O(n)
 2. 外层循环 O(log(n))
 3. 内存循环 O(n)
 综述，时间复杂度 O(n) + O(logn) * O(n) = O(nlogn)
 
 #### 空间复杂度 O(1)
 */


void __148_entry() {
    vector<int> nums = {4, 2, 1, 3};
    nums = {-1, 5, 3, 4, 0};
    ListNode *list = create_singlyLinkedList(nums);
    
    ListNode *ret = sortList_148::Solution().sortList(list);
    
    print_singlyLinkedList(ret);
}
