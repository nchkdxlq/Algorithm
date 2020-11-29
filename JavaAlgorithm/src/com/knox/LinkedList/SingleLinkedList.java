package com.knox.LinkedList;

import com.knox.Asserts;

public class SingleLinkedList<T> {

    private static class Node<T> {
        public T value;
        public Node<T> next;

        public Node(T value) {
            this.value = value;
            this.next = null;
        }
    }

    private static final int ELEMENT_NOT_FOUND = -1;

    private int size;
    private Node<T> first;


    private void checkIndex(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index:" + index + ", Size: " + size);
        }
    }

    private void checkIndexForInsert(int index) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException("Index:" + index + ", Size: " + size);
        }
    }


    public SingleLinkedList() { }

    public boolean isEmpty() {
        return size == 0;
    }

    public int size() {
        return size;
    }

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

    public void insert(T element, int index) {
        checkIndexForInsert(index);
        Node<T> newNode = new Node<>(element);
        if (first == null) {
            first = newNode;
        } else {
            int preIndex = index - 1; // 插入位置的前一个位置的下标
            int i = 0;
            Node<T> cur = first;
            while (i < preIndex) {
                cur = cur.next;
                i++;
            }
            // cur为插入位置的前一个结点, next为插入位置的后一个结点
            Node<T> next = cur.next;
            cur.next = newNode;
            newNode.next = next;
        }
        size++;
    }

    public T first() {
        checkIndex(0);
        return first.value;
    }

    public T last() {
        checkIndex(0);
        Node<T> cur = first;
        while (cur.next != null) {
            cur = cur.next;
        }
        return cur.value;
    }

    public T get(int index) {
        checkIndex(index);

        Node<T> cur = first;
        int i = 0;
        while (i < index) {
            cur = cur.next;
            i++;
        }
        return cur.value;
    }


    public T set(T element, int index) {
        checkIndex(index);

        Node<T> cur = first;
        int curIndex = 0;
        while (curIndex < index) {
            cur = cur.next;
            curIndex++;
        }
        T oldValue = cur.value;
        cur.value = element;

        return oldValue;
    }

    public int indexOf(T element) {
        int index = 0;
        Node<T> cur = first;
        while (cur != null) {
            if (cur.value == element) {
                return index;
            }
            cur = cur.next;
            index++;
        }
        return ELEMENT_NOT_FOUND;
    }


    public boolean contains(T element) {
        Node<T> node = first;
        while (node != null) {
            if (element == null) {
                if (node.value == null) return true;
            } else {
                if (node.value != null) {
                    if (node.value.equals(element)) return true;
                }
            }
            node = node.next;
        }
        return false;
    }

    public T remove(int index) {
        checkIndex(index);

        Node<T> cur = first;
        int curIndex = 0;
        while (curIndex < index) {
            cur = cur.next;
            curIndex++;
        }
        size--;
        return cur.value;
    }

    public void clear() {
        first = null;
        size = 0;
    }


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
        SingleLinkedList<Integer> list = new SingleLinkedList<>();

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

        // remove
        // size:3 [ 10->90->100->null ]
        int remove_insert_value = 66;
        list.insert(remove_insert_value, 1);
        int remove_old_size = list.size();
        int remove_return = list.remove(1);
        Asserts.testEqual(list.size(), remove_old_size -1);
        Asserts.testEqual(remove_insert_value, remove_return);

        // clear
        list.append(50);
        list.clear();
        Asserts.testTrue(list.isEmpty());
        Asserts.testEqual(list.size(), 0);
        System.out.println(list);
    }
}
