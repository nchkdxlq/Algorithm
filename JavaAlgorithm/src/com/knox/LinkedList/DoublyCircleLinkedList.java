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
//        insert_v1(element, index);
        insert_v2(element, index);
    }

    private void insert_v2(T element, int index) {
        checkIndexForInsert(index);

        if (index == size) { // 往最后添加元素, 因为是size, 不能通过index获取对应结点, 单独处理.
            Node<T> oldLast = last;
            Node<T> newNode = new Node<>(element, oldLast, first);
            last = newNode;
            if (oldLast == null) { // 链表为空, newNode的next/prev都指向自己
                newNode.prev = newNode;
                newNode.next = newNode;
                first = newNode;
            } else {
                oldLast.next = newNode;
                first.prev = newNode;
            }
        } else { // 来到else, 说明链表不为空
            // 根据index找到的node为newNode的next
            Node<T> next = nodeForIndex(index);
            Node<T> prev = next.prev;
            /*
            * next为中间结点, 没任何问题, 比较好理解;
            *
            * next为首节点时为什么也成立呢?
            * 1. next是头结点(first), prev就是尾节点(last), newNode.next指向next(first), newNode.prev指向为prev(last)
            * 2. newNode应该为首节点了, 所以next.prev指向newNode, prev.next指向newNode
            * 3. 整体来看, 首结点也属于链表的中间位置, 更普通的中间位置结点一样逻辑处理。
            * */
            Node<T> newNode = new Node<>(element, prev, next);
            prev.next = newNode;
            next.prev = newNode;

            if (index == 0 /* next == first */) {
                first = newNode;
            }
        }
        size++;
    }

    private void insert_v1(T element, int index) {
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
        removeNode_v2(node);
    }

    private void removeNode_v1(Node<T> node) {
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

    private void removeNode_v2(Node<T> node) {
        if (node == null) return;

        if (size == 1) { // 删除元素后链表为空, 所以单独处理
            first = null;
            last = null;
        } else {
            Node<T> prev = node.prev;
            Node<T> next = node.next;
            prev.next = next;
            next.prev = prev;

            if (node == first) {
                first = next;
            }
            if (node == last) {
                last = prev;
            }
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