package com.knox.LinkedList;

import com.knox.tools.Asserts;
import com.knox.list.AbstractList;
import com.knox.list.List;
import com.knox.util.Util;


public class SinglyCircleLinkedList<T> extends AbstractList<T> {

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
    public void insert(T element, int index) {
        checkIndexForInsert(index);
        Node<T> newNode = new Node<>(element);
        if (index == 0) {
            if (first == null) {
                first = newNode;
                newNode.next = first; // 自己的next指向自己
            } else {
                Node<T> last = nodeForIndex(size-1);
                last.next = newNode;
                newNode.next = first;
                first = newNode;
            }
        } else {
            // 能处理插入到最后一个位置的情况, 如果index == size, prev就是last, prev.next就是first。
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
        Node<T> prev = null; // 当前结点的上一个结点
        boolean contains = false;
        int index = 0;
        while (cur != null && index < size) {
            if (cur.value == element) {
                contains = true;
                break;
            } else {
                prev = cur;
                cur = cur.next;
            }
            index++;
        }
        if (contains) {
            if (prev == null) { // prev为空时, 说明是第一个结点; 既然是第一个结点, 就需要修改first.
                if (size == 1) {
                    // size == 1时, 清空first
                    first = null;
                } else {
                    first = cur.next;
                    Node<T> last = nodeForIndex(size-1);
                    last.next = first;
                }
            } else {
                prev.next = cur.next;
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
            if (size == 1) {
                first = null;
            } else {
                first = first.next;
                Node<T> last = nodeForIndex(size-1);
                last.next = first;
            }
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
        return nodeForIndex(size-1).value;
    }

    @Override
    public void clear() {
        first = null;
        size = 0;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder(100);
        builder.append("SinglyCircleLinkedList ");
        builder.append("size:").append(size);
        builder.append(" [ ");

        Node<T> node = first;
        int index = 0;
        while (index < size) {
            String nodeStr = "{" + node.value + "-" + node.next.value + "}";
            builder.append(nodeStr);
            if (index < (size-1)) builder.append(", ");

            node = node.next;
            index++;
        }
        builder.append(" ]");
        return builder.toString();
    }

    public static void main(String[] args) {
        List<Integer> list = new SinglyCircleLinkedList<>();

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
