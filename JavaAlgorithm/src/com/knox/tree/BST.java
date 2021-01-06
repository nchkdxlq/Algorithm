package com.knox.tree;


import com.knox.tools.Asserts;
import com.knox.tree.printer.BinaryTrees;

import java.util.Comparator;
import java.util.LinkedList;

public class BST<T> extends BinaryTree<T> {

    private Comparator<T> comparator;

    public BST() {
        this(null);
    }

    public BST(Comparator<T> comparator) {
        this.comparator= comparator;
    }

    protected TreeNode<T> createNode(T element, TreeNode<T> parent) {
        return new TreeNode<>(element, parent);
    }

    public void add(T element) {
        elementNotNullCheck(element);

        if (root == null) {
            root = createNode(element, null);
            size++;
            afterAdd(root);
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

        TreeNode<T> newNode = createNode(element, parent);
        if (cmp < 0) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
        }
        size++;
        afterAdd(newNode);
    }

    protected void afterAdd(TreeNode<T> node) {}

    public void remove(T element) {
        TreeNode<T> node = node(element);
        remove(node);
    }

    private void remove(TreeNode<T> node) {
        if (node == null) return;
        size--;

        if (node.hasTwoChildren()) {
            TreeNode<T> s = successor(node);
            node.value = s.value;
            node = s;
        }

        // 统一度为0、1删除逻辑, 度为0时, replacement == null, 下面逻辑也成立
        TreeNode<T> replacement = node.left != null ? node.left : node.right;
        if (replacement != null) { // 度为1的结点
            replacement.parent = node.parent;
        }

        if (node.parent == null) { // 根节点
            root = replacement;
        } else  {
            if (node == node.parent.left) {
                node.parent.left = replacement;
            } else { // node == node.parent.right
                node.parent.right = replacement;
            }
        }

        afterRemove(node);
    }

    // 删除之后处理
    protected void afterRemove(TreeNode<T> node) {}

    public boolean contains(T element) {
        return node(element) != null;
    }

    private TreeNode<T> node(T element) {
        TreeNode<T> node = root;
        while (node != null) {
            int cmp = compare(element, node.value);
            if (cmp == 0) {
                return node;
            } else if (cmp < 0) {
                node = node.left;
            } else  {
                node = node.right;
            }
        }
        return null;
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


    public static void main(String[] args) {

        test_isComplete();
        test_height();

        test_traversal();
    }

    private static void test_traversal() {
        System.out.println("=================== traversal ===================");
        BinarySearchTree<Integer> bst = createTree();
        BinaryTrees.print(bst);
        test_preoder(bst);
        test_inoder(bst);
        test_postoder(bst);
    }

    private static void test_preoder(BinarySearchTree<Integer> bst) {
        LinkedList<Integer> ret = new LinkedList<>();
        bst.preorder(new BinarySearchTree.Visitor<Integer>() {
            @Override
            public boolean visit(Integer element) {
                ret.add(element);
                return false;
            }
        });
        System.out.println("preorder : " + ret.toString());
    }

    private static void test_inoder(BinarySearchTree<Integer> bst) {
        LinkedList<Integer> ret = new LinkedList<>();
        bst.inorder(new BinarySearchTree.Visitor<Integer>() {
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
        bst.postorder(new BinarySearchTree.Visitor<Integer>() {
            @Override
            public boolean visit(Integer element) {
                ret.add(element);
                return false;
            }
        });
        System.out.println("postorder : " + ret.toString());
    }


    private static void test_height() {
        System.out.println("=================== height ===================");
        BinarySearchTree<Integer> bst = randomCreateTree(10);
        BinaryTrees.print(bst);
        System.out.println("height = " + bst.height());
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

    private static BinarySearchTree<Integer> randomCreateTree(int size) {
        Integer[] arr = new Integer[size];
        for (int i = 0; i < size; i++) {
            arr[i] = (int)(Math.random() * 100);
        }
        return createTree(arr);
    }
}
