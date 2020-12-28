package com.knox.map;

import com.knox.Asserts;
import com.knox.model.Key;
import com.knox.model.Person;
import com.knox.model.SubKey1;
import com.knox.model.SubKey2;
import com.knox.tree.printer.BinaryTreeInfo;
import com.knox.tree.printer.BinaryTrees;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Objects;
import java.util.Queue;

public class HashMap<K, V> implements Map<K, V> {

    private static final boolean RED = false;
    private static final boolean BLACK = true;

    private static class Node<K, V> {
        public int hash;
        K key;
        V value;
        boolean color = RED;
        Node<K, V> left;
        Node<K, V> right;
        Node<K, V> parent;
        public Node(K key, V value, Node<K, V> parent) {
            int hash = key == null ? 0 : key.hashCode();
            this.hash = hash ^ (hash >>> 16);
            this.key = key;
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
            return parent != null && this == parent.left;
        }

        public boolean isRightChild() {
            return parent != null && this == parent.right;
        }

        public Node<K, V> sibling() {
            if (isLeftChild()) {
                return parent.right;
            }

            if (isRightChild()) {
                return parent.left;
            }

            return null;
        }

        @Override
        public String toString() {
            return "{" + key + ":" + value + "}";
        }
    }

    // 默认容量
    private static final int DEFAULT_CAPACITY = 1 << 4;
    private static final float DEFAULT_LOAD_FACTOR = 0.75f;

    private int size;
    private Node<K, V>[] table;


    public HashMap() {
        table = new Node[DEFAULT_CAPACITY];
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public void clean() {
        if (size == 0) return;

        for (int i = 0; i < table.length; i++) {
            table[i] = null;
        }
        size = 0;
    }

    @Override
    public V put(K key, V value) {
        resize();

        int index = index(key);
        Node<K, V> root = table[index];
        if (root == null) {
            Node<K, V> node = createNode(key, value, null);
            table[index] = node;
            size++;
            fixAfterPut(node);
            return null;
        }

        Node<K, V> cur = root;
        Node<K, V> parent = root;
        int cmp = 0;
        K k1 = key;
        int h1 = hash(key);
        Node<K, V> result = null;
        boolean searched = false; // 是否已经搜索个这个key
        do {
            parent = cur;
            K k2 = cur.key;
            int h2 = cur.hash;
            if (h1 < h2) {
                cmp = -1;
            } else if (h1 > h2) {
                cmp = 1;
            } else if (Objects.equals(k1, k2)) {
                cmp = 0;
            } else if (k1 != null && k2 != null
                    && k1.getClass() == k2.getClass()
                    && k1 instanceof Comparable
                    && (cmp = ((Comparable)k1).compareTo(k2)) != 0) {
                // ⚠️do nothing, cmp == 0, 只代表大小相等, 但不一定equals, equals为true才表示对象相等⚠️
                // 这里需要执行下面扫描代码
            } else if (searched) { // 已经扫描过
                cmp = System.identityHashCode(k1) - System.identityHashCode(k2);
            } else { // 没有扫描过, 需要扫描左右子树
                /*
                 来到这里, 哈希值相等, 不equals, 也不具备可比较性. 如果发现不能比较的时候, 就直接使用内存地址决定往左往右,会出现相同key的情况。
                 所以，需要先扫描, 再根据内存地址大小决定往左/往右.
                */
                if ( (cur.left != null && (result = node(cur.left, k1)) != null)
                        || (cur.right != null && (result = node(cur.right, k1)) != null) ) {
                    // 已经存在这个key
                    cur = result;
                    cmp = 0;
                } else { // 不存在这个key
                    cmp = System.identityHashCode(k1) - System.identityHashCode(k2);
                    searched = true;
                }
            }


            if (cmp < 0) {
                cur = cur.left;
            } else if (cmp > 0) {
                cur = cur.right;
            } else {
                V originValue = cur.value;
                cur.key = key;
                cur.value = value;
                return originValue;
            }
        } while (cur != null);

        Node<K, V> node = createNode(key, value, parent);
        if (cmp < 0) {
            parent.left = node;
        } else {
            parent.right = node;
        }
        size++;
        fixAfterPut(node);
        return null;
    }

    @Override
    public V get(K key) {
        Node<K, V> node = node(key);
        return node != null ? node.value : null;
    }

    @Override
    public V remove(K key) {
        return remove(node(key));
    }

    @Override
    public boolean containsKey(K key) {
        return node(key) != null;
    }

    @Override
    public boolean containsValue(V value) {
        if (size == 0) return false;

        Queue<Node<K, V>> queue = new LinkedList<>();
        for (int i = 0; i < table.length; i++) {
            Node<K, V> node = table[i];
            if (node == null) continue;

            queue.offer(node);
            while (!queue.isEmpty()) {
                node = queue.poll();
                if (Objects.equals(value, node.value)) {
                    return true;
                }
                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
        }

        return false;
    }

    @Override
    public void traversal(Visitor<K, V> visitor) {
        if (size == 0 || visitor == null) return;

        Queue<Node<K, V>> queue = new LinkedList<>();
        for (int i = 0; i < table.length; i++) {
            Node<K, V> node = table[i];
            if (node == null) continue;

            queue.offer(node);
            while (!queue.isEmpty()) {
                node = queue.poll();
                if (visitor.visit(node.key, node.value)) {
                    return;
                }
                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
        }
    }

    private void resize() {
        if ((float)size / table.length <= DEFAULT_LOAD_FACTOR) return;

        Node<K, V>[] oldTable = table;
        int newLength = oldTable.length << 1;
        table = new Node[newLength];

        for (int i = 0; i < oldTable.length; i++) {
            Node<K, V> root = oldTable[i];
            if (root == null) continue;
            Queue<Node<K, V>> queue = new LinkedList<>();
            queue.offer(root);
            while (!queue.isEmpty()) {
                Node<K, V> node = queue.poll();
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);

                moveNode(node);
            }
        }
    }

    private void moveNode(Node<K, V> node) {
        node.left = null;
        node.right = null;
        node.parent = null;
        color(node, RED);

        int index = index(node);
        Node<K, V> root = table[index];
        if (root == null) {
            table[index] = node;
            fixAfterPut(node);
            return;
        }

        K k1 = node.key;
        int h1 = node.hash;
        int cmp = 0;
        Node<K, V> parent = null;
        do {
            parent = root;
            K k2 = root.key;
            int h2 = root.hash;
            if (h1 < h2) {
                cmp = -1;
            } else if (h1 > h2) {
                cmp = 1;
            } else if (k1 != null && k2 != null
                    && k1 instanceof Comparable
                    && k1.getClass() == k2.getClass()
                    && ((cmp = ((Comparable)k1).compareTo(k2)) != 0) ) {
                // do nothing
            } else {
                cmp = System.identityHashCode(k1) - System.identityHashCode(k2);
            }
            root = cmp < 0 ? root.left : root.right;
        } while (root != null);

        if (cmp < 0) {
            parent.left = node;
        } else {
            parent.right = node;
        }
        node.parent = parent;

        fixAfterPut(node);
    }

    private Node<K, V> node(K key) {
        return node_v2(key);
    }

    private Node<K, V> node(Node<K, V> node, K key) {
        return node_v2(node, key);
    }

    private Node<K, V> node_v1(K key) {
        Node<K, V> node = table[index(key)];
        int h1 = key == null ? 0 : key.hashCode();
        while (node != null) {
            int cmp = compare(key, node.key, h1, node.hash);
            if (cmp < 0) {
                node = node.left;
            } else if (cmp > 0) {
                node = node.right;
            } else {
                return node;
            }
        }
        return null;
    }

    private Node<K, V> node_v2(K key) {
        Node<K, V> root = table[index(key)];
        return root == null ? null : node_v2(root, key);
    }

    // 递归查找
    private Node<K, V> node_v2(Node<K, V> node, K k1) {
        int h1 = hash(k1);
        Node<K, V> result = null;
        int cmp = 0;
        while (node != null) {
            K k2 = node.key;
            int h2 = node.hash;
            if (h1 < h2) {
                node = node.left;
            } else if (h1 > h2) {
                node = node.right;
            } else if (Objects.equals(k1, k2)) { // 哈希值相等先判断是否equals
                return node;
            } else if (k1 != null && k2 != null
                    && k1.getClass() == k2.getClass()
                    && k1 instanceof Comparable
                    && ((cmp = ((Comparable)k1).compareTo(k2)) != 0)) {
                node = cmp < 0 ? node.left : node.right;
                // 对下面else if的注释，哈希值相等、不equals, 也不具备可比较性
            } else if (node.left != null && (result = node_v2(node.left, k1)) != null) { // 在左子树中扫描, 扫描的结果保存在result中
                return result;
            } else {
                // 左节点没找到,只能往右子树找, 所以可以使用node = node.right, 进入新的循环。
                // 相等于右子树递归查找
                node = node.right;
            }
//            } else if (node.right != null && (result = node_v2(node.right, k1)) != null) {
//                return result;
//            } else {
//                // 在左、右子树中都没扫描到, 说明没有相等的节点
//                return null;
//            }
        }
        return null;
    }

    private int hash(K key) {
        if (key == null) return 0;
        int hashcode = Math.abs(key.hashCode());
        return hashcode ^ (hashcode >>> 16);
    }

    private int index(K key) {
        if (key == null) return 0;
        return Math.abs(hash(key)) % (table.length - 1);
    }

    private int index(Node<K, V> node) {
        if (node == null) return 0;
        return Math.abs(node.hash) % (table.length - 1);
    }


    @Override
    public String toString() {
        StringBuffer sb = new StringBuffer(100);
        sb.append("<HashMap> size=");
        sb.append(size);
        sb.append(", {");
        traversal(new Visitor<K, V>() {
            @Override
            public boolean visit(K key, V value) {
                String ret = "\n   <" + key.toString() + ":" + value.toString() +">";
                sb.append(ret);
                return false;
            }
        });
        sb.append("\n}");
        return sb.toString();
    }


    public void print() {
        System.out.println(">>>>>>>> <HashMap> table.length = " + table.length + ", size = " + size + " <<<<<<<<<");
        for (int i = 0; i < table.length; i++) {
            Node<K, V> root = table[i];
            if (root == null) continue;

            System.out.println("\n--------------------【index = " + i + "】-------------------------");
            BinaryTrees.print(new BinaryTreeInfo() {
                @Override
                public Object root() {
                    return root;
                }

                @Override
                public Object left(Object node) {
                    return ((Node<K, V>)node).left;
                }

                @Override
                public Object right(Object node) {
                    return ((Node<K, V>)node).right;
                }

                @Override
                public Object string(Object node) {
                    return node;
                }
            });
        }
    }

    private void fixAfterPut(Node<K, V> node) {
        Node<K, V> parent = node.parent;

        // 添加的是根节点 或者 上溢到达了根节点
        if (parent == null) {
            black(node);
            return;
        }

        // 如果父节点是黑色，直接返回
        if (isBlack(parent)) return;

        Node<K, V> uncle = parent.sibling(); // uncle可能为red, black, null
        Node<K, V> grand = parent.parent;

        if (isRed(uncle)) {
            // 添加到parent度为2的红色节点上
            black(parent);
            black(uncle);
            red(grand);
            fixAfterPut(grand);
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

    private V remove(Node<K, V> node) {
        if (node == null) return null;

        size--;

        V oldValue = node.value;

        if (node.hasTwoChildren()) { // 度为2的节点
            // 找到后继节点
            Node<K, V> s = successor(node);
            // 用后继节点的值覆盖度为2的节点的值
            node.key = s.key;
            node.value = s.value;
            node.hash = s.hash;
            // 删除后继节点
            node = s;
        }

        // 删除node节点（node的度必然是1或者0）
        Node<K, V> replacement = node.left != null ? node.left : node.right;
        int index = index(node);

        if (replacement != null) { // node是度为1的节点
            // 更改parent
            replacement.parent = node.parent;
            // 更改parent的left、right的指向
            if (node.parent == null) { // node是度为1的节点并且是根节点
                table[index] = replacement;
            } else if (node == node.parent.left) {
                node.parent.left = replacement;
            } else { // node == node.parent.right
                node.parent.right = replacement;
            }

            // 删除节点之后的处理
            afterRemove(replacement);
        } else if (node.parent == null) { // node是叶子节点并且是根节点
            table[index] = null;
        } else { // node是叶子节点，但不是根节点
            if (node == node.parent.left) {
                node.parent.left = null;
            } else { // node == node.parent.right
                node.parent.right = null;
            }

            // 删除节点之后的处理
            afterRemove(node);
        }

        return oldValue;
    }

    private void afterRemove(Node<K, V> node) {
        // 如果删除的节点是红色
        // 或者 用以取代删除节点的子节点是红色
        if (isRed(node)) {
            black(node);
            return;
        }

        Node<K, V> parent = node.parent;
        if (parent == null) return;

        // 删除的是黑色叶子节点【下溢】
        // 判断被删除的node是左还是右
        boolean left = parent.left == null || node.isLeftChild();
        Node<K, V> sibling = left ? parent.right : parent.left;
        if (left) { // 被删除的节点在左边，兄弟节点在右边
            if (isRed(sibling)) { // 兄弟节点是红色
                black(sibling);
                red(parent);
                rotateLeft(parent);
                // 更换兄弟
                sibling = parent.right;
            }

            // 兄弟节点必然是黑色
            if (isBlack(sibling.left) && isBlack(sibling.right)) {
                // 兄弟节点没有1个红色子节点，父节点要向下跟兄弟节点合并
                boolean parentBlack = isBlack(parent);
                black(parent);
                red(sibling);
                if (parentBlack) {
                    afterRemove(parent);
                }
            } else { // 兄弟节点至少有1个红色子节点，向兄弟节点借元素
                // 兄弟节点的左边是黑色，兄弟要先旋转
                if (isBlack(sibling.right)) {
                    rotateRight(sibling);
                    sibling = parent.right;
                }

                color(sibling, colorOf(parent));
                black(sibling.right);
                black(parent);
                rotateLeft(parent);
            }
        } else { // 被删除的节点在右边，兄弟节点在左边
            if (isRed(sibling)) { // 兄弟节点是红色
                black(sibling);
                red(parent);
                rotateRight(parent);
                // 更换兄弟
                sibling = parent.left;
            }

            // 兄弟节点必然是黑色
            if (isBlack(sibling.left) && isBlack(sibling.right)) {
                // 兄弟节点没有1个红色子节点，父节点要向下跟兄弟节点合并
                boolean parentBlack = isBlack(parent);
                black(parent);
                red(sibling);
                if (parentBlack) {
                    afterRemove(parent);
                }
            } else { // 兄弟节点至少有1个红色子节点，向兄弟节点借元素
                // 兄弟节点的左边是黑色，兄弟要先旋转
                if (isBlack(sibling.left)) {
                    rotateLeft(sibling);
                    sibling = parent.left;
                }

                color(sibling, colorOf(parent));
                black(sibling.left);
                black(parent);
                rotateRight(parent);
            }
        }
    }

    private Node<K, V> successor(Node<K, V> node) {
        if (node == null) return null;

        // 前驱节点在左子树当中（right.left.left.left....）
        Node<K, V> p = node.right;
        if (p != null) {
            while (p.left != null) {
                p = p.left;
            }
            return p;
        }

        // 从父节点、祖父节点中寻找前驱节点
        while (node.parent != null && node == node.parent.right) {
            node = node.parent;
        }

        return node.parent;
    }



    private void rotateLeft(Node<K, V> grand) {
        Node<K, V> parent = grand.right;
        Node<K, V> child = parent.left;
        grand.right = child;
        parent.left = grand;

        afterRotate(grand, parent, child);
    }

    private void rotateRight(Node<K, V> grand) {
        Node<K, V> parent = grand.left;
        Node<K, V> child = parent.right;
        grand.left = child;
        parent.right = grand;

        afterRotate(grand, parent, child);
    }

    private void afterRotate(Node<K, V> grand, Node<K, V> parent, Node<K, V> child) {
        // 更新子树的根结点
        Node<K, V> rootParent = grand.parent;
        if (grand.isLeftChild()) {
            rootParent.left = parent;
        } else if (grand.isRightChild()) {
            rootParent.right = parent;
        } else {
            table[index(grand)] = parent;
        }

        // 更新parent
        if (child != null) {
            child.parent = grand;
        }
        grand.parent = parent;
        parent.parent = rootParent;
    }

    private int compare(K k1, K k2, int h1, int h2) {
        // 1. 比较hash值, key != null时, hashcode也可能为0
        int result = h1 - h2;
        if (result != 0) return result;

        // 2. 比较equals, equals只能比较是否相等, 不能比较大小
        if (Objects.equals(k1, k2)) return 0;

        // 下面是hashcode相等, 但不equals
        // 3. 比较类名
        if (k1 != null && k2 != null) {
            String k1Cls = k1.getClass().getName();
            String k2Cls = k2.getClass().getName();
            result = k1Cls.compareTo(k2Cls);

            // 3-1. 类名不同
            if (result != 0) return result;

            // 3-2. 同类型且具备可比较性
            if (k1 instanceof Comparable) {
                return ((Comparable)k1).compareTo(k2);
            }
        }

        // 4. 三种情况 a) 同一类型, 但是不具备可比较性. b) k1 == null, k2 != null. c) k1 != null, k2 == null.
        return System.identityHashCode(k1) - System.identityHashCode(k2);
    }

    private Node<K, V> createNode(K key, V value, Node<K, V> parent) {
        return new Node<>(key, value, parent);
    }

    private Node<K, V> color(Node<K, V> node, boolean color) {
        if (node == null) return null;
        node.color = color;
        return node;
    }

    private Node<K, V> red(Node<K, V> node) {
        return color(node, RED);
    }

    private Node<K, V> black(Node<K, V> node) {
        return color(node, BLACK);
    }

    private boolean colorOf(Node<K, V> node) {
        return node == null ? BLACK : node.color;
    }

    private boolean isBlack(Node<K, V> node) {
        return colorOf(node) == BLACK;
    }

    private boolean isRed(Node<K, V> node) {
        return colorOf(node) == RED;
    }



    public static void main(String[] args) {
//        testPut_remove();
//        test_containsKey();
//        test_containsValue();
//        test_get();
//        test_discoverProblem();
        test_map();
    }



    private static void testPut_remove() {
        HashMap<String, Integer> hashMap = new HashMap<>();
        hashMap.put("rose", 10);
        hashMap.put("jack", 20);
        hashMap.put("kangkang", 40);
        hashMap.put("rose", 50);

        System.out.println(hashMap);

        hashMap.remove("rose");
        hashMap.remove("jack");
        hashMap.remove("kangkang");

        System.out.println(hashMap);
    }

    private static void test_containsKey() {
        HashMap<String, Integer> hashMap = new HashMap<>();
        hashMap.put("rose", 10);
        hashMap.put("jack", 20);
        hashMap.put("kangkang", 40);
        hashMap.put("rose", 50);

        Asserts.testTrue(hashMap.containsKey("rose"));
        Asserts.testTrue(hashMap.containsKey("kangkang"));
        Asserts.testFalse(hashMap.containsKey("lilei"));
    }

    private static void test_containsValue() {
        HashMap<String, Integer> hashMap = new HashMap<>();
        hashMap.put("rose", 10);
        hashMap.put("jack", 20);
        hashMap.put("kangkang", 40);
        hashMap.put("rose", 50);

        Asserts.testTrue(hashMap.containsValue(50));
        Asserts.testTrue(hashMap.containsValue(40));
        Asserts.testFalse(hashMap.containsValue(10));
    }

    private static void test_get() {
        HashMap<String, Integer> hashMap = new HashMap<>();
        hashMap.put("rose", 10);
        hashMap.put("jack", 20);
        hashMap.put("kangkang", 40);
        hashMap.put("rose", 50);

        Asserts.testEqual(hashMap.get("rose"), 50);
        Asserts.testEqual(hashMap.get("jack"), 20);
        Asserts.testEqual(hashMap.get("lilei"), null);
    }

    private static void test_discoverProblem() {
        HashMap<Key, Integer> hashMap = new HashMap<>();
        for (int i = 1; i < 20; i++) {
            hashMap.put(new Key(i), i);
        }

        hashMap.put(new Key(4), 100);
        Asserts.testEqual(hashMap.size(), 19);
        Asserts.testEqual(hashMap.get(new Key(4)), 100);
        Asserts.testEqual(hashMap.get(new Key(18)), 18);

        hashMap.print();
    }

    private static void test_person() {
        Person p1 = new Person(10, 170, "Jack");
        Person p2 = new Person(10, 178, "Rose");

        // cmp == 0, 只代表大小相等, 但不一定equals, equals为true才表示对象相等
        int cmp = p1.compareTo(p2);
    }

    private static void test_map() {
        test2();
        test3();
        test4();
        test5();
    }

    static void test2() {
        HashMap<Key, Integer> map = new HashMap<>();
        for (int i = 1; i <= 20; i++) {
            map.put(new Key(i), i);
        }
        for (int i = 5; i <= 7; i++) {
            map.put(new Key(i), i + 5);
        }
        Asserts.testEqual(map.size(), 20);
        Asserts.testEqual(map.get(new Key(4)), 4);
        Asserts.testEqual(map.get(new Key(5)), 10);
        Asserts.testEqual(map.get(new Key(6)), 11);
        Asserts.testEqual(map.get(new Key(7)), 12);
        Asserts.testEqual(map.get(new Key(8)), 8);
    }

    static void test3() {
        HashMap<Object, Integer> map = new HashMap<>();
        map.put(null, 1); // 1
        map.put(new Object(), 2); // 2
        map.put("jack", 3); // 3
        map.put(10, 4); // 4
        map.put(new Object(), 5); // 5
        map.put("jack", 6);
        map.put(10, 7);
        map.put(null, 8);
        map.put(10, null);
        Asserts.testEqual(map.size(),5);
        Asserts.testEqual(map.get(null), 8);
        Asserts.testEqual(map.get("jack"), 6);
        Asserts.testNull(map.get(10));
        Asserts.testNull(map.get(new Object()));
        Asserts.testTrue(map.containsKey(10));
        Asserts.testTrue(map.containsKey(null));
        Asserts.testTrue(map.containsValue(null));
        Asserts.testFalse(map.containsValue(1));
    }

    static void test4() {
        HashMap<Object, Integer> map = new HashMap<>();

        map.put("jack", 1);
        map.put("rose", 2);
        map.put("jim", 3);
        map.put("jake", 4);
        map.remove("jack");
        map.remove("jim");
        for (int i = 1; i <= 10; i++) {
            map.put("test" + i, i);
            map.put(new Key(i), i);
        }
        for (int i = 5; i <= 7; i++) {
            Asserts.testEqual(map.remove(new Key(i)), i);
        }
        for (int i = 1; i <= 3; i++) {
            map.put(new Key(i), i + 5);
        }
        Asserts.testEqual(map.size(), 19);
        Asserts.testEqual(map.get(new Key(1)), 6);
        Asserts.testEqual(map.get(new Key(2)), 7);
        Asserts.testEqual(map.get(new Key(3)), 8);
        Asserts.testEqual(map.get(new Key(4)), 4);
        Asserts.testNull(map.get(new Key(5)));
        Asserts.testNull(map.get(new Key(6)));
        Asserts.testNull(map.get(new Key(7)));
        Asserts.testEqual(map.get(new Key(8)), 8);
        map.print();
    }

    static void test5() {
        HashMap<Key, Integer> map = new HashMap<>();
        for (int i = 1; i <= 20; i++) {
            map.put(new SubKey1(i), i);
        }
        map.put(new SubKey2(1), 5);
        Asserts.testEqual(map.get(new SubKey1(1)), 5);
        Asserts.testEqual(map.get(new SubKey2(1)), 5);
        Asserts.testEqual(map.size(), 20);
    }


}
