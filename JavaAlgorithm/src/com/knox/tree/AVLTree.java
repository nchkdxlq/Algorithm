package com.knox.tree;

import com.knox.tree.printer.BinaryTrees;

import java.util.Comparator;

public class AVLTree<T> extends BST<T> {

    private static class AVLNode<T> extends TreeNode<T> {
        int height = 1;

        public AVLNode(T value, TreeNode parent) {
            super(value, parent);
        }

        private int leftHeight() {
            return left == null ? 0 : ((AVLNode<T>)left).height;
        }

        private int rightHeight() {
            return right == null ? 0 : ((AVLNode<T>)right).height;
        }

        public int balanceFactor() {
            return leftHeight() - rightHeight();
        }

        public void updateHeight() {
            height = 1 + Math.max(leftHeight(), rightHeight());
        }

        public AVLNode<T> tallerChild() {
            int leftHeight = leftHeight();
            int rightHeight = rightHeight();
            TreeNode<T> target = null;
            if (leftHeight > rightHeight) {
                target = left;
            } else if (rightHeight > leftHeight) {
                target = right;
            } else {
                target = isLeftChild() ? left : right;
            }
            return (AVLNode<T>)target;
        }

    }


    public AVLTree() {
        this(null);
    }

    public AVLTree(Comparator comparator) {
        super(comparator);
    }


    @Override
    protected TreeNode<T> createNode(T element, TreeNode<T> parent) {
        return new AVLNode<>(element, parent);
    }

    @Override
    protected void afterAdd(TreeNode<T> node) {
        while ((node = node.parent) != null) {
            AVLNode<T> avlNode = (AVLNode<T>)node;
            if (isBalanced(avlNode)) {
                // 更新高度
                updateHeight(avlNode);
            } else {
                // 恢复平衡
                rebalance(avlNode);
                // 整棵树恢复平衡, 退出循环
                break;
            }
        }
    }

    @Override
    protected void afterRemove(TreeNode<T> node) {
        while ((node = node.parent) != null) {
            AVLNode<T> avlNode = (AVLNode<T>)node;
            if (isBalanced(avlNode)) {
                // 更新高度
                updateHeight(avlNode);
            } else {
                // 恢复平衡
                rebalance(avlNode);
            }
        }
    }

    private void rebalance(AVLNode<T> grand) {
//        rebalanced_v1(grand);
        rebalance_v2(grand);
    }

    private void rebalance_v1(AVLNode<T> grand) {
        AVLNode<T> parent = grand.tallerChild();
        AVLNode<T> node = parent.tallerChild();

        if (parent.isLeftChild()) { // L
            if (node.isLeftChild()) { // LL
                LLRotate(node, parent, grand);
            } else { // LR
                LRRotate(node, parent, grand);
            }
        } else { // R
            if (node.isRightChild()) { // RR
                RRRotate(node, parent, grand);
            } else  { // RL
                RLRotate(node, parent, grand);
            }
        }
    }

    private void LLRotate(AVLNode<T> node, AVLNode<T> parent, AVLNode<T> grand) {
        // 旋转
        grand.left = parent.right;
        parent.right = grand;
        TreeNode<T> root = grand.parent;
        if (grand.isLeftChild()) {
            root.left = parent;
        } else if (grand.isRightChild()) {
            root.right = parent;
        } else  {
            this.root = parent;
        }

        // 更新parent
        parent.right.parent = grand;
        grand.parent = parent;
        parent.parent = root;

        // 更新高度
        grand.updateHeight();
        parent.updateHeight();
    }

    private void LRRotate(AVLNode<T> node, AVLNode<T> parent, AVLNode<T> grand) {
        parent.right = node.left;
        grand.left = node.right;
        node.left = parent;
        node.right = grand;

        TreeNode<T> root = grand.parent;
        if (grand.isLeftChild()) {
            root.left = node;
        } else if (grand.isRightChild()) {
            root.right = node;
        } else  {
            this.root = node;
        }

        node.left.parent = parent;
        node.right.parent = grand;
        parent.parent = node;
        grand.parent = node;
        node.parent = root;

        grand.updateHeight();
        parent.updateHeight();
        node.updateHeight();
    }

    private void RRRotate(AVLNode<T> node, AVLNode<T> parent, AVLNode<T> grand) {
        grand.right = parent.left;
        parent.left = grand;
        TreeNode<T> root = grand.parent;
        if (grand.isLeftChild()) {
            root.left = parent;
        } else if (grand.isRightChild()) {
            root.right = parent;
        } else  {
            this.root = parent;
        }

        parent.left.parent = grand;
        grand.parent = parent;
        parent.parent = root;

        grand.updateHeight();
        parent.updateHeight();
    }

    private void RLRotate(AVLNode<T> node, AVLNode<T> parent, AVLNode<T> grand) {
        // g n p
        grand.right = node.left;
        parent.left = node.right;
        node.left = grand;
        node.right = parent;
        TreeNode<T> root = grand.parent;
        if (grand.isLeftChild()) {
            root.left = node;
        } else if (grand.isRightChild()) {
            root.right = node;
        } else  {
            root = node;
        }

        grand.right.parent = grand;
        parent.left.parent = parent;
        node.parent = root;

        grand.updateHeight();
        parent.updateHeight();
        node.updateHeight();
    }

    private void rebalance_v2(AVLNode<T> grand) {
        AVLNode<T> parent = grand.tallerChild();
        AVLNode<T> node = parent.tallerChild();

        if (parent.isLeftChild()) { // L
            if (node.isLeftChild()) { // LL
                rotateRight(grand);
            } else { // LR
                rotateLeft(parent);
                rotateRight(grand);
            }
        } else { // R
            if (node.isRightChild()) { // RR
                rotateLeft(grand);
            } else  { // RL
                rotateRight(parent);
                rotateLeft(grand);
            }
        }
    }

    private void rotateLeft(TreeNode<T> grand) {
        TreeNode<T> parent = grand.right;
        TreeNode<T> child = parent.left;
        grand.right = child;
        parent.left = grand;

        afterRotate(grand, parent, child);
    }

    private void rotateRight(TreeNode<T> grand) {
        TreeNode<T> parent = grand.left;
        TreeNode<T> child = parent.right;
        grand.left = child;
        parent.right = grand;

        afterRotate(grand, parent, child);
    }

    private void afterRotate(TreeNode<T> grand, TreeNode<T> parent, TreeNode<T> child) {
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

        // 更新高度
        updateHeight(grand);
        updateHeight(parent);
    }


    private void rebalance_v3(AVLNode<T> grand) {
        AVLNode<T> parent = grand.tallerChild();
        AVLNode<T> node = parent.tallerChild();
        if (parent.isLeftChild()) { // L
            if (node.isLeftChild()) { // LL
                rotate(grand, node, node.right, parent, parent.right, grand);
            } else { // LR
                rotate(grand, parent, node.left, node, node.right, grand);
            }
        } else { // R
            if (node.isLeftChild()) { // RL
                rotate(grand, grand, node.left, node, node.right, parent);
            } else { // RR
                rotate(grand, grand, parent.left, parent, node.left, node);
            }
        }
    }


    private void rotate(TreeNode<T> r,
                        TreeNode<T> b, TreeNode<T> c,
                        TreeNode<T> d,
                        TreeNode<T> e, TreeNode<T> f) {
        b.right = c;
        if (c != null) c.parent = b;
        updateHeight(b);

        f.left = e;
        if (e != null) e.parent = f;
        updateHeight(f);

        d.left = b;
        d.right = f;
        b.parent = b;
        f.parent = b;
        updateHeight(d);

        if (r.isLeftChild()) {
            r.parent.left = d;
        } else if (r.isRightChild()) {
            r.parent.right = d;
        } else {
            root = d;
        }
    }

    private void updateHeight(TreeNode<T> node) {
        ((AVLNode<T>)node).updateHeight();
    }

    private boolean isBalanced(AVLNode<T> node) {
        return Math.abs(node.balanceFactor()) <= 1;
    }

    public static void main(String[] args) {
        AVLTree<Integer> avl = createAVLTree();
        BinaryTrees.print(avl);

        int[] arr = new int[] {
                61, 92, 91, 35, 53, 32, 83, 28, 90, 18
        };

        for (int i = 0; i < arr.length; i++) {
            avl.remove(arr[i]);
            System.out.println("-------------------------------------【remove data】= " + arr[i]);
            BinaryTrees.print(avl);
        }
    }

    private static AVLTree<Integer> createAVLTree() {
        AVLTree<Integer> avl = new AVLTree<>();
        int[] arr = new int[] {
                61, 92, 91, 35, 53, 32, 83, 28, 90, 18
        };
        for (int i = 0; i < arr.length; i++) {
            avl.add(arr[i]);
        }
        return avl;
    }
}
