package com.knox.heap;

import com.knox.tools.Asserts;
import com.knox.tree.printer.BinaryTreeInfo;
import com.knox.tree.printer.BinaryTrees;

import java.util.Comparator;

public class BinaryHeap<T> implements Heap<T>, BinaryTreeInfo {
    private static int DEFAULT_CAPACITY = 10;

    private T[] elements;
    private int size;
    private Comparator<T> comparator;

    public BinaryHeap(Comparator<T> comparator) {
        this.comparator = comparator;
        elements = (T[]) new Object[DEFAULT_CAPACITY];
    }

    public BinaryHeap() {
        this((Comparator<T>)null);
    }

    private BinaryHeap(T[] elements, Comparator<T> comparator) {
        this.comparator = comparator;
        if (elements == null && elements.length == 0) {
            this.elements = (T[]) new Object[DEFAULT_CAPACITY];
        } else {
            int length = elements.length;
            int campacity = Math.max(elements.length, DEFAULT_CAPACITY);
            this.elements = (T[]) new Object[campacity];
            for (int i = 0; i < length; i++) {
                this.elements[i] = elements[i];
            }
            size = length;
            heapify();
        }
    }

    private BinaryHeap(T[] elements) {
        this(elements, null);
    }

    // 批量建堆
    private void heapify() {
        heapify_v2();
    }

    /*
    * 自上而下的上滤, 相当于添加元素的过程
    * */
    private void heapify_v1() {
        for (int i = 0; i < size; i++) {
            siftUp(i);
        }
    }

    /*
    * 自下而上的下滤
    * 原理
    * 1) 首先所有的叶子节点本身就满足二叉堆的性质, 所以叶子节点本身就是二叉堆。
    * 2) 从最后一个非叶子结点开始, 自下而上的下滤, 相当于删除元素用最后一个元素覆盖第一个元素的过程
    * 3) 最后一个非叶子结点的索引index = (size >> 1) - 1
    * */
    private void heapify_v2() {
        int index = (size >> 1) - 1;
        for (int i = index; i >= 0 ; i--) {
            siftDown(i);
        }
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public void clear() {
        for (int i = 0; i < size; i++) {
            elements[i] = null;
        }
        size = 0;
    }

    @Override
    public void add(T element) {
        checkElementNotNull(element);
        ensureCapacity();
        elements[size] = element;
        size++;
        siftUp(size - 1);
    }

    @Override
    public T get() {
        emptyCheck();
        return elements[0];
    }

    @Override
    public T remove() {
        emptyCheck();
        int lastIndex = size - 1;
        T element = elements[0];
        elements[0] = elements[lastIndex];
        elements[lastIndex] = null;
        size--;
        siftDown(0);
        return element;
    }

    @Override
    public T replace(T element) {
        if (size == 0) {
            elements[0] = element;
            size++;
            return null;
        }
        T old = elements[0];
        elements[0] = element;
        siftDown(0);
        return old;
    }

    private void siftUp(int index) {
        // siftUp_v1(index);
        siftUp_v2(index);
    }

    private void siftUp_v1(int index) {
        while (index > 0) {
            int parentIndex = index >> 1;
            T element = elements[index];
            T parent = elements[parentIndex];
            // <= 0, 则满足二叉堆性质
            if (compare(element, parent) <= 0) return;

            // 交互index、parentIndex索引的元素
            T tmp = elements[index];
            elements[index] = elements[parentIndex];
            elements[parentIndex] = tmp;
            index = parentIndex;
        }
    }

    /*
    * 在siftUp_v1中, 每次循环都需要与原始的index处的元素交换。这里可以进行优化,
    * 1. 先记录index处的初始元素
    * 2. 在循环过程中, 用parent元素覆盖index的位置的元素
    * 3. 用初始元素覆盖最终index位置的元素
    * 4. 优化效果, 3log(n)优化为 log(n) + 1
    * */
    private void siftUp_v2(int index) {
        T element = elements[index];
        while (index > 0) {
            int parentIndex = index >> 1;
            T parent = elements[parentIndex];
            // <= 0, 则满足二叉堆性质, 退出循环
            if (compare(element, parent) < 0) break;
            // parent覆盖index处元素
            elements[index] = parent;
            index = parentIndex;
        }
        elements[index] = element;
    }

    private void siftDown(int index) {
        T element = elements[index];
        int half = size >> 1;
        // 第一个叶子节点的索引 == 非叶子节点的数量, 完全二叉树非叶子节点的数量等于 floor(size / 2)
        // index < 第一个叶子节点的索引
        while (index < half) {
            // 位运算符优先级最低的, 需要用括号
            int maxIndex = (index << 1) + 1;
            int rightIndex = maxIndex + 1;
            T maxChild = elements[maxIndex];
            if (rightIndex < size && compare(elements[rightIndex], maxChild) > 0) {
                maxIndex = rightIndex;
                maxChild = elements[rightIndex];
            }
            if (compare(element, maxChild) >= 0) break;

            elements[index] = maxChild;
            index = maxIndex;
        }
        elements[index] = element;
    }

    // 扩容
    private void ensureCapacity() {
        if (elements.length > size) return;

        int newCapacity = elements.length << 1;
        T[] oldElements = elements;
        elements = (T[]) new Object[newCapacity];
        for (int i = 0; i < size; i++) {
            elements[i] = oldElements[i];
        }
    }

    private int compare(T e1, T e2) {
        if (comparator == null) {
            return ((Comparable)e1).compareTo(e2);
        } else {
            return comparator.compare(e1, e2);
        }
    }

    private void checkElementNotNull(T element) {
        if (element == null) {
            throw new IllegalArgumentException("element must not be null");
        }
    }


    private void emptyCheck() {
        if (size == 0) {
            throw new IndexOutOfBoundsException("Heap is empty");
        }
    }

    @Override
    public Object root() {
        return 0;
    }

    @Override
    public Object left(Object node) {
        int index = ((int)node << 1) + 1;
        return index < size ? index : null;
    }

    @Override
    public Object right(Object node) {
        int index = ((int)node << 1) + 2;
        return index < size ? index : null;
    }

    @Override
    public Object string(Object node) {
        return elements[(int)node];
    }

    public static void main(String[] args) {
        BinaryHeap<Integer> heap = new BinaryHeap<>();
        Asserts.testTrue(heap.isEmpty());

        // test add
        heap.add(10);
        Asserts.testEqual(heap.size(), 1);
        Asserts.testEqual(heap.get(), 10);

        heap.add(20);
        Asserts.testEqual(heap.get(), 20);

        heap.add(15);
        heap.add(11);
        heap.add(23);
        heap.add(9);
        Asserts.testEqual(heap.get(), 23);
        Asserts.testEqual(heap.size(), 6);
        Asserts.testFalse(heap.isEmpty());

        BinaryTrees.print(heap);


        // test remove
        heap.remove();
        BinaryTrees.print(heap);
        Asserts.testEqual(heap.get(), 20);

        heap.remove();
        Asserts.testEqual(heap.get(), 15);

        heap.remove();
        Asserts.testEqual(heap.get(), 11);

        heap.remove();
        Asserts.testEqual(heap.get(), 10);

        heap.remove();
        Asserts.testEqual(heap.get(), 9);

        heap.remove();
        Asserts.testTrue(heap.isEmpty());

        test_replace();

        test_remove();

        test_heapify();

        test_topK();
    }

    static void test_remove() {
        BinaryHeap<Integer> heap = new BinaryHeap<>(new Integer[] {
                92, 98, 32, 91, 50, 17, 12, 6, 84, 80, 45, 47, 54, 44, 16, 27, 78
        });
        Integer[] order = new Integer[] {
                98, 92, 91, 84, 80, 78, 54, 50, 47, 45, 44, 32, 27, 17, 16, 12, 6
        };

        for (int i = 0; i < order.length; i++) {
            Asserts.testEqual(heap.remove(), order[i]);
        }
    }

    static void test_replace() {
        BinaryHeap<Integer> heap = new BinaryHeap<>();
        heap.add(15);
        heap.add(11);
        heap.add(23);
        heap.add(9);

        Asserts.testEqual(heap.get(), 23);
        Asserts.testEqual(heap.replace(50), 23);
        Asserts.testEqual(heap.get(), 50);
        BinaryTrees.print(heap);
    }

    static void test_heapify() {
        BinaryHeap<Integer> heap = new BinaryHeap<>(new Integer[] {
                92, 98, 32, 91, 50, 17, 12, 6, 84, 80, 45, 47, 54, 44, 16, 27, 78
        });
        BinaryTrees.print(heap);
    }


    /*
    * 从n个整数中, 找出最大的前K个数(n远大于k)
    * 使用小顶堆, 堆顶元素，为k个元素中最小的一个
    * topK问题时间复杂度为O(nlogk)
    * */
    static void test_topK() {
        Integer[] elements = new Integer[] {
                92, 98, 32, 91, 50, 17, 12, 6, 84, 80, 45, 47, 54, 44, 16, 27, 78
        };
        int topK = 100;

        // 使用小顶堆, 堆顶元素，为k个元素中最小的一个
        BinaryHeap<Integer> heap = new BinaryHeap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });

        for (int i = 0; i < elements.length; i++) {
            if (heap.size < topK) {
                heap.add(elements[i]);
            } else if (elements[i] > heap.get()) {
                heap.replace(elements[i]);
            }
        }
        System.out.println("-------------- TopK ---------------");
        BinaryTrees.print(heap);
    }
}
