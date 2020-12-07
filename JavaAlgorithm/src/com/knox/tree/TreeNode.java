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
}
