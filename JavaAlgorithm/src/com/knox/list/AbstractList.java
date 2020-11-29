package com.knox.list;

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
}
