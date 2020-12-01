package com.knox.list;

import com.knox.Asserts;

public abstract class AbstractList<T> implements List<T> {

    public static final int ELEMENT_NOT_FOUND = -1;

    protected int size;

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    protected void outOfBounds(int index) {
        throw new IndexOutOfBoundsException("Index:" + index + ", Size: " + size);
    }

    protected void checkIndex(int index) {
        if (index < 0 || index >= size) {
            outOfBounds(index);
        }
    }

    protected void checkIndexForInsert(int index) {
        if (index < 0 || index > size) {
            outOfBounds(index);
        }
    }

    @Override
    public void append(T element) {
        insert(element, size);
    }

    @Override
    public boolean isValid() {
        return true;
    }

    public static void test_append(List<Integer> list) {
        list.clear();

        list.append(1);
        list.append(4);
        list.append(3);
        list.append(7);

        Asserts.testTrue(list.isValid());

        // 1 -> 4 -> 3 -> 7
        System.out.println("test_append: " + list);
    }

    public static void test_insertAtIndex(List<Integer> list) {
        list.clear();

        list.insert(2, 0);
        list.insert(10, 1);
        list.insert(20, 2);

        list.insert(11, 0);
        list.insert(12, 1);
        list.insert(30, list.size());

        Asserts.testTrue(list.isValid());

        // 11 -> 12 -> 2 -> 10 -> 20 -> 30
        System.out.println("test_insertAtIndex: " + list);
    }

    public static void test_removeAtIndex(List<Integer> list) {
        list.clear();

        list.append(1);
        list.append(2);
        list.append(3);
        list.append(4);
        list.append(7);

        list.removeAtIndex(1);
        list.removeAtIndex(0);
        list.removeAtIndex(list.size()-1);

        Asserts.testTrue(list.isValid());

        // 3 -> 4
        System.out.println("test_removeAtIndex: " + list);
    }

    public static void test_remove(List<Integer> list) {
        list.clear();

        list.append(1);
        list.append(2);
        list.append(2);
        list.append(4);
        list.append(7);
        list.append(5);

        list.remove(1);
        list.remove(5);
        list.remove(2);

        Asserts.testTrue(list.isValid());
        // 2 -> 4 -> 7
        System.out.println("test_remove: " + list);
    }

}
