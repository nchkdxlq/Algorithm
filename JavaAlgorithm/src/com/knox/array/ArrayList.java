package com.knox.array;

import com.knox.Asserts;

public class ArrayList<T> {

    private int size;
    private T[] elements;

    private static final int DEFAULT_CAPACITY = 10;
    private static final int ELEMENT_NOT_FOUND = -1;


    public ArrayList(int capacity) {
        capacity = Math.max(capacity, DEFAULT_CAPACITY);
        elements = (T[]) new Object[capacity];
        size = 0;
    }

    public ArrayList() {
        // 调用上面的构造方法
        this(DEFAULT_CAPACITY);
    }

    private void outOfBounds(int index) {
        throw new IndexOutOfBoundsException("Index:" + index + ", Size: " + size);
    }

    private void checkIndex(int index) {
        if (index < 0 || index >= size) {
            outOfBounds(index);
        }
    }

    private void checkIndexForInsert(int index) {
        if (index < 0 || index > size) {
            outOfBounds(index);
        }
    }

    private void ensureCapacity(int capacity) {
        int oldCapacity = elements.length;
        if (oldCapacity >= capacity) return;

        // 新容量为旧容量的1.5倍
        int newCapacity = oldCapacity + (oldCapacity >> 1);
        T[] newElements = (T[]) new Object[newCapacity];

        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        elements = newElements;

        System.out.println("[ capacity from " + oldCapacity + " to " + newCapacity + " ]");
    }

    public void clear() {
        // 清空数组中的元素
        for (int i = 0; i < size; i++) {
            elements[i] = null;
        }
        size = 0;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean contains(T element) {
        return indexOf(element) != ELEMENT_NOT_FOUND;
    }

    public void append(T element) {
        insert(element, size);
    }

    public void insert(T element, int index) {
        checkIndexForInsert(index);
        ensureCapacity(size + 1);
        for (int i = size - 1; i >= index; i--) {
            elements[i+1] = elements[i];
        }
        elements[index] = element;
        size++;
    }

    public T remove(int index) {
        checkIndex(index);
        T target = elements[index];
        for (int i = index + 1; i < size; i++) {
            elements[i-1] = elements[i];
        }
        // 清空数组中最后一个元素
        elements[size-1] = null;
        size--;
        return target;
    }

    public T set(T element, int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index:" + index + ", Size: " + size);
        }
        T old = elements[index];
        elements[index] = element;
        return old;
    }

    public int indexOf(T element) {
        for (int i = 0; i < size; i++) {
            // java中 == 判断对象的内存地址是否相等
            if (elements[i].equals(element)) return i;
        }
        return ELEMENT_NOT_FOUND;
    }

    public T get(int index) {
        checkIndex(index);
        return elements[index];
    }

    public T first() {
        checkIndex(0);
        return elements[0];
    }

    public T last() {
        checkIndex(size-1);
        return elements[size-1];
    }

    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("ArrayList: size=").append(size).append(", [");
        for (int i = 0; i < size; i++) {
            if (i != 0) {
                builder.append(", ");
            }
            builder.append(elements[i]);
        }
        builder.append("]");
        return builder.toString();
    }


    public static void main(String[] args) {
        ArrayList<Integer> list = new ArrayList<>();
        Asserts.testTrue(list.isEmpty());
        Asserts.testEqual(list.size(), 0);

        // append
        list.append(10);
        list.append(20);
        list.append(30);
        list.append(40);
        Asserts.testEqual(list.size(), 4);

        // last first
        Asserts.testEqual(list.last(), 40);
        Asserts.testEqual(list.first(), 10);

        // contains
        Asserts.testTrue(list.contains(30));
        Asserts.testFalse(list.contains(100));

        // insert
        list.insert(13, 1);
        Asserts.testEqual(list.get(1), 13);

        // remove
        int oldSize = list.size();
        Integer ret = list.remove(1);
        Asserts.testEqual(ret, 13);
        int newSize = list.size();
        Asserts.testEqual(newSize, oldSize - 1);

        // set
        Integer setNewValue = 300;
        Integer oldValue = list.get(0);
        Integer setRet = list.set(setNewValue, 0);
        Asserts.testEqual(oldValue, setRet);
        Asserts.testEqual(list.first(), setNewValue);

        // clear
        list.clear();
        Asserts.testEqual(list.size(), 0);
        Asserts.testTrue(list.isEmpty());
    }
}
