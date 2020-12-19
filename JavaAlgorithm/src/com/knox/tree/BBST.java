package com.knox.tree;

import java.util.Comparator;

public class BBST<T> extends BST<T> {

    public BBST() {
        this(null);
    }

    public BBST(Comparator comparator) {
        super(comparator);
    }


    protected void rotateLeft(TreeNode<T> grand) {
        TreeNode<T> parent = grand.right;
        TreeNode<T> child = parent.left;
        grand.right = child;
        parent.left = grand;

        afterRotate(grand, parent, child);
    }

    protected void rotateRight(TreeNode<T> grand) {
        TreeNode<T> parent = grand.left;
        TreeNode<T> child = parent.right;
        grand.left = child;
        parent.right = grand;

        afterRotate(grand, parent, child);
    }

    protected void afterRotate(TreeNode<T> grand, TreeNode<T> parent, TreeNode<T> child) {
        // 更新子树的根结点
        TreeNode<T> rootParent = grand.parent;
        if (grand.isLeftChild()) {
            rootParent.left = parent;
        } else if (grand.isRightChild()) {
            rootParent.right = parent;
        } else {
            root = parent;
        }

        // 更新parent
        if (child != null) {
            child.parent = grand;
        }
        grand.parent = parent;
        parent.parent = rootParent;
    }

}
