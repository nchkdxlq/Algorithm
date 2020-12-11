package com.knox.tree;

import com.knox.tree.printer.BinaryTreeInfo;

import java.util.*;


public class BinaryTree<T> implements BinaryTreeInfo {

    public static abstract class Visitor<T> {
        boolean stop;
        // @return 如果返回true, 就停止遍历
        abstract boolean visit(T element);
    }

    protected TreeNode<T> root;
    protected int size;

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void clear() {
        root = null;
        size = 0;
    }

    // 前驱结点 (中序遍历时的前一个结点)
    protected TreeNode<T> predecessor(TreeNode<T> node) {
        if (node == null) return null;

        if (node.left != null) {
            TreeNode<T> p = node.left;
            while (p.right != null) {
                p = p.right;
            }
            return p;
        }

        while (node.parent != null && node == node.parent.left) {
            node = node.parent;
        }
        return node.parent;
    }

    // 后继结点 (中序遍历时的后一个结点)
    protected TreeNode<T> successor(TreeNode<T> node) {
        if (node == null) return null;

        if (node.right != null) {
            TreeNode<T> p = node.right;
            while (p.left != null) {
                p = p.left;
            }
            return p;
        }

        while (node.parent != null && node == node.parent.right) {
            node = node.parent;
        }

        return node.parent;
    }

    // 树的高度
    public int height() {
        if (root == null) return 0;

        Queue<TreeNode<T>> queue = new LinkedList<>();
        queue.offer(root);
        // 存储每一层的元素数量
        int levelSize = 1;
        int height = 0;
        while (!queue.isEmpty()) {
            TreeNode<T> node = queue.poll();
            levelSize--;

            if (node.left != null) {
                queue.offer(node.left);
            }

            if (node.right != null) {
                queue.offer(node.right);
            }

            if (levelSize == 0) { // 遍历完一层, 即将访问下一层
                levelSize = queue.size();
                height++;
            }
        }
        return height;
    }

    // 判断是否为完全二叉树
    public boolean isComplete() {
        if (root == null) return true;

        Queue<TreeNode<T>> queue = new LinkedList<>();
        queue.offer(root);
        boolean leaf = false;
        while (!queue.isEmpty()) {
            TreeNode<T> node = queue.poll();
            if (leaf && !node.isLeaf()) return false;

            if (node.left != null) {
                queue.offer(node.left);
            } else if (node.right != null) { // node.left == null && node.right != null
                return false;
            }

            if (node.right != null) {
                queue.offer(node.right);
            } else {
                // 当node.right == null 时, 后面的所有结点都是叶子结点才是完全二叉树
                leaf = true;
            }
        }

        return true;
    }

    public void preorder(TreeNode<T> root, BinarySearchTree.Visitor<T> visitor) {
        if (root == null) return;

        Stack<TreeNode<T>> stack = new Stack<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            TreeNode<T> node = stack.pop();
            visitor.visit(node.value);

            if (node.right != null) {
                stack.push(node.right);
            }
            if (node.left != null) {
                stack.push(node.left);
            }
        }
    }

    // 中序遍历
    public void inorder(TreeNode<T> root, Visitor<T> visitor) {
        if (root == null) return;

        Stack<TreeNode<T>> stack = new Stack<>();
        TreeNode<T> node = root;
        while (!stack.isEmpty() || node!= null) {
            // 把node和node.left.left...都放进stack中
            if (node != null) {
                stack.push(node);
                node = node.left;
            } else  {
                node = stack.pop();
                visitor.visit(node.value);
                node = node.right;
            }
        }
    }

    // 后序遍历
    public void postoder(TreeNode<T> root, Visitor<T> visitor) {
        if (root == null) return;

        Stack<TreeNode<T>> stack = new Stack<>();
        TreeNode<T> node = root;
        TreeNode<T> prevVisited = null; // 上一个访问的结点

        while (!stack.isEmpty() || node != null) {
            // 把node和node.left.left...都放进stack中
            if (node != null) {
                stack.push(node);
                node = node.left;
            } else {
                // 因为把左节点都放入栈了, 来到这,说明peek没有左节点或者其左节点已经访问过.
                TreeNode<T> peek = stack.peek();
                if (peek.right == null || peek.right == prevVisited) {
                    stack.pop();
                    visitor.visit(peek.value);
                    prevVisited = peek;
                } else {
                    node = peek.right;
                }
            }
        }
    }

    // 层序遍历
    public void levelOrder(BinarySearchTree.Visitor<T> visitor) {
        if (root == null || visitor == null) return;
        Queue<TreeNode<T>> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode<T> node = queue.poll();
            if (visitor.visit(node.value)) return;

            if (node.left != null) {
                queue.offer(node.left);
            }
            if (node.right != null) {
                queue.offer(node.right);
            }
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
        TreeNode<T> treeNode = ((TreeNode<T>)node);
        String parentStr = treeNode.parent == null ? "null" : treeNode.parent.value.toString();
        return treeNode.value.toString() + "_p(" + parentStr + ")";
    }

}
