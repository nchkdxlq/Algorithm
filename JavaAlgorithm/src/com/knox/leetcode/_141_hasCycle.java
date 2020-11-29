package com.knox.leetcode;

import com.knox.Asserts;
import com.knox.leetcode.LinkedList.ListNode;

import java.util.HashSet;

public class _141_hasCycle {

    private static class Solution {
        public boolean hasCycle(ListNode head) {
            return hasCycle_v1(head);
//            return hasCycle_v2(head);
        }

        /*
        * 暴力解法
        *
        * 思路
        * 1. 使用一个set记录已经遍历的结点
        * 2. 每遍历到一个结点, 先去set中查找是否已经遍历过
        *   a) 如果set中存在, 则链表有环, return true
        *   b) 如果不存在, 把当前结点放入set中, 接续遍历链表
        *   c) 如果遍历完链表, 这链表没有环
        *
        * 复杂度
        * 时间复杂度: O(n), 遍历一次链表
        * 空间复杂度: O(n), 需要使用set的n个空间记录已经遍历的结点
        *
        * */
        private boolean hasCycle_v1(ListNode head) {
            if (head == null || head.next == null) return false;

            HashSet<ListNode> set = new HashSet<>();
            while (head != null) {
                if (set.contains(head)) {
                    return true;
                } else {
                    set.add(head);
                    head = head.next;
                }
            }
            return false;
        }

        /*
        * 快慢指针
        *
        * 思路
        * 1. 利用快慢指针，慢指针一次走一个结点, 快指针一次走两个结点
        * 2. 初始化时 slow = head, fast = head.next, 避免slow与fast相等
        * 3. 如果存在环, 快慢指针在遍历链表的过程中一定会出现相等, 返回true。
        *    如何理解? 把快慢指针比喻为两个人在环形跑道上跑步, 两人的速度不一样, 一定会相遇。
        * 4. 如果链表没有环, 那么遍历链表一定能结束, 返回false
        *
        * 复杂度
        * 时间复杂度: O(n), 遍历一次链表
        * 空间复杂度: O(1), 只需要存储快慢指针临时变量
        *
        * */
        private boolean hasCycle_v2(ListNode head) {
            if (head == null || head.next == null) return false;

            ListNode slow = head;
            ListNode fast = head.next;
            while (fast != null && fast.next != null) {
                if (slow == fast) {
                    return true;
                }
                slow = slow.next;
                fast = fast.next.next;
            }

            return false;
        }
    }


    public static void main(String[] args) {
        Solution ins = new Solution();

        {
            int[] arr = {3, 2, 0, -4};
            int pos = 1;
            ListNode list = LeetCodeHelper.createCircleSinglyLinkedListFromArray(arr, pos);

            boolean ret = ins.hasCycle(list);
            Asserts.testTrue(ret);
        }


        {
            int[] arr = {2};
            int pos = 0;
            ListNode list = LeetCodeHelper.createCircleSinglyLinkedListFromArray(arr, pos);
            boolean ret = ins.hasCycle(list);
            Asserts.testTrue(ret);
        }


        {
            int[] arr = {3, 5};
            int pos = 1;
            ListNode list = LeetCodeHelper.createCircleSinglyLinkedListFromArray(arr, pos);
            boolean ret = ins.hasCycle(list);
            Asserts.testTrue(ret);
        }


        {
            int[] arr = {};
            int pos = -1;
            ListNode list = LeetCodeHelper.createCircleSinglyLinkedListFromArray(arr, pos);
            boolean ret = ins.hasCycle(list);
            Asserts.testFalse(ret);
        }


        {
            int[] arr = {3, 5};
            int pos = -1;
            ListNode list = LeetCodeHelper.createCircleSinglyLinkedListFromArray(arr, pos);
            boolean ret = ins.hasCycle(list);
            Asserts.testFalse(ret);
        }

    }
}
