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
        m_root = __insert(m_root, key, value);
    }

    void insert_v2(Key key, Value value) {
        
        Node **node = &m_root;
        
        while (true) {
            
            if (*node == nullptr) {
                *node = new Node(key, value);
                m_count++;
                break;
            }
            
            if (*node->key == key) {
                *node->value = value;
                break;
            } else if (key < *node->key) {
                node = &(*node->left);
            } else { // key > node->key
                node = &(*node->right);
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
    
};


#endif /* BST_hpp */
