package com.knox.leetcode;

import com.knox.leetcode.LinkedList.ListNode;


/*
* 21. 合并两个有序链表 https://leetcode-cn.com/problems/merge-two-sorted-lists/
*
* 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
*
* 示例：
* 输入：1->2->4, 1->3->4
* 输出：1->1->2->3->4->4
*
* */

public class _021_MergeTwoLists {

    private static class Solution {
        public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
            if (l1 == null) return l2;
            if (l2 == null) return l1;

            ListNode dummy = new ListNode();
            ListNode tail = dummy;
            while (l1 != null && l2 != null) {
                if (l1.val < l2.val) {
                    tail.next = l1;
                    tail = l1;
                    l1 = l1.next;
                } else {
                    tail.next = l2;
                    tail = l2;
                    l2 = l2.next;
                }
            }
            tail.next = l1 != null ? l1 : l2;

            return dummy.next;
        }
    }

    public static void main(String[] args) {
        int[] arr1 = {1, 2, 4};
        int[] arr2 = {1, 3, 4};
        ListNode l1 = LeetCodeHelper.createSingleLinkedListFromArray(arr1);
        ListNode l2 = LeetCodeHelper.createSingleLinkedListFromArray(arr2);
        Solution instance = new Solution();
        ListNode ret = instance.mergeTwoLists(l1, l2);
        LeetCodeHelper.printLinkedList(ret);


        int[] arr1_1 = {};
        int[] arr2_1 = {1, 3, 4};
        l1 = LeetCodeHelper.createSingleLinkedListFromArray(arr1_1);
        l2 = LeetCodeHelper.createSingleLinkedListFromArray(arr2_1);
        ret = instance.mergeTwoLists(l1, l2);
        LeetCodeHelper.printLinkedList(ret);


        int[] arr1_2 = {1, 2, 4};
        int[] arr2_2 = {};
        l1 = LeetCodeHelper.createSingleLinkedListFromArray(arr1_2);
        l2 = LeetCodeHelper.createSingleLinkedListFromArray(arr2_2);
        ret = instance.mergeTwoLists(l1, l2);
        LeetCodeHelper.printLinkedList(ret);

        int[] arr1_3 = {};
        int[] arr2_3 = {};
        l1 = LeetCodeHelper.createSingleLinkedListFromArray(arr1_3);
        l2 = LeetCodeHelper.createSingleLinkedListFromArray(arr2_3);
        ret = instance.mergeTwoLists(l1, l2);
        LeetCodeHelper.printLinkedList(ret);

    }
}
