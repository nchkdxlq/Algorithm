//
//  BST.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/2.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

template<typename Key, typename Value>
class BST {
    
private:
     struct Node {
         Key key;
         Value value;
         Node *left;
         Node *right;
         
         Node(Key key, Value value) {
             this->key = key;
             this->value = value;
             this->left = this->right = nullptr;
         }
         
         Node(Node *node) {
             this->key = node->key;
             this->value = node->value;
             this->left = node->left;
             this->right = node->right;
         }
         
    };
    
    Node *m_root;
    int m_count;

    
    
public:
    
    BST() {
        m_root = nullptr;
        m_count = 0;
    }
    
    ~BST() {
        destruct(m_root);
    }
    
    int size() {
        return m_count;
    }
    
    bool isEmpty() {
        return m_root == nullptr;
    }
    
    void insert(Key key, Value value) {
//        m_root = __insert(m_root, key, value);
        insert_v2(key, value);
    }

    void insert_v2(Key key, Value value) {
        
        Node **node = &m_root;
        while (true) {
            if (*node == nullptr) {
                *node = new Node(key, value);
                m_count++;
                return;
            }
            
            if (key == (*node)->key) {
                (*node)->value = value;
                return;
            } else if (key < (*node)->key) {
                node = &(*node)->left;
            } else { // key > node->key
                node = &(*node)->right;
            }
        }
    }
    
    void insert_v3(Key key, Value value) {
        if (m_root == nullptr) {
            m_root = new Node(key, value);
            m_count++;
            return;
        }
        
        Node *cur = m_root;
        
        while (cur) {
             if (key < cur->key) {
                 if (cur->left == nullptr) {
                     cur->left = new Node(key, value);
                     m_count++;
                     break;
                 } else {
                     cur = cur->left;
                 }
            } else if (key > cur->key) {
                if (cur->right == nullptr) {
                    cur->right = new Node(key, value);
                    m_count++;
                    break;
                } else {
                    cur = cur->right;
                }
            } else { // cur->key == key
                cur->value = value;
                break;
            }
        }
    }
    
    
    bool contain(Key key) {
        return __contain(m_root);
    }
    
    
    Value* search(Key key) {
        return __search(m_root, key);
    }
    
    
    Value* search_v2(Key key) {
        
        Node *node = m_root;
        while (node) {
            if (node->key == key) {
                return &(node->value);
            } else if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        
        return nullptr;
    }
    
    // 深度优先遍历
    
    void preTraverse() {
        __preTraverse(m_root);
        cout << endl;
    }
    
    void midTraverse() {
        __midTraverse(m_root);
        cout << endl;
    }
    
    void postTraverse() {
        __postTraverse(m_root);
        cout << endl;
    }
    
    
    // 广度优先遍历
    void levelTraverse() {
        if (isEmpty()) {
            return;
        }
        queue<Node *> q;
        q.push(m_root);
        
        while (!q.empty()) {
            Node *node = q.front();
            q.pop();
            cout << node->key << " ";
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
        
        cout << endl;
    }
    
    
    // 最值
    Key minimum() {
        assert(m_root != nullptr);
        
        Node *min = __min_v2(m_root);
        return min->key;
    }
    
    Key maximum() {
        assert(m_root != nullptr);
        
        Node *max = __max_v2(m_root);
        return max->key;
    }
    
    // 删除
    
    void remove(Key key) {
        Node *node = m_root;
        Node *parentNode = nullptr;
        bool isLeft = true;
        
        while (node) {
            if (key == node->key) {
                Node *targetNode = node;
                
                if (node->left) {
                    targetNode = node->left;
                    parentNode = node;
                    isLeft = true;
                    // 找以targetNode根节点值最大的节点
                    while (targetNode) {
                        if (targetNode->right) {
                            parentNode = targetNode;
                            targetNode = targetNode->right;
                            isLeft = false;
                        } else {
                            break;
                        }
                    }
                } else if (node->right) {
                    targetNode = node->right;
                    parentNode = node;
                    isLeft = false;
                    while (targetNode) {
                        if (targetNode->left) {
                            parentNode = targetNode;
                            targetNode = targetNode->left;
                            isLeft = true;
                        } else {
                            break;
                        }
                    }
                }
                
                if (targetNode == node) {  // 删除的是叶子节点
                    if (parentNode) { // 删除的不是根节点
                        isLeft ? parentNode->left = nullptr : parentNode->right = nullptr;
                    } else {
                        m_root = nullptr;
                    }
                    delete targetNode;
                } else {
                    node->key = targetNode->key;
                    node->value = targetNode->value;
                    isLeft ? parentNode->left = targetNode->left : parentNode->right = nullptr;
                    delete targetNode;
                }
                m_count--;
                break;
            }
            
            parentNode = node;
            if (key < node->key) {
                node = node->left;
                isLeft = true;
            } else {
                node = node->right;
                isLeft = false;
            }
        }
    }
    
    
    void remove_v2(Key key) {
        m_root = __remove_v2(m_root, key);
    }
    
    void removeMax() {
        
        if (isEmpty()) {
            return;
        }
        
        Node *max = m_root;
        Node *parent = nullptr;
        
        while (max->right) {
            parent = max;
            max = max->right;
        }
        
        if (parent == nullptr) { // 根节点为最大值
            m_root = m_root->left;
        } else {
            // 最大值节点可能还有左节点，需要赋值给父节点的右节点
            parent->right = max->left;
        }
        
        delete max;
        max = nullptr;
        m_count--;
    }
    
    void removeMax_v2() {
        assert(m_root != nullptr);
        
        __removeMax_v2(m_root);
    }
    
    
    void removeMin() {
        if (isEmpty()) {
            return;
        }
        
        Node *min = m_root;
        Node *parent = nullptr;
        while (min->left) {
            parent = min;
            min = min->left;
        }
        
        if (parent == nullptr) { // 根节点为最小值
            m_root = m_root->right;
        } else { // 最小值节点可能还有右节点，需要赋值给父节点的左节点
            parent->left = min->right;
        }
        
        delete min;
        min = nullptr;
        m_count--;
    }
    
    void removeMin_v2() {
        assert(m_root != nullptr);
        __removeMin_v2(m_root);
    }
    
private:
    
    
    /**
     递归析构以node为根的搜索二叉树

     @param node 搜索二叉树的根节点
     */
    void destruct(Node *node) {
        
        if (node == nullptr) {
            return;
        }
        Node *left = node->left;
        Node *right = node->right;
        
        destruct(left);
        destruct(right);
        
        delete node;
        m_count--;
    }
    
    Node* __insert(Node *node, Key key, Value value) {
        
        if (node == nullptr) {
            m_count++;
            return new Node(key, value);
        }
        
        if (key == node->key) {
            node->value = value;
        } else if (key < node->key) {
            node->left = __insert(node->left, key, value);
        } else { // key > node->key
            node->right = __insert(node->right, key, value);
        }
        
        return node;
    }
    
    void __insert_v2(Node **node_p, Key key, Value value) {
        
        if (*node_p == nullptr) {
            *node_p = new Node(key, value);
            m_count++;
            return;
        }
        
        if (key == (*node_p)->key) {
            (*node_p)->value = value;
            return;
        } else if (key < (*node_p)->key) {
            node_p = &(*node_p->left);
        } else {
            node_p = &(*node_p->right);
        }
        __insert_v2(node_p, key, value);
    }
    
    
    bool __contain(Node *node, Key key) {
        if (node == nullptr) {
            return false;
        }
        
        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return __contain(node->key, key);
        } else {
            return __contain(node->right, key);
        }
    }
    
    
    /**
     在以node为根的搜索二叉树中查找给定key对应的value

     @param node 搜索二叉树的根
     @param key 搜索的key
     @return value的地址，如果没找到返回nullptr
     */
    Value* __search(Node *node, Key key) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (key == node->key) {
            return &(node->value);
        } else if (key < node->key) {
            return __search(node->left, key);
        } else {
            return __search(node->right, key);
        }
    }
    
    
    /**
     对以node为根节点的二叉树进行 先序遍历、中序遍历、后续遍历

     @param node 二叉树的根节点
     */
    void __preTraverse(Node *node) {
        
        if (node == nullptr) {
            return;
        }
        
        cout << node->key << " ";
        __preTraverse(node->left);
        __preTraverse(node->right);
    }
    
    void __midTraverse(Node *node) {
        
        if (node == nullptr) {
            return;
        }
        
        __midTraverse(node->left);
        cout << node->key << " ";
        __midTraverse(node->right);
    }
    
    void __postTraverse(Node *node) {
        
        if (node == nullptr) {
            return;
        }
        
        __postTraverse(node->left);
        __postTraverse(node->right);
        cout << node->key << " ";
    }
    
    
    Node* __max(Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        while (node->right) {
            node = node->right;
        }
        return node;
    }
    
    
    /**
     递归查找以root为根的搜索二叉树

     @param root 搜索二叉树的根节点
     @return 最大值
     */
    Node* __max_v2(Node *root) {
        
        if (root->right == nullptr)
            return root;
        else
            return __max_v2(root->right);
    }
    
    Node* __min(Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    
    
    /**
     递归查找以node为根的最小值

     @param root 搜索二叉树的根节点
     @return 最小值
     */
    Node* __min_v2(Node *root) {
        
        if (root->left == nullptr)
            return root;
        else
            return __min_v2(root->left);
    }
    
    
    Node* __removeMax_v2(Node *root) {
        
        if (root->right == nullptr) {
            Node *left = root->left;
            delete root;
            m_count--;
            return left;
        }
        
        root->right = __removeMax_v2(root->right);
        return root;
    }

    Node* __removeMin_v2(Node *root) {
        
        if (root->left == nullptr) {
            Node *right = root->right;
            delete root;
            m_count--;
            return right;
        }
        
        root->left = __removeMin_v2(root->left);
        return root;
    }
    
    
    /**
     删除以root为根的二叉搜索树中指定的key

     @param root 二叉搜索树的根节点
     @param key 删除的key
     @return 删除指定key后的二叉搜索树
     */
    Node* __remove_v2(Node *root, Key key) {
        
        if (root == nullptr) {
            return nullptr;
        }
        
        if (key == root->key) {
#if 1
            if (root->left == nullptr) { // 没有左孩子
                Node *right = root->right;
                delete root;
                m_count--;
                return right;
            }
            
            if (root->right == nullptr) { // 没有右孩子
                Node *left = root->left;
                delete root;
                m_count--;
                return left;
            }
            
            // root->left != nullptr && root->right != nullptr
            Node *rightMin = __min_v2(root->right);
            Node *targetNode = new Node(rightMin);
            m_count++;
            targetNode->left = root->left;
            targetNode->right = __removeMin_v2(root->right);
            delete root;
            m_count--;
            return targetNode;
#else
            if (root->left) {
                Node *leftMax = __max_v2(root->left);
                root->key = leftMax->key;
                root->value = leftMax->value;
                root->left = __removeMax_v2(root->left);
                return root;
            } else if (root->right) {
                Node *rightMin = __min_v2(root->right);
                root->key = rightMin->key;
                root->value = rightMin->value;
                root->right = __removeMin_v2(root->right);
                return root;
            } else {
                delete root;
                m_count--;
                return nullptr;
            }
#endif
        } else if (key < root->key) {
            root->left = __remove_v2(root->left, key);
        } else { // key > root->key
            root->right = __remove_v2(root->right, key);
        }
        return root;
    }
    
    void __remove_v3(Node *node, Key key) {
        // node结点的父节点
        Node *p = nullptr;
        
        while (node && node->key != key) {
            p = node;
            if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        
        if (node == nullptr) return;
        
        if (node->left && node->right) {
            // 寻找右子树中的最小结点
            Node *min = node->right;
            Node *minP = node;
            while (min->left) {
                minP = min;
                min = min->left;
            }
            
            node->value = min->value;
            p = minP;
            node = min;
        }
        
        Node *child = nullptr;
        // 只有左结点
        if (node->left) {
            child = node->left;
        } else if (node->right) {
            child = node->right;
        }
        
        if (p == nullptr) { // 删除的是根结点
            m_root = child;
        } else if (p->right == node) {
            p->right = child;
        } else {
            p->left = child;
        }
        
        delete node;
        m_count--;
    }
};


#endif /* BST_hpp */
