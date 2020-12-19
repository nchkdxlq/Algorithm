package com.knox.tree;

public class TreeNode<T> {
    public T value;
    public TreeNode left;
    public TreeNode right;
    public TreeNode parent;

    public TreeNode(T value, TreeNode parent) {
        this.value = value;
        this.parent = parent;
    }

    public boolean isLeaf() {
        return left == null && right == null;
    }

    public boolean hasTwoChildren() {
        return left != null && right != null;
    }

    public boolean isLeftChild() {
        return parent != null && parent.left == this;
    }

    public boolean isRightChild() {
        return parent != null && parent.right == this;
    }

    public TreeNode<T> sibling() {
        if (isLeftChild()) {
            return parent.right;
        } else if (isRightChild()) {
            return parent.left;
        } else {
            return null;
        }
    }
}
