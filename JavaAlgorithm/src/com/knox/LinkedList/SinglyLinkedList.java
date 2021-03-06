package com.knox.LinkedList;

import com.knox.tools.Asserts;
import com.knox.list.AbstractList;
import com.knox.list.List;
import com.knox.util.Util;

/*
* 处理链表的关键
*
* 1. 头结点空时特殊处理
* 2. 插入、删除的下标为0的情况
* 3. 在指定位置插入、删除指定下标节点的关键在于找到上一个结点
* 4. 定义一个根据下标返回对应结点的方法
*
*
* */
public class SinglyLinkedList<T> extends AbstractList<T> {

    private static class Node<T> {
        public T value;
        public Node<T> next;

        public Node(T value) {
            this.value = value;
            this.next = null;
        }
    }

    private Node<T> first;

    // 根据指定的下标返回结点
    private Node<T> nodeForIndex(int index) {
        checkIndex(index);
        Node<T> cur = first;
        int i = 0;
        while (i < index) {
            cur = cur.next;
            i++;
        }
        return cur;
    }

    @Override
    public void append(T element) {
        Node<T> newNode = new Node<>(element);
        if (first == null) {
            first = newNode;
        } else {
            Node<T> cur = first;
            while (cur.next != null) {
                cur = cur.next;
            }
            cur.next = newNode;
        }
        size++;
    }

    @Override
    public void insert(T element, int index) {
        checkIndexForInsert(index);
        Node<T> newNode = new Node<>(element);
        if (index == 0) {
            if (first == null) {
                first = newNode;
            } else {
                Node<T> next = first.next;
                first = newNode;
                newNode.next = next;
            }
        } else {
            Node<T> prev = nodeForIndex(index - 1);
            Node<T> next = prev.next;
            prev.next = newNode;
            newNode.next = next;
        }
        size++;
    }

    @Override
    public void remove(T element) {
        Node<T> cur = first; // 当前访问的结点
        Node<T> pre = null; // 当前结点的上一个结点
        boolean contains = false;
        while (cur != null) {
            if (cur.value == element) {
                contains = true;
                break;
            } else {
                pre = cur;
                cur = cur.next;
            }
        }
        if (contains) {
            if (pre == null) {
                first = cur.next;
            } else {
                pre.next = cur.next;
            }
            size--;
        }
    }

    @Override
    public T removeAtIndex(int index) {
        checkIndex(index);

        Node<T> targetNode;
        if (index == 0) {
            targetNode = first;
            first = first.next;
        } else {
            Node<T> prev = nodeForIndex(index - 1);
            targetNode = prev.next;
            prev.next = targetNode.next;
        }
        size--;
        return targetNode.value;
    }

    @Override
    public int indexOf(T element) {
        int index = 0;
        Node<T> cur = first;
        while (cur != null) {
            if (Util.safeEqual(element, cur.value)) {
                return index;
            } else  {
                cur = cur.next;
                index++;
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
        Node<T> node = nodeForIndex(index);
        return node.value;
    }

    @Override
    public T set(T element, int index) {
        Node<T> node = nodeForIndex(index);
        T oldValue = node.value;
        node.value = element;
        return oldValue;
    }

    @Override
    public T first() {
        checkIndex(0);
        return first.value;
    }

    @Override
    public T last() {
        checkIndex(0);
        Node<T> cur = first;
        while (cur.next != null) {
            cur = cur.next;
        }
        return cur.value;
    }

    @Override
    public void clear() {
        first = null;
        size = 0;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder(100);
        builder.append("SingleLinkedList ");
        builder.append("size:").append(size);
        builder.append(" [ ");

        Node<T> node = first;
        while (node != null) {
            builder.append(node.value).append("->");
            node = node.next;
        }
        builder.append("null ]");
        return builder.toString();
    }

    public static void main(String[] args) {
        List<Integer> list = new SinglyLinkedList<>();

        // isEmpty
        Asserts.testTrue(list.isEmpty());
        Asserts.testEqual(list.size(), 0);

        // append
        list.append(10);
        Asserts.testFalse(list.isEmpty());
        Asserts.testEqual(list.size(), 1);

        // insert
        list.insert(20, 1);
        Asserts.testEqual(list.size(), 2);

        // first, last
        if (!list.isEmpty()) {
            Asserts.testEqual(list.first(), 10);
            Asserts.testEqual(list.last(), 20);
        }

        // get
        int last = list.last();
        int size = list.size();
        Asserts.testEqual(list.get(size - 1), last);

        // set
        last = list.last();
        size = list.size();
        int setNewValue = 90;
        int setRet = list.set(setNewValue, size-1);
        Asserts.testEqual(setRet, last);
        Asserts.testEqual(list.get(size-1), setNewValue);

        // indexOf
        // size:2 [ 10->90->null ]
        Asserts.testEqual(list.indexOf(10), 0);
        Asserts.testEqual(list.indexOf(90), 1);
        Asserts.testEqual(list.indexOf(100), ELEMENT_NOT_FOUND);

        // contains
        list.append(100);
        Asserts.testTrue(list.contains(100));
        Asserts.testFalse(list.contains(200));

        System.out.println(list);

        // removeAtIndex
        // size:3 [ 10->90->100->null ]
        int remove_insert_value = 66;
        list.insert(remove_insert_value, 1);
        int remove_old_size = list.size();
        int remove_pre = list.get(0);
        int remove_next = list.get(2);
        int remove_return = list.removeAtIndex(1);
        Asserts.testEqual(list.size(), remove_old_size -1);
        Asserts.testEqual(remove_insert_value, remove_return);
        Asserts.testEqual(list.get(0), remove_pre);
        Asserts.testEqual(list.get(1), remove_next);

        // clear
        list.append(50);
        list.clear();
        Asserts.testTrue(list.isEmpty());
        Asserts.testEqual(list.size(), 0);

        // remove
        list.clear();
        list.append(10);
        list.append(20);
        list.append(30);
        list.append(20);
        size = list.size();
        // 删除非重复元素
        list.remove(10);
        Asserts.testFalse(list.contains(10));
        Asserts.testEqual(list.size(), size-1);

        // 删除重复元素
        size = list.size();
        list.remove(20);
        Asserts.testTrue(list.contains(20));
        Asserts.testEqual(list.size(), size-1);

        // 删除不存在元素
        size = list.size();
        list.remove(100);
        Asserts.testEqual(list.size(), size);


        System.out.println(list);
    }
}
