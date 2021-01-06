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

    public void preorder(Visitor<T> visitor) {
        iterator_preorder_v1(visitor);
        // iterator_preorder_v2(visitor);
    }

    private void iterator_preorder_v1(Visitor<T> visitor) {
        if (root == null || visitor == null) return;

        Stack<TreeNode<T>> stack = new Stack<>();
        TreeNode<T> node = root;
        while (true) {
            if (node != null) {
                // 访问结点
                if (visitor.visit(node.value)) return;
                // 将右节点入栈
                if (node.right != null) {
                    stack.push(node.right);
                }
                // 向左走
                node = node.left;
            } else if (stack.isEmpty()) {
                // node为空且stack为空, 结束.
                return;
            } else {
                // node为空且stack不为空, 出栈
                node = stack.pop();
            }
        }
    }

    private void iterator_preorder_v2(Visitor<T> visitor) {
        if (root == null || visitor == null) return;

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

    private void recursive_preorder(TreeNode<T> root, Visitor<T> visitor) {
        if (root == null || visitor.stop) return;

        visitor.stop = visitor.visit(root.value);
        recursive_preorder(root.left, visitor);
        recursive_preorder(root.right, visitor);
    }

    // 中序遍历
    public void inorder(Visitor<T> visitor) {
        // iterator_inorder_v1(visitor);
        iterator_inorder_v2(visitor);
    }

    private void iterator_inorder_v1(Visitor<T> visitor) {
        if (root == null || visitor == null) return;

        TreeNode<T> node = root;
        Stack<TreeNode<T>> stack = new Stack<>();
        while (true) {
            if (node != null) {
                stack.push(node);
                node = node.left;
            } else if (stack.isEmpty()) {
                return;
            } else {
                node = stack.pop();
                if (visitor.visit(node.value)) return;
                node = node.right;
            }
        }
    }

    private void iterator_inorder_v2(Visitor<T> visitor) {
        if (root == null || visitor == null) return;

        TreeNode<T> node = root;
        Stack<TreeNode<T>> stack = new Stack<>();
        while (node != null || !stack.isEmpty()) {
            if (node != null) {
                stack.push(node);
                node = node.left;
            } else {
                node = stack.pop();
                if (visitor.visit(node.value)) return;
                node = node.right;
            }
        }
    }

    private void recursive_inorder(TreeNode<T> root, Visitor<T> visitor) {
        if (root == null || visitor.stop) return;

        recursive_inorder(root.left, visitor);
        if (visitor.stop) return;
        visitor.stop = visitor.visit(root.value);
        recursive_inorder(root.right, visitor);
    }

    // 后序遍历
    public void postorder(TreeNode<T> root, Visitor<T> visitor) {
        iterator_postorder_v1(visitor);
    }

    private void iterator_postorder_v1(Visitor<T> visitor) {
        if (root == null) return;

        Stack<TreeNode<T>> stack = new Stack<>();
        stack.push(root);
        TreeNode<T> prev = null;
        while (!stack.isEmpty()) {
            TreeNode<T> top = stack.peek();
            // 1. 当top是叶子节点
            // 2. top的左右结点都访问过, 也就是, top为prev的父节点 prev.parent == top
            if ((top.left == null && top.right == null)
                    || (prev != null && (top.left == prev || top.right == prev))) {
                prev = stack.pop();
                if (visitor.visit(prev.value)) return;
            } else {
                if (top.right != null) {
                    stack.push(top.right);
                }
                if (top.left != null) {
                    stack.push(top.left);
                }
            }
        }
    }

    private void iterator_postorder_v2(Visitor<T> visitor) {
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

    private void recursive_postorder(TreeNode<T> root, Visitor<T> visitor) {
        if (root == null || visitor.stop) return;

        recursive_postorder(root.left, visitor);
        recursive_postorder(root.right, visitor);
        if (visitor.stop) return;
        visitor.stop = visitor.visit(root.value);
    }


    // 层序遍历
    public void levelOrder(Visitor<T> visitor) {
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


    public static void main(String[] args) {
        test_preorder();
        test_inorder();
        test_postorder();
    }


    private static void test_preorder() {

    }

    private static void test_inorder() {

    }

    private static void test_postorder() {

    }

}
