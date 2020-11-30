package com.knox.leetcode;

import com.knox.leetcode.LinkedList.ListNode;

/*
* 83. 删除排序链表中的重复元素 https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/
*
* 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
*
* 示例 1:
* 输入: 1->1->2
* 输出: 1->2
*
* 示例 2:
* 输入: 1->1->2->3->3
* 输出: 1->2->3
*
* */
public class _083_deleteDuplicates {

    private static class Solution {
        /*
        * 思路
        * 1. 新建一个链表虚拟头结点
        * 2. 把符合条件的结点添加到新链表中
        * 3. 因为是链表是有序的, 只要当前结点不等于新链表最后一个结点就不是重复, 需添加进新链表
        * 4. 需要注意的是, 添加第一个结点时, dummy.next为空; 把结点添加到新链表之前，需要情况当前结点的next.
        *
        * 时间复杂度: O(n)
        * 空间付制度: O(1)
        * */
        public ListNode deleteDuplicates(ListNode head) {
            if (head == null || head.next == null) return head;

            ListNode dummy = new ListNode();
            ListNode tail = dummy;
            while (head != null) {
                ListNode next = head.next;
                if (dummy.next == null || tail.val != head.val) {
                    head.next = null;
                    tail.next = head;
                    tail = head;
                }
                head = next;
            }
            return dummy.next;
        }
    }

    public static void main(String[] args) {
        Solution ins = new Solution();

        {
            int[] arr = {1};
            ListNode list = LeetCodeHelper.createSingleLinkedListFromArray(arr);
            ListNode ret = ins.deleteDuplicates(list);
            LeetCodeHelper.printLinkedList(ret);
        }

        {
            int[] arr = {1, 1, 2};
            ListNode list = LeetCodeHelper.createSingleLinkedListFromArray(arr);
            ListNode ret = ins.deleteDuplicates(list);
            LeetCodeHelper.printLinkedList(ret);
        }

        {
            int[] arr = {1, 1, 2, 3, 3};
            ListNode list = LeetCodeHelper.createSingleLinkedListFromArray(arr);
            ListNode ret = ins.deleteDuplicates(list);
            LeetCodeHelper.printLinkedList(ret);
        }

        {
            int[] arr = {1, 1, 2, 2, 3, 3};
            ListNode list = LeetCodeHelper.createSingleLinkedListFromArray(arr);
            ListNode ret = ins.deleteDuplicates(list);
            LeetCodeHelper.printLinkedList(ret);
        }

        {
            int[] arr = {0, 0, 0, 0, 0, 0};
            ListNode list = LeetCodeHelper.createSingleLinkedListFromArray(arr);
            ListNode ret = ins.deleteDuplicates(list);
            LeetCodeHelper.printLinkedList(ret);
        }
    }
}
