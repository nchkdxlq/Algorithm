package com.knox.leetcode;

import com.knox.leetcode.LinkedList.ListNode;

public class LeetCodeHelper {

    public final static ListNode createSingleLinkedListFromArray(int []array) {
        if (array.length == 0) return null;

        int length = array.length;
        ListNode dummy = new ListNode();
        ListNode tail = dummy;
        for (int i = 0; i < length; i++) {
            ListNode node = new ListNode(array[i]);
            tail.next = node;
            tail = node;
        }

        return dummy.next;
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
