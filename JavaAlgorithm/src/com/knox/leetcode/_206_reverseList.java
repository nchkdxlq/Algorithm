package com.knox.leetcode;

import com.knox.leetcode.LinkedList.ListNode;


/*
* 206. 反转链表 https://leetcode-cn.com/problems/reverse-linked-list/
*
* 反转一个单链表。
* 输入: 1->2->3->4->5->NULL
* 输出: 5->4->3->2->1->NULL
*
* */
public class _206_reverseList {

    private static class Solution {
        public ListNode reverseList(ListNode head) {
//            return reverseList_v1(head);
            return reverseList_v2(head);
        }

        // 递归结果
        private ListNode reverseList_v1(ListNode head) {
            if (head == null || head.next == null) return head;

            ListNode next = head.next;
            // 经过翻转, next结点已经是翻转后链表的尾结点了, 所以只需要把next.next指向head
            // 但此时, head.next还有值, 所以需要把它清空
            ListNode newHead = reverseList_v1(next);
            next.next = head;
            head.next = null;
            return newHead;
        }

        // 迭代解法
        private ListNode reverseList_v2(ListNode head) {
            if (head == null || head.next == null) return head;

            ListNode dummy = new ListNode();
            ListNode node = head.next;
            head.next = null; //第一个结点翻转后会变为最后一个结点, 需要把next清空。
            dummy.next = head;
            while (node != null) {
                ListNode next = node.next;
                // 当前结点放到新链表的第一个位置
                node.next = dummy.next;
                dummy.next = node;
                node = next;
            }

            return dummy.next;
        }
    }


    public static void main(String[] args) {
        Solution ins = new Solution();

        int[] arr1 = {1, 2, 3, 4, 5};
        ListNode head = LeetCodeHelper.createSingleLinkedListFromArray(arr1);
        ListNode ret = ins.reverseList(head);
        LeetCodeHelper.printLinkedList(ret);


    }
}
