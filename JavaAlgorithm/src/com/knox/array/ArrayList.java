package com.knox.array;

import com.knox.Asserts;
import com.knox.list.AbstractList;
import com.knox.list.List;

public class ArrayList<T> extends AbstractList<T> {

    private T[] elements;

    private static final int DEFAULT_CAPACITY = 10;


    public ArrayList(int capacity) {
        capacity = Math.max(capacity, DEFAULT_CAPACITY);
        elements = (T[]) new Object[capacity];
        size = 0;
    }

    public ArrayList() {
        // 调用上面的构造方法
        this(DEFAULT_CAPACITY);
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

    private void trim() {
        int newCapacity = elements.length >> 1;
        // 剩余空间不足一半 || 容量比较小时, 不扩容
        if (size > newCapacity || newCapacity < DEFAULT_CAPACITY) return;

        T[] newElements = (T[]) new Object[newCapacity];
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        elements = newElements;
    }

    @Override
    public void append(T element) {
        insert(element, size);
    }

    @Override
    public void insert(T element, int index) {
        checkIndexForInsert(index);
        ensureCapacity(size + 1);
        for (int i = size - 1; i >= index; i--) {
            elements[i+1] = elements[i];
        }
        elements[index] = element;
        size++;
    }

    @Override
    public T removeAtIndex(int index) {
        checkIndex(index);
        T target = elements[index];
        for (int i = index + 1; i < size; i++) {
            elements[i-1] = elements[i];
        }
        // 清空数组中最后一个元素
        elements[size-1] = null;
        size--;
        trim(); // 缩容
        return target;
    }

    @Override
    public void remove(T element) {
        int targetIndex = indexOf(element);
        if (targetIndex != ELEMENT_NOT_FOUND) {
            removeAtIndex(targetIndex);
        }
    }

    @Override
    public int indexOf(T element) {
        for (int i = 0; i < size; i++) {
            // java中 == 判断对象的内存地址是否相等
            T value = elements[i];
            if (element == null) {
                if (value == null) return i;
            } else {
                if (value != null && value.equals(element)) return i;
            }
        }
        return ELEMENT_NOT_FOUND;
    }

    @Override
    public boolean contains(T element) {
        return indexOf(element) != ELEMENT_NOT_FOUND;
    }

    @Override
    public T get(int index) {
        checkIndex(index);
        return elements[index];
    }

    @Override
    public T set(T element, int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index:" + index + ", Size: " + size);
        }
        T old = elements[index];
        elements[index] = element;
        return old;
    }

    @Override
    public T first() {
        checkIndex(0);
        return elements[0];
    }

    @Override
    public T last() {
        checkIndex(size-1);
        return elements[size-1];
    }

    @Override
    public void clear() {
        // 清空数组中的元素
        for (int i = 0; i < size; i++) {
            elements[i] = null;
        }
        size = 0;
    }

    @Override
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
        List<Integer> list = new ArrayList<>();
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

        // removeAtIndex
        int oldSize = list.size();
        Integer ret = list.removeAtIndex(1);
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

        // remove
        list.clear();
        list.append(10);
        list.append(20);
        list.append(30);
        list.append(20);
        int size = list.size();
        // 删除非重复元素
        list.remove(10);
        Asserts.testFalse(list.contains(10));
        Asserts.testEqual(list.size(), size-1);
    }
}
