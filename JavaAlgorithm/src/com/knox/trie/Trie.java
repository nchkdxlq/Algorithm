package com.knox.trie;

import com.knox.tools.Asserts;

import java.util.HashMap;

public class Trie<T> {

    private static class Node<T> {
        T value;
        HashMap<Character, Node<T>> children;
        boolean word;
        Character character;
        Node<T> parent;

        public Node(Node<T> parent) {
            this.parent = parent;
        }

        boolean isLeaf() {
            return children == null || children.isEmpty();
        }

        void addChild(Character c, Node<T> child) {
            if (children == null) {
                children = new HashMap<>();
            }
            children.put(c, child);
        }

        Node<T> getChild(Character c) {
            return children == null ? null : children.get(c);
        }

        void removeChildForHashKey(Character haskKey) {
            if (children != null) children.remove(haskKey);
        }

    }

    private Node<T> root = new Node<>(null);
    private int size;

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void clear() {

    }

    public T add(String key, T value) {
        keyCheck(key);

        int length = key.length();
        Node<T> node = root;
        for (int i = 0; i < length; i++) {
            char c = key.charAt(i);
            Node<T> child = node.getChild(c);
            if (child == null) {
                Node<T> newNode = new Node<>(node);
                newNode.character = c;
                node.addChild(c, newNode);
                node = newNode;
            } else {
                node = child;
            }
        }

        if (node.word) { // 当前key已经存在
            T oldValue = node.value;
            node.value = value;
            return oldValue;
        } else {
            node.value = value;
            node.word = true;
            size++;
            return null;
        }
    }

    public T get(String key) {
        keyCheck(key);
        Node<T> node = find(key);
        if (node != null && node.word) {
            return node.value;
        } else {
            return null;
        }
    }

    public T remove(String key) {
        // 找到最后一个节点
        Node<T> node = find(key);
        // 不是单词结尾, 不做任何处理
        if (node == null || !node.word) return null;

        T oldValue = node.value;
        node.value = null;
        node.word = false;
        size--;

        while (node.parent != null) {
            if (node.word || !node.isLeaf()) break;
            node.parent.removeChildForHashKey(node.character);
            node = node.parent;
        }

        return oldValue;
    }

    public boolean contains(String key) {
        keyCheck(key);
        Node<T> node = find(key);
        return node != null && node.word;
    }

    public boolean startWith(String prefix) {
        keyCheck(prefix);
        Node<T> node = find(prefix);
        return node != null;
    }

    private Node<T> find(String key) {
        int length = key.length();
        Node<T> node = root;
        for (int i = 0; i < length; i++) {
            char c = key.charAt(i);
            node = node.getChild(c);
            if (node == null) return null;
        }
        return node;
    }

    private void keyCheck(String key) {
        if (key == null || key.length() == 0) {
            throw new IllegalArgumentException("key must not be empty");
        }
    }

    public static void main(String[] args) {
        Trie<Integer> trie = new Trie<>();
        Asserts.testTrue(trie.isEmpty());
        Asserts.testEqual(trie.size(), 0);

        // test add
        Asserts.testEqual(trie.add("rose", 10), null);
        Asserts.testEqual(trie.size(), 1);

        Asserts.testEqual(trie.add("rose", 20), 10);
        Asserts.testEqual(trie.size(), 1);

        Asserts.testEqual(trie.add("jack", 30), null);
        Asserts.testEqual(trie.size(), 2);

        trie.add("dog", 30);
        trie.add("doggy", 0);
        Asserts.testEqual(trie.size(), 4);

        // test contains
        Asserts.testTrue(trie.contains("dog"));
        Asserts.testTrue(trie.contains("doggy"));
        Asserts.testFalse(trie.contains("dog1"));
        trie.add("学会偷懒", 40);
        trie.add("房间号", 404);
        Asserts.testTrue(trie.contains("房间号"));
        Asserts.testFalse(trie.contains("房间"));

        // test get
        Asserts.testEqual(trie.get("rose"), 20);
        Asserts.testEqual(trie.get("dog"), 30);
        Asserts.testEqual(trie.get("房间号"), 404);
        Asserts.testNull(trie.get("房间"));

        // test startWith
        Asserts.testTrue(trie.startWith("房间号"));
        Asserts.testTrue(trie.startWith("房间"));
        Asserts.testTrue(trie.startWith("ro"));
        Asserts.testTrue(trie.startWith("ros"));
        Asserts.testTrue(trie.startWith("rose"));

        // test remove
        trie.add("ro", 40);
        int size = trie.size();
        Asserts.testEqual(trie.remove("rose"), 20);
        Asserts.testNull(trie.get("rose"));
        Asserts.testEqual(trie.size(), size - 1);
        Asserts.testFalse(trie.startWith("ros"));
        Asserts.testTrue(trie.startWith("ro"));
        Asserts.testTrue(trie.contains("ro"));
        Asserts.testTrue(trie.startWith("r"));

        Asserts.testEqual(trie.remove("房间号"), 404);
        size = trie.size();
        Asserts.testEqual(trie.remove("房间"), null);
        Asserts.testEqual(trie.size(), size);
    }
}
