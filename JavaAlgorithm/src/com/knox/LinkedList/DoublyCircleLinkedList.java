package com.knox.LinkedList;

import com.knox.Asserts;
import com.knox.list.AbstractList;
import com.knox.list.List;
import com.knox.util.Util;


public class DoublyCircleLinkedList<T> extends AbstractList<T> {

    private static class Node<T> {
        public T value;
        public Node<T> prev;
        public Node<T> next;

        public Node(T value) {
            this(value, null, null);
        }

        public Node(T value, Node<T> prev, Node<T> next) {
            this.value = value;
            this.next = prev;
            this.prev = next;
        }
    }

    private Node<T> first;
    private Node<T> last;

    // 根据指定的下标返回结点
    private Node<T> nodeForIndex(int index) {
        checkIndex(index);

        Node<T> cur;
        if (index < size >> 1) { // 在前半部分
            cur = first;
            for (int i = 0; i < index; i++) {
                cur = cur.next;
            }
        } else  {
            cur = last;
            for (int i = size - 1; i > index ; i--) {
                cur = cur.prev;
            }
        }
        return cur;
    }

    @Override
    public void insert(T element, int index) {
        checkIndexForInsert(index);

        Node<T> newNode = new Node<>(element);
        if (index == 0) {
            newNode.next = first;
            if (first == null) {
                first = newNode;
                last = newNode;
            } else {
                first.prev = newNode;
                first = newNode;
            }
            first.prev = last;
            last.next = first;
        } else {
            Node<T> prev = nodeForIndex(index - 1);
            Node<T> next = prev.next;

            prev.next = newNode;
            newNode.prev = prev;
            newNode.next = next;
            next.prev = newNode;

            if (index == size) {
                last = newNode;
            }
        }
        size++;
    }

    @Override
    public void remove(T element) {
        Node<T> cur = first; // 当前访问的结点
        Node<T> target = null;
        int index = 0;
        while (index < size) {
            if (cur.value == element) {
                target = cur;
                break;
            } else {
                cur = cur.next;
            }
            index++;
        }

        if (target != null) {
            removeNode(target);
        }
    }


    @Override
    public T removeAtIndex(int index) {
        checkIndex(index);

        Node<T> node = nodeForIndex(index);
        removeNode(node);
        return node.value;
    }

    // 双向链表删除结点模板
    private void removeNode(Node<T> node) {
        if (node == null) return;

        Node<T> prev = node.prev;
        Node<T> next = node.next;
        if (node == first) { // 删除第一个结点
            if (size == 1) {
                first = null;
                last = null;
            } else {
                next.prev = prev;
                prev.next = next;
                first = next;
            }
        } else {
            next.prev = prev;
            prev.next = next;
        }

        size--;
    }

    @Override
    public int indexOf(T element) {
        int index = 0;
        Node<T> cur = first;
        while (index < size) {
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
        return last.value;
    }

    @Override
    public void clear() {
        first = null;
        last = null;
        size = 0;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder(100);
        builder.append("DoublyCircleLinkedList ");
        builder.append("size:").append(size);
        builder.append(" [ ");

        Node<T> node = first;
        int index = 0;
        while (index < size) {
            Node<T> prev = node.prev;
            Node<T> next = node.next;
            String prevStr = "{" + prev.value.toString();
            String nodeStr = "<-" + node.value.toString() + "->";
            String nextStr = next.value.toString() + "}";
            builder.append(prevStr).append(nodeStr).append(nextStr);
            if (index < size - 1) {
                builder.append(", ");
            }
            node = node.next;
            index++;
        }

        builder.append(" ]");
        return builder.toString();
    }

    public static void main(String[] args) {
        List<Integer> list = new DoublyCircleLinkedList<>();

        // isEmpty
        Asserts.testTrue(list.isEmpty());
        Asserts.testEqual(list.size(), 0);

        // append
        test_append(list);

        // insert
        test_insertAtIndex(list);

        // removeAtIndex
        test_removeAtIndex(list);

        test_remove(list);
    }
}