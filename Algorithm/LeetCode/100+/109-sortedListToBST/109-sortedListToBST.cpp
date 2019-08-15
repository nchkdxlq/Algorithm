//
//  109-sortedListToBST.cpp
//  LeetCode
//
//  Created by Knox on 2019/8/15.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "109-sortedListToBST.hpp"
#include "STLHelper.hpp"
#include "LinkedListHelper.hpp"
#include "TreeHelper.hpp"

using namespace Singly;



/*
 https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/
 */

namespace sortedListToBST_109 {
    
    class Solution {
    public:
        TreeNode* sortedListToBST(ListNode* head) {
            return sortedListToBST(head, nullptr);
        }
        
    private:
        // 寻找以head为头结点，tail为尾结点但不包含tail链表的构建BST
        TreeNode* sortedListToBST(ListNode* head, ListNode* tail) {
            ListNode *midNode = getMid(head, tail);
            if (midNode == nullptr) return nullptr;
            
            TreeNode* node = new TreeNode(midNode->val);
            node->left = sortedListToBST(head, midNode);
            node->right = sortedListToBST(midNode->next, tail);
            
            return node;
        }
        
        // 寻找以head为头结点，tail为尾结点但不包含tail链表的中间结点
        ListNode* getMid(ListNode* head, ListNode* tail) {
            if (head == tail) return nullptr;
            if (head == nullptr || head->next == nullptr) return head;
            
            auto fast = head;
            auto slow = head;
            
            while(fast && fast->next != tail
                  && fast->next && fast->next->next != tail) {
                slow = slow->next;
                fast = fast->next->next;
            }
            
            return slow;
        }
    };
}



void __109_entry() {
    vector<int> nums = {-10, -3, 0, 5, 9};
    
    ListNode *list = create_singlyLinkedList(nums);
    TreeNode *root = sortedListToBST_109::Solution().sortedListToBST(list);
    vector<int> ret = BTree::inorderTraverse(root);
    cout << "==== 109-sortedListToBST ====" << endl;
    print_vector(ret);
    cout << endl;
}

