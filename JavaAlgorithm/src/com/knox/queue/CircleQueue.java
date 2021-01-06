package com.knox.queue;

import com.knox.tools.Asserts;

import java.util.Arrays;

public class CircleQueue<T> {

    private static int DEFAULT_CAPACITY = 10;

    private T[] elements;
    private int front;
    private int size;

    public CircleQueue() {
        elements = (T[]) new Object[DEFAULT_CAPACITY];
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void enQueue(T element) {
        ensureCapacity(size + 1);
        elements[index(size)] = element;
        size++;
    }

    public T deQueue() {
        T frontElement = elements[front];
        elements[front] = null;
        size--;
        front++;
        return frontElement;
    }

    public T front() {
        return elements[front];
    }

    public void clear() {
        for (int i = 0; i < size; i++) {
            elements[index(i)] = null;
        }
        size = 0;
        front = 0;
    }


    private void ensureCapacity(int capacity) {
        int oldCapacity = elements.length;
        if (capacity <= oldCapacity) return;

        // >> 运算符优先级比较低, 需要使用()
        int newCapacity = oldCapacity + (oldCapacity >> 1);
        T[] newElements = (T[]) new Object[newCapacity];
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[index(i)];
        }
        elements = newElements;
        front = 0;
    }

    // 队列的逻辑index转换到数组的index
    private int index(int i) {
        return (front + i) % elements.length;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(100);
        sb.append("CircleQueue ")
                .append("capacity = ").append(elements.length)
                .append(" size = ").append(size)
                .append(" front = ").append(front)
                .append("  ")
                .append(Arrays.toString(elements));

        return sb.toString();
    }

    public static void main(String[] args) {
        CircleQueue<Integer> queue = new CircleQueue<>();
        Asserts.testTrue(queue.isEmpty());

        int size1 = 5;
        for (int i = 0; i < size1; i++) {
            queue.enQueue( i * 10);
        }
        Asserts.testFalse(queue.isEmpty());
        Asserts.testEqual(queue.size(), size1);
        Asserts.testEqual(queue.front(), 0);
        System.out.println(queue);


        for (int i = 0; i < size1; i++) {
            int ret = queue.deQueue();
            Asserts.testEqual(ret, i*10);
        }
        Asserts.testTrue(queue.isEmpty());
        Asserts.testEqual(queue.size(), 0);
        System.out.println(queue);

        int size2 = 7;
        for (int i = 0; i < size2; i++) {
            queue.enQueue( i * 10);
        }
        Asserts.testEqual(queue.front(), 0);
        System.out.println(queue);

        queue.clear();
        Asserts.testEqual(queue.size(), 0);
        Asserts.testTrue(queue.isEmpty());
        System.out.println(queue);

        int size3 = 20;
        for (int i = 0; i < size3; i++) {
            queue.enQueue( i * 10);
        }
        System.out.println(queue);

        for (int i = 0; i < 10; i++) {
            queue.deQueue();
        }
        for (int i = 0; i < 5; i++) {
            queue.enQueue(i+4);
        }
        System.out.println(queue);

    }
}
