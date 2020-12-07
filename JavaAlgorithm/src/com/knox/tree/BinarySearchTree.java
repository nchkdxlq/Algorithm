package com.knox.tree;


import com.knox.tree.printer.BinaryTreeInfo;
import com.knox.tree.printer.BinaryTrees;

import java.util.Comparator;

public class BinarySearchTree<T> implements BinaryTreeInfo {

    private TreeNode<T> root;
    private int size;
    private Comparator<T> comparator;

    public BinarySearchTree(Comparator<T> comparator) {
        this.comparator = comparator;
    }

    public BinarySearchTree() {
        this(null);
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void add(T element) {
        elementNotNullCheck(element);

        if (root == null) {
            root = new TreeNode<T>(element, null);
            size++;
            return;
        }

        TreeNode<T> cur = root;
        TreeNode<T> parent = root;
        int cmp = 0;
        while (cur != null) {
            parent = cur;
            cmp = compare(element, cur.value);
            if (cmp < 0) {
                cur = cur.left;
            } else if (cmp > 0) {
                cur = cur.right;
            } else {
                cur.value = element;
                return;
            }
        }

        TreeNode<T> newNode = new TreeNode(element, parent);
        if (cmp < 0) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
        }
        size++;
    }

    public void remove(T element) {

    }

    public boolean contains(T element) {
        return false;
    }

    public void clear() {

    }

    private void elementNotNullCheck(T element) {
        if (element == null) {
            throw new NullPointerException("element should not be null");
        }
    }

    private int compare(T lhs, T rhs) {
        if (comparator != null) {
            return comparator.compare(lhs, rhs);
        } else {
            return ((Comparable<T>)lhs).compareTo(rhs);
        }
    }

    @Override
    public Object root() {
        return root;
    }

    @Override
    public Object left(Object node) {
        return ((TreeNode<T>)node).left;
    }

    @Override
    public Object right(Object node) {
        return ((TreeNode<T>)node).right;
    }

    @Override
    public Object string(Object node) {
        return ((TreeNode<T>)node).value.toString();
    }

    public static void main(String[] args) {

        BinarySearchTree<Integer> bst = new BinarySearchTree<>(new Comparator<Integer>() {
            // 匿名类, java很多内置的数据类型都实现Comparator接口, 自定义的类需要比较才实现该接口
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1.intValue() - o2.intValue();
            }
        });

        for (int i = 0; i < 10; i++) {
            int value = (int)(Math.random() * 100);
            bst.add(value);
        }

        BinaryTrees.print(bst);
    }
}
