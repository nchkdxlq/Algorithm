package com.knox.queue;

import com.knox.tools.Asserts;
import com.knox.LinkedList.DoublyLinkedList;

public class Deque<T> {

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

    // 从队头入列
    public void enQueueFront(T element) {
        list.insert(element, 0);
    }

    // 从队头出列
    public T deQueueFront() {
        return list.removeAtIndex(0);
    }

    // 从队尾入列
    public void enQueueRear(T element) {
        list.append(element);
    }

    // 从队尾出列
    public T deQueueRear() {
        return list.removeAtIndex(list.size() - 1);
    }

    // 查看队头元素
    public T frontPeek() {
        return list.first();
    }

    // 查看队尾元素
    public T rearPeek() {
        return list.last();
    }

    public static void main(String[] args) {
        Deque<Integer> deque = new Deque<>();
        Asserts.testTrue(deque.isEmpty());

        deque.enQueueRear(10);
        deque.enQueueFront(1);

        Asserts.testEqual(deque.size(), 2);
        Asserts.testEqual(deque.frontPeek(), 1);
        Asserts.testEqual(deque.rearPeek(), 10);

        Asserts.testEqual(deque.deQueueFront(), 1);
        Asserts.testEqual(deque.deQueueRear(), 10);

        deque.clear();
        Asserts.testTrue(deque.isEmpty());
    }

}
