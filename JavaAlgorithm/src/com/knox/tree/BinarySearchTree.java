package com.knox.tree;


import com.knox.Asserts;
import com.knox.tree.printer.BinaryTreeInfo;
import com.knox.tree.printer.BinaryTrees;

import java.util.Comparator;
import java.util.LinkedList;
import java.util.Queue;

public class BinarySearchTree<T> implements BinaryTreeInfo {

    public static abstract class Visitor<T> {
        boolean stop;
        // @return 如果返回true, 就停止遍历
        abstract boolean visit(T element);
    }

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
                // 当node.right == null 时, 后面的所有结点都需要是叶子结点才是完全二叉树
                leaf = true;
            }
        }

        return true;
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

    // 前序遍历
    public void preorder(Visitor<T> visitor) {
        if (visitor == null) return;
        preorder(root, visitor);
    }
    private void preorder(TreeNode<T> root, Visitor<T> visitor) {
        if (root == null || visitor.stop) return;

        visitor.stop = visitor.visit(root.value);
        preorder(root.left, visitor);
        preorder(root.right, visitor);
    }

    // 中序遍历
    public void inorder(Visitor<T> visitor) {
        if (visitor == null) return;
        inorder(root, visitor);
    }
    private void inorder(TreeNode<T> root, Visitor<T> visitor) {
        if (root == null || visitor.stop) return;

        inorder(root.left, visitor);
        if (visitor.stop) return;
        visitor.stop = visitor.visit(root.value);
        inorder(root.right, visitor);
    }

    // 后序遍历
    public void postorder(Visitor<T> visitor) {
        if (visitor == null) return;
        postorder(root, visitor);
    }
    private void postorder(TreeNode<T> root, Visitor<T> visitor) {
        if (root == null || visitor.stop) return;

        postorder(root.left, visitor);
        postorder(root.right, visitor);
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
        return treeNode.value.toString() + "(" + parentStr + ")";
    }

    public static void main(String[] args) {
        BinarySearchTree<Integer> bst = createTree();
        BinaryTrees.print(bst);
        test_preoder(bst);
        test_inoder(bst);
        test_postoder(bst);

        test_isComplete();

//        test_levelOrder();
    }


    private static void test_isComplete() {
        {
            Integer[] arr = new Integer[] {
                    7, 4, 9
            };
            BinarySearchTree<Integer> bst = createTree(arr);
            Asserts.testTrue(bst.isComplete());
        }

        {
            Integer[] arr = new Integer[] {
                    7, 4, 9, 2
            };
            BinarySearchTree<Integer> bst = createTree(arr);
            Asserts.testTrue(bst.isComplete());
        }

        {
            Integer[] arr = new Integer[] {
                    7, 4, 9, 8
            };
            BinarySearchTree<Integer> bst = createTree(arr);
            Asserts.testFalse(bst.isComplete());
        }
    }

    private static void test_preoder(BinarySearchTree<Integer> bst) {
        LinkedList<Integer> ret = new LinkedList<>();
        bst.preorder(new Visitor<Integer>() {
            @Override
            public boolean visit(Integer element) {
                ret.add(element);
                return element == 4;
            }
        });
        System.out.println("preorder : " + ret.toString());
    }

    private static void test_inoder(BinarySearchTree<Integer> bst) {
        LinkedList<Integer> ret = new LinkedList<>();
        bst.inorder(new Visitor<Integer>() {
            @Override
            public boolean visit(Integer element) {
                ret.add(element);
                return false;
            }
        });
        System.out.println("inorder : " + ret.toString());
    }

    private static void test_postoder(BinarySearchTree<Integer> bst) {
        LinkedList<Integer> ret = new LinkedList<>();
        bst.postorder(new Visitor<Integer>() {
            @Override
            public boolean visit(Integer element) {
                ret.add(element);
                return element == 4;
            }
        });
        System.out.println("postorder : " + ret.toString());
    }

    private static void test_levelOrder() {
        BinarySearchTree<Integer> bst = createTree();
        BinaryTrees.print(bst);
        LinkedList<Integer> ret = new LinkedList<>();
        bst.levelOrder(new Visitor<Integer>() {
            @Override
            public boolean visit(Integer element) {
                ret.add(element);
                return element == 5;
            }
        });
        System.out.println("levelOrder : " + ret.toString());
    }

    private static void test1() {
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

    private static BinarySearchTree<Integer> createTree() {
        BinarySearchTree<Integer> bst = new BinarySearchTree<>();
        int[] arr = new int[] {
                7, 4, 9, 2, 5, 8, 11, 1, 3, 10, 12
        };
        for (int i = 0; i < arr.length; i++) {
            bst.add(arr[i]);
        }
        return bst;
    }

    private static BinarySearchTree<Integer> createTree(Integer[] arr) {
        BinarySearchTree<Integer> bst = new BinarySearchTree<>();
        for (int i = 0; i < arr.length; i++) {
            bst.add(arr[i]);
        }
        return bst;
    }
}
