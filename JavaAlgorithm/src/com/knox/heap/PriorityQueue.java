package com.knox.heap;

import com.knox.Asserts;
import com.knox.tree.printer.BinaryTrees;

import java.util.Comparator;

public class PriorityQueue<T> {
    private BinaryHeap<T> heap;

    public PriorityQueue(Comparator<T> comparator) {
        heap = new BinaryHeap<>(comparator);
    }

    public PriorityQueue() {
        this(null);
    }

    public int size() {
        return heap.size();
    }

    public boolean isEmpty() {
        return heap.isEmpty();
    }

    public void clear() {
        heap.clear();
    }

    public void enQueue(T element) {
        heap.add(element);
    }

    public T deQueue() {
        return heap.remove();
    }

    public T peek() {
        return heap.get();
    }


    public static void main(String[] args) {
        Integer[] elements = new Integer[] {
                92, 98, 32, 91, 50, 17, 12, 6, 84, 80, 45, 47, 54, 44, 16, 27, 78
        };

        PriorityQueue<Integer> queue = new PriorityQueue<>();
        for (int i = 0; i < elements.length; i++) {
            queue.enQueue(elements[i]);
        }

        Integer[] order = new Integer[] {
                98, 92, 91, 84, 80, 78, 54, 50, 47, 45, 44, 32, 27, 17, 16, 12, 6
        };

        for (int i = 0; i < order.length; i++) {
            Asserts.testEqual(queue.deQueue(), order[i]);
        }
    }
}
