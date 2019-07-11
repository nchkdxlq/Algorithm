//
//  206-reverseList.cpp
//  LeetCode
//
//  Created by Knox on 2019/7/10.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "206-reverseList.hpp"
#include "stlheaders.h"
#include "LinkedListHelper.hpp"

using namespace Singly;



/**
 
 反转一个单链表。
 
 示例:
 输入: 1->2->3->4->5->NULL
 输出: 5->4->3->2->1->NULL
 
 进阶:
 你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/reverse-linked-list
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 */


namespace reverseList_206 {
    
    class Solution {
    private:
        
        ListNode* v1_reverseList(ListNode* head) {
            ListNode dummy = ListNode(-1);
            
            while (head) {
                ListNode *next = head->next;
                head->next = dummy.next;
                dummy.next = head;
                head = next;
            }
            
            return dummy.next;
        }
        
        
        ListNode* v2_reverseList(ListNode* head) {
            if (head == nullptr || head->next == nullptr) return head;
            
            ListNode *next = head->next;
            ListNode *newHead = v2_reverseList(next);
            // 经过翻转后，next结点变成了子链表的最后一个结点
            next->next = head;
            // head结点放到最后一个结点了，所以next指针需要清空，否者会导致链表为循环链表
            head->next = nullptr;
            
            return newHead;
        }
        
    public:
        ListNode* reverseList(ListNode* head) {
//            return v1_reverseList(head);
            return v2_reverseList(head);
        }
    };
}


/**
 
 ## 迭代解法
 
 ### 解题思路
 
 定义一个dummy哑结点，遍历链表，一次把遍历到的结点插入到dummy结点的后面
 
 
 ### 复杂度分析
 
 #### 时间复杂度
 O(n)
 
 #### 空间复杂度
 只需要使用几个临时变量，空间复杂度为O(1)
 
 
 ## 递归解法
 
 ### 解题思路
 
 把当前结点后的子链表翻转后，然后把当前结点放到翻转后链表最后面。整个链表就全部翻转了。
 
 
 ### 复杂度分析
 假设链表的长度为n

 #### 时间复杂度
 递归的深度为链表的长度n,所以时间复杂度为 O(n)。
 
 #### 空间复杂度
 每层递归需要使用几个临时变量，时间复杂度为O(1)， 递归的最大深度为n，所以空间复杂度为O(n).

 */




void __206_entry() {
    
    vector<int> nums{1,2,3,4,5};
    
    ListNode *list = create_singlyLinkedList(nums);
    ListNode *ret = reverseList_206::Solution().reverseList(list);
    print_singlyLinkedList(ret);
}
