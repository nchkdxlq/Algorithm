package com.knox.leetcode;

import com.knox.leetcode.LinkedList.ListNode;

public class LeetCodeHelper {

    public static ListNode createSingleLinkedListFromArray(int []array) {
        return createCircleSinglyLinkedListFromArray(array, -1);
    }
    public static ListNode createCircleSinglyLinkedListFromArray(int []array, int pos) {
        if (array.length == 0) return null;

        ListNode dummy = new ListNode();
        ListNode tail = dummy;
        for (int val : array) {
            ListNode node = new ListNode(val);
            tail.next = node;
            tail = node;
        }

        if (pos >= 0) setSinglyLinkedListCircleAtPosition(dummy.next, pos);

        return dummy.next;
    }

    private static void setSinglyLinkedListCircleAtPosition(ListNode head, int pos) {
        if (head == null && pos < 0) return;

        int index = 0;
        ListNode cur = head;
        // target为需要接环的结点, tail为尾结点
        ListNode target = null, tail = null;
        while (cur != null) {
            if (target == null) {
                if (index == pos) {
                    target = cur;
                } else {
                    index++;
                }
            }

            if (cur.next == null) { // 最后一个结点
                tail = cur;
            }
            cur = cur.next;
        }

        if (target != null) { // pos合法, 找到对应结点
            tail.next = target;
        }
    }


    public static void printLinkedList(ListNode head) {
        StringBuilder builder = new StringBuilder(100);
        builder.append("[ ");

        while (head != null) {
            builder.append(head.val).append(" -> ");
            head = head.next;
        }
        builder.append("null").append(" ]");

        System.out.println(builder.toString());
    }

}
