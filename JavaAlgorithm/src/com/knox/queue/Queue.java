package com.knox.queue;

import com.knox.Asserts;
import com.knox.LinkedList.DoublyLinkedList;

import java.util.LinkedList;

public class Queue<T> {

    private DoublyLinkedList<T> list = new DoublyLinkedList<>();

    public int size() {
        return list.size();
    }

    public boolean isEmpty() {
        return list.isEmpty();
    }

    public void clear() {
        list.clear();
    }

    public void enQueue(T element) {
        list.append(element);
    }

    public T deQueue() {
        return list.removeAtIndex(0);
    }

    public T front() {
        return list.first();
    }

    public static void main(String[] args) {

        Queue<Integer> queue = new Queue<>();
        queue.enQueue(10);
        queue.enQueue(20);
        queue.enQueue(30);
        queue.enQueue(40);

        Asserts.testEqual(queue.size(), 4);
        Asserts.testFalse(queue.isEmpty());

        LinkedList<Integer> list = new LinkedList();
        list.add(queue.deQueue());
        list.add(queue.deQueue());
        list.add(queue.deQueue());
        list.add(queue.deQueue());
        Asserts.testTrue(queue.isEmpty());

        System.out.println(list);

        queue.enQueue(50);
        Asserts.testEqual(queue.front(), 50);

        queue.clear();
        Asserts.testTrue(queue.isEmpty());
    }

}
