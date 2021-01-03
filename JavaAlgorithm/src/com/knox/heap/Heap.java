package com.knox.heap;

public interface Heap<T> {

    int size(); // 元素数量

    boolean isEmpty(); // 是否为空

    void clear(); // 清空

    void add(T element); // 添加元素

    T get(); // 获取堆顶元素

    T remove(); // 删除堆顶元素

    T replace(T element); // 删除堆顶元素并添加一个元素
}
