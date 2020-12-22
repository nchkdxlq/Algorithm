package com.knox.tree;

import com.knox.tree.printer.BinaryTreeInfo;
import com.knox.tree.printer.BinaryTrees;

import java.util.Comparator;

public class RBTree<T> extends BBST<T> {

    private static final  boolean RED = false;
    private static final  boolean BLACK = true;

    private static class RBNode<T> extends TreeNode<T> {
        public boolean color = RED;
        public RBNode(T value, TreeNode parent) {
            super(value, parent);
        }
    }

    public RBTree() {
        this(null);
    }

    public RBTree(Comparator<T> comparator) {
        super(comparator);
    }


    @Override
    protected void afterAdd(TreeNode<T> node) {
        TreeNode<T> parent = node.parent;

        // 添加的是根节点 或者 上溢到达了根节点
        if (parent == null) {
            black(node);
            return;
        }

        // 如果父节点是黑色，直接返回
        if (isBlack(parent)) return;

        TreeNode<T> uncle = parent.sibling(); // uncle可能为red, black, null
        TreeNode<T> grand = parent.parent;

        if (isRed(uncle)) {
            // 添加到parent度为2的红色节点上
            black(parent);
            black(uncle);
            red(grand);
            afterAdd(grand);
            return;
        }

        // 添加到parent度为1的红色节点上,
        // 下面parent是red, grand为黑色, 叔父节点不是red(可能是black, 也可以为空)
        if (parent.isLeftChild()) { // L
            if (node.isLeftChild()) { // LL
                // 1. parent->black, 2. grand -> red, 3. grand右旋
                black(parent);
                red(grand);
                rotateRight(grand);
            } else { // LR
                // 1. node -> balck, 2. grand -> red,  3. parent左旋 4. grand右旋
                black(node);
                red(grand);
                rotateLeft(parent);
                rotateRight(grand);
            }
        } else { // R
            if (node.isLeftChild()) { // RL
                // 1. node -> balck, 2. grand -> red,  3. parent右旋 4. grand左旋
                black(node);
                red(grand);
                rotateRight(parent);
                rotateLeft(grand);
            } else { // RR
                // 1. parent -> black, 2. grand -> red, 3. grand左旋
                black(parent);
                red(grand);
                rotateLeft(grand);
            }
        }
    }

    @Override
    protected TreeNode<T> createNode(T element, TreeNode<T> parent) {
        return new RBNode<>(element, parent);
    }

    private TreeNode<T> color(TreeNode<T> node, boolean color) {
        if (node == null) return null;
        ((RBNode<T>)node).color = color;
        return node;
    }

    private TreeNode<T> red(TreeNode<T> node) {
        return color(node, RED);
    }

    private TreeNode<T> black(TreeNode<T> node) {
        return color(node, BLACK);
    }

    private boolean colorOf(TreeNode<T> node) {
        return node == null ? BLACK : ((RBNode<T>)node).color;
    }

    private boolean isBlack(TreeNode<T> node) {
        return colorOf(node) == BLACK;
    }

    private boolean isRed(TreeNode<T> node) {
        return colorOf(node) == RED;
    }


    @Override
    public Object string(Object node) {
        RBNode rbNode = (RBNode<T>)node;
        String color = rbNode.color == RED ? "(R)_" : "(B)_";
        return color + super.string(node);
    }

    public static void main(String[] args) {
        testAdd();
    }

    private static void testAdd() {
        RBTree<Integer> rbt = new RBTree<>();
        Integer[] arr = new Integer[] {
                73, 29, 39, 25, 62, 81, 45, 31
        };

        for (int i = 0; i < arr.length; i++) {
            rbt.add(arr[i]);
        }
        BinaryTrees.print(rbt);
    }
}
