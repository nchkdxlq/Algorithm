package com.knox.leetcode;

import com.knox.leetcode.LinkedList.ListNode;

/*
* 203. 移除链表元素 https://leetcode-cn.com/problems/remove-linked-list-elements/
* 删除链表中等于给定值 val 的所有节点。
*
* 示例:
* 输入: 1->2->6->3->4->5->6, val = 6
* 输出: 1->2->3->4->5
*
* */
public class _203_removeElements {

    private static class Solution {
        /*
        * 思路
        * 1. 新建一个空节点dummy作为新链表, 使用tail记录新链表的最后一个结点
        * 2. 遍历head, 把不等于val的结点连接到新链表最有一个元素, 并且更新tail;
        *    需要注意的是, 把结点追加到新链表中时, 需要清空该结点的next指针
        * 3. dummy.next为删除val后的链表
        *
        * 时间复杂度: O(n)
        * 空间复杂度: O(1)
        *
        * */
        public ListNode removeElements(ListNode head, int val) {
            ListNode dummy = new ListNode();
            ListNode tail = dummy;
            while (head != null) {
                ListNode next = head.next;
                if (head.val != val) {
                    head.next = null; // 清空next, 如果head.val == val时, 不清空还会指向原链表中在其后面的结点
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
            int[] arr = {1, 2, 6, 3, 4, 5, 6};
            int value = 6;
            ListNode list = LeetCodeHelper.createSingleLinkedListFromArray(arr);
            ListNode ret = ins.removeElements(list, value);
            LeetCodeHelper.printLinkedList(ret);
        }

        {
            int[] arr = {1, 2, 6, 3, 4, 5, 6, 7};
            int value = 6;
            ListNode list = LeetCodeHelper.createSingleLinkedListFromArray(arr);
            ListNode ret = ins.removeElements(list, value);
            LeetCodeHelper.printLinkedList(ret);
        }
    }

}
