package com.knox.list;

public interface List<T> {

    int size();

    boolean isEmpty();

    void append(T element);

    void insert(T element, int index);

    T removeAtIndex(int index);

    void remove(T element);

    int indexOf(T element);

    boolean contains(T element);

    T set(T element, int index);

    T get(int index);

    T first();

    T last();

    void clear();

    String toString();

}
