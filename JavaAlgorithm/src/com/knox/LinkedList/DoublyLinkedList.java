package com.knox.LinkedList;

import com.knox.Asserts;
import com.knox.list.AbstractList;
import com.knox.list.List;
import com.knox.util.Util;


public class DoublyLinkedList<T> extends AbstractList<T> {

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
                last = newNode;
            } else {
                first.prev = newNode;
            }
            first = newNode;
        } else {
            Node<T> prev = nodeForIndex(index - 1);
            Node<T> next = prev.next;
            prev.next = newNode;
            newNode.prev = prev;
            newNode.next = next;

            if (next == null) {
                last = newNode;
            } else {
                next.prev = newNode;
            }
        }

//        if (first == null) {
//            first = newNode;
//        } else {
//            if (index == 0) {
//                newNode.next = first;
//                first = newNode;
//            } else {
//                Node<T> prev = nodeForIndex(index - 1);
//                Node<T> next = prev.next;
//                newNode.next = next;
//                newNode.prev = prev;
//                prev.next = newNode;
//                if (next != null) {
//                    next.prev = newNode;
//                }
//            }
//        }
//        if (index == size) {
//            last = newNode;
//        }

        size++;
    }

    @Override
    public void remove(T element) {
        Node<T> cur = first; // 当前访问的结点
        Node<T> target = null;
        while (cur != null) {
            if (cur.value == element) {
                target = cur;
                break;
            } else {
                cur = cur.next;
            }
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

//        if (index == 0) {
//            first = first.next;
//            first.prev = null;
//            if (index == size - 1) {
//                last = null;
//            }
//        } else if (index == size - 1) {
//            last = node.prev;
//            last.next = null;
//        } else {
//            node.prev.next = node.next;
//            node.next.prev = node.prev;
//        }
//        size--;

        return node.value;
    }

    // 双向链表删除结点模板
    private void removeNode(Node<T> node) {
        if (node == null) return;
        Node<T> prev = node.prev;
        Node<T> next = node.next;

        if (prev == null) {
            first = next;
        } else {
            prev.next = next;
        }

        if (next == null) {
            last = prev;
        } else {
            next.prev = prev;
        }

        size--;
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
        builder.append("SingleLinkedList ");
        builder.append("size:").append(size);
        builder.append(" [ ");

        Node<T> node = first;
        while (node != null) {
            Node<T> prev = node.prev;
            Node<T> next = node.next;
            String prevStr = prev != null ? prev.value.toString() : "null";
            String nextStr = next != null ? next.value.toString() : "null";
            String nodeStr = "{" + prevStr + "<-" + node.value + "->" + nextStr + "}";
            builder.append(nodeStr);
            if (next != null) {
                builder.append(", ");
            }
            node = next;
        }
        builder.append(" ]");
        return builder.toString();
    }

    public static void main(String[] args) {
        List<Integer> list = new DoublyLinkedList<>();

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