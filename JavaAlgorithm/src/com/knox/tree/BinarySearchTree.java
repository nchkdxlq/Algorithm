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

    // 前驱结点 (中序遍历时的前一个结点)
    private TreeNode<T> predecessor(TreeNode<T> node) {
        if (node == null) return null;

        // 前驱节点在左子树当中（left.right.right.right....）
        if (node.left != null) {
            TreeNode<T> p = node.left;
            while (p.right != null) {
                p = p.right;
            }
            return p;
        }

        /*
        * 在父节点、祖父结点中寻找前驱结点
        *
        * 存在parent, 并且node == node.parent.left, 还需要往父节点找
        * 1. 当node == node.parent.right时, node.parent为前驱结点
        * 2. 当一直找到根节点, 即node.parent == null时, 没有前驱结点
        * */
        while (node.parent != null && node == node.parent.left) {
            node = node.parent;
        }
        return node.parent;
    }

    // 后继结点 (中序遍历时的后一个结点)
    private TreeNode<T> successor(TreeNode<T> node) {
        if (node == null) return null;

        if (node.right != null) {
            TreeNode<T> p = node.right;
            while (p.left != null) {
                p = p.left;
            }
            return p;
        }

        // 一直往父节点找, 一直找到node结点是父结点的左结点, 此时父节点就是后驱结点
        while (node.parent != null && node == node.parent.right) {
            node = node.parent;
        }

        return node.parent;
    }

    // 树的高度
    public int height() {
//        return height_v1(root);
        return height_v2();
    }

    /*
    * 迭代解法
    *
    * 思路:
    * 使用层序遍历, 遍历完一层height就加1
    * 1. 如何知道遍历完一层呢？需要知道一层的结点个数levelSize
    * 2. 如何知道一层的结点个数呢？ 第一层是已知的, 把根结点加入队列, 结点数量为1
    * 3. 从队列中取出元素, levelSize减1, 并且把结点的左右结点加入队列
    * 4. 当levelSize == 0时, 一层已经遍历完, 此时queue.size()为下一层的结点数量, height也需要加1
    *
    * */
    private int height_v2() {
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

    /* 递归
     *
     * 思路：
     * 1. 先递归求出左子树的高度
     * 2. 再递归求出右子树的高度
     * 3. 子树高度较大值+1就是树的高度
     * */
    private int height_v1(TreeNode<T> node) {
        if (node == null) return 0;

        int leftHeight = height_v1(node.left);
        int rightHeight = height_v1(node.right);
        return Math.max(leftHeight, rightHeight) + 1;
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
//        BinarySearchTree<Integer> bst = createTree();
//        BinaryTrees.print(bst);
//        test_preoder(bst);
//        test_inoder(bst);
//        test_postoder(bst);
//
//        test_isComplete();

//        test_height();

        test_predecessor();

//        test_levelOrder();
    }

    private static void test_predecessor() {
        Integer[] arr = new Integer[] {
                8, 4, 13, 2, 6, 10, 1, 3, 5, 7, 9, 12, 11
        };
        BinarySearchTree<Integer> bst = createTree(arr);
        BinaryTrees.print(bst);

        {
            // node.left != null
            TreeNode<Integer> node = bst.root.left; //4
            TreeNode<Integer> target = node.left.right; // 3
            TreeNode<Integer> ret = bst.predecessor(node);
            Asserts.testEqual(ret, target);
        }

        {
            // node.left == null && node,parent != null
            TreeNode<Integer> node = bst.root.right.left.left; // 9
            TreeNode<Integer> target = bst.root; // 8
            TreeNode<Integer> ret = bst.predecessor(node);
            Asserts.testEqual(ret, target);

            node = bst.root.left.left.left; // 1
            target = null; // 1
            ret = bst.predecessor(node);
            Asserts.testEqual(ret, target);
        }

        {
            arr = new Integer[] {
                    8, 13, 10, 9, 12, 11
            };
            bst = createTree(arr);
            BinaryTrees.print(bst);
            // node.left == null && node,parent == null, 没有左子树的根结点
            TreeNode<Integer> node = bst.root;
            TreeNode<Integer> ret = bst.predecessor(node);
            TreeNode<Integer> target = null;
            Asserts.testEqual(ret, target);
        }
    }


    private static void test_height() {
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

    private static BinarySearchTree<Integer> randomCreateTree(int size) {
        Integer[] arr = new Integer[size];
        for (int i = 0; i < size; i++) {
            arr[i] = (int)(Math.random() * 100);
        }
        return createTree(arr);
    }
}
